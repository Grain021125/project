#include "tcpmgr.h"
#include <QAbstractSocket>
#include <QJsonDocument>

TcpMgr::TcpMgr(): _host(""), _port(0), _b_recv_pending(false), _message_id(0), _message_len(0) {
    QObject::connect(&_socket, &QTcpSocket::connected, [&](){
        qDebug() << "Connected to server";
        emit sig_con_success(true);
    });

    QObject::connect(&_socket, &QTcpSocket::readyRead, [&](){
        _buffer.append(_socket.readAll());

        QDataStream stream(&_buffer, QIODevice::ReadOnly);
        stream.setVersion(QDataStream::Qt_5_0);

        forever{
            if (!_b_recv_pending) {
                //检查缓冲区中的数据是否足够解析出一个消息头(消息ID + 消息长度)
                if (_buffer.size() < static_cast<int>(sizeof(quint16) * 2)) {
                    return;
                }

                //预读取消息ID和消息长度,但不从缓冲区中移除
                stream >> _message_id >> _message_len;

                //将buffer中前四个字节移除
                _buffer = _buffer.mid(sizeof(quint16) * 2);

                qDebug() << "Message ID:" << _message_id << ", length:" << _message_len;
            }

            if (_buffer.size() < _message_len) {
                _b_recv_pending = true;
                return;
            }

            _b_recv_pending = false;

            //读取消息体
            QByteArray messageBody = _buffer.mid(0, _message_len);
            qDebug() << "receive body msg is " << messageBody;

            _buffer = _buffer.mid(_message_len);
            handleMessage(ReqId(_message_id), _message_len, messageBody);
        }
    });

    //错误处理
    QObject::connect(&_socket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::errorOccurred), [&](QAbstractSocket::SocketError socketError) {
        Q_UNUSED(socketError)
        qDebug() << "Error:" << _socket.errorString();
        emit sig_con_success(false);
    });

    //处理连接断开
    QObject::connect(&_socket, &QTcpSocket::disconnected, [&]() {
        qDebug() << "Disconnected from server.";
    });

    //连接发送信号用来发送数据
    QObject::connect(this, &TcpMgr::sig_send_data, this, &TcpMgr::slot_send_data);

    //注册消息
    initHandlers();
}

void TcpMgr::initHandlers()
{
    _handlers.insert(ID_CHAT_LOGIN_RSP, [this](ReqId id, int len, QByteArray data) {
        Q_UNUSED(len);
        qDebug() << "handle id is " << id << "; data is " << data;

        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);

        if (jsonDoc.isNull()) {
            qDebug() << "Falied to create QJsonDocument.";
            return;
        }

        QJsonObject jsonObj = jsonDoc.object();

        if (!jsonObj.contains("error")) {
            int err = ErrorCodes::ERR_JSON;
            qDebug() << "Login Faild, error is Json Parse Error " << err;
            return;
        }

        int err = jsonObj["error"].toInt();
        if (err != ErrorCodes::SUCCESS) {
            qDebug() << "Login Faild, error is " << err;
            return;
        }

        emit sig_switch_chatdialg();
    });
}

void TcpMgr::handleMessage(ReqId reqId, int len, QByteArray msg)
{
    auto find_iter = _handlers.find(reqId);
    if (find_iter == _handlers.end()) {
        qDebug() << "not found id [" << reqId << "] to handle";
        return;
    }

    find_iter.value()(reqId, len, msg);
}



void TcpMgr::slot_send_data(ReqId reqId, QString data)
{
    uint16_t id = reqId;
    // 将字符串转换为UTF-8编码的字节数组
    QByteArray dataBytes = data.toUtf8();
    // 计算长度（使用网络字节序转换）
    quint16 len = static_cast<quint16>(data.size());
    // 创建一个QByteArray用于存储要发送的所有数据
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    // 设置数据流使用网络字节序
    out.setByteOrder(QDataStream::BigEndian);
    // 写入ID和长度
    out << id << len;
    // 添加字符串数据
    block.append(dataBytes);
    // 发送数据
    _socket.write(block);
}

void TcpMgr::slot_tcp_connect(ServerInfo si)
{
    qDebug() << "receive tcp connect signal";

    _host = si.Host;
    _port = static_cast<uint16_t>(si.Port.toUInt());

    qDebug() << _host << " " << _port;
    _socket.connectToHost(si.Host, _port);
}
