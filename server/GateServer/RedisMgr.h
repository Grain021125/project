#pragma once
#include "const.h"
#include "Singleton.h"

class RedisConnectPool {
public:
	RedisConnectPool(size_t poolSize, const std::string& host, int port, const char* pwd)
		: _poolSize(poolSize), _host(host), _port(port), _password(pwd), _b_stop(false) {
		for (size_t i = 0; i < _poolSize; ++i) {
			std::unique_ptr<redisContext> context(redisConnect(_host.c_str(), _port));
			if (context == nullptr || context->err != 0) {
				redisFree(context.get());
				continue;
			}

			auto reply = (redisReply*)redisCommand(context.get(), "AUTH %s", pwd);
			if (reply->type == REDIS_REPLY_ERROR) {
				std::cout << "��֤ʧ��" << std::endl;
				freeReplyObject(reply);
				redisFree(context.get());
				continue;
			}

			//ִ�гɹ� �ͷ�redisCommandִ�к󷵻ص�redisReply��ռ�õ��ڴ�
			freeReplyObject(reply);
			std::cout << "��֤�ɹ�" << std::endl;
			_pool.push(std::move(context));
		}
	}

	~RedisConnectPool() {
		std::lock_guard<std::mutex> lock(_mutex);
		Stop();
		while (!_pool.empty()) {
			auto context = std::move(_pool.front());
			_pool.pop();
			if (context) {
				redisFree(context.get()); // �ͷ�redisContext
			}
		}
	}

	void Stop() {
		_b_stop.store(true);
		_cond.notify_all();
	}

	std::unique_ptr<redisContext> getConnection() {
		std::unique_lock<std::mutex> lock(_mutex);
		_cond.wait(lock, [this]() {
			if (_b_stop) {
				return true; // ���ֹͣ��־�����ã�ֱ�ӷ���
			}

			return !_pool.empty(); // �ȴ�ֱ��_pool���в�Ϊ��
		});


		if (_b_stop) {
			return nullptr; // ���ֹͣ��־�����ã�����nullptr
		}

		std::unique_ptr<redisContext> context = std::move(_pool.front());
		_pool.pop();
		return context; // ��ȡ����ǰ�˵�redisContext
	}

	void returnConnection(std::unique_ptr<redisContext> context) {
		std::lock_guard<std::mutex> lock(_mutex);
		if (_b_stop) {
			return; // ���ֹͣ��־�����ã�ֱ�ӷ���
		}
		_pool.push(std::move(context)); // ��redisContext�Żس���
		_cond.notify_one(); // ֪ͨ�ȴ����߳�
	}

private:
	size_t _poolSize;
	std::string _host;
	int _port;
	const char* _password;
	std::atomic<bool> _b_stop;
	std::queue <std::unique_ptr< redisContext >> _pool;
	std::mutex _mutex;
	std::condition_variable _cond;
};

class RedisMgr: public Singleton<RedisMgr>
{
	friend class Singleton<RedisMgr>;
public:
	~RedisMgr();
	bool Get(const std::string& key, std::string& value);
	bool Set(const std::string& key, const std::string& value);
	bool Auth(const std::string& password);
	bool LPush(const std::string& key, const std::string& value);
	bool LPop(const std::string& key, std::string& value);
	bool RPush(const std::string& key, const std::string& value);
	bool RPop(const std::string& key, std::string& value);
	bool HSet(const std::string& key, const std::string& hkey, const std::string& value);
	bool HSet(const char* key, const char* hkey, const char* hvalue, size_t hvaluelen);
	std::string HGet(const std::string& key, const std::string& hkey);
	bool Del(const std::string& key);
	bool ExistsKey(const std::string& key);
	void Close();
private:
	RedisMgr();

	std::unique_ptr<RedisConnectPool> _con_pool;
};

