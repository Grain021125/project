#include "MysqlPool.h"

MysqlPool::MysqlPool(const std::string& url, const std::string& user, const std::string& password, const std::string& schema, int poolsize) :
	_url(url), _user(user), _password(password), _schema(schema), _poolsize(poolsize), _b_stop(false)
{
	try
	{
		for (int i = 0; i < _poolsize; ++i) {
			sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
			sql::Connection* connection(driver->connect(_url, _user, _password));
			connection->setSchema(_schema);
			// ��ȡ��ǰʱ���
			auto currentTime = std::chrono::system_clock::now().time_since_epoch();
			// ��ʱ���ת��Ϊ��
			long long timestamp = std::chrono::duration_cast<std::chrono::seconds>(currentTime).count();
			_pool.push(std::make_unique<SqlConnection>(connection, timestamp));
		}

		_check_thread = std::thread([this] {
			while (!_b_stop) {
				checkConnection();
				std::this_thread::sleep_for(std::chrono::seconds(60)); // ÿ60����һ������
			}
			});

		_check_thread.detach(); // �����߳�
	}
	catch (const std::exception& err)
	{
		std::cerr << "MysqlPool init failed: " << err.what() << std::endl;
	}
}

MysqlPool::~MysqlPool()
{
	std::lock_guard<std::mutex> lock(_mutex);
	Stop();
	while (!_pool.empty()) {
		_pool.front()->getConnection().close(); //��ʵ��sql::Connection�������������Զ��ر�����
		_pool.pop();
	}
}

void MysqlPool::Stop()
{
	_b_stop = true;
	_cond_var.notify_all();
}

void MysqlPool::checkConnection()
{
	std::lock_guard<std::mutex> lock(_mutex);
	auto currentTime = std::chrono::system_clock::now().time_since_epoch();
	long long currentTimestamp = std::chrono::duration_cast<std::chrono::seconds>(currentTime).count();
	for (int i = 0; i < _pool.size(); ++i) {
		auto connection = std::move(_pool.front());
		_pool.pop();
		Defer defer([this, &connection] {
			_pool.push(std::move(connection));
			});

		if (currentTimestamp - connection->getLastOpTime() < 10) {// ���������10s���в���������Ϊ�����ǻ�Ծ��
			continue;
		}

		try {
			std::unique_ptr<sql::Statement> stmt(connection->getConnection().createStatement());
			stmt->executeQuery("SELECT 1");
			connection->setLastOpTime(currentTimestamp);
		}
		catch (sql::SQLException& e) {
			std::cout << "Error keeping connection alive:" << e.what() << std::endl;
			//���´������Ӳ��滻�ɵ�����
			sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
			auto* newcon = driver->connect(_url, _user, _password);
			newcon->setSchema(_schema);
			connection->setConnection(newcon);
			connection->setLastOpTime(currentTimestamp);
		}
	}
}

std::unique_ptr<SqlConnection> MysqlPool::getConnection()
{
	std::unique_lock<std::mutex> lock(_mutex);
	_cond_var.wait(lock, [this] {
		if (_b_stop) {
			return true;
		}

		return !_pool.empty();
		});
	if (_b_stop) {
		return nullptr;
	}

	std::unique_ptr<SqlConnection> connection(std::move(_pool.front()));
	_pool.pop();
	return connection;
}

void MysqlPool::returnConnection(std::unique_ptr<SqlConnection> connection)
{
	std::unique_lock<std::mutex> lock(_mutex);
	if (_b_stop) {
		return;
	}
	_pool.push(std::move(connection));
	_cond_var.notify_one();
}
