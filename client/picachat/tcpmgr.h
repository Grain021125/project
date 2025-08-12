#ifndef TCPMGR_H
#define TCPMGR_H

#include <QTcpSocket>
#include "singleton.h"
#include "global.h"
#include <functional>
#include <QObject>
#include <QByteArray>

class TcpMgr: public QObject, public Singleton<TcpMgr>
{
    Q_OBJECT
    friend class Singleton<TcpMgr>;
public:
    ~TcpMgr() = default;
private:
    TcpMgr();
    void initHandlers();
    void handleMessage(ReqId, int, QByteArray);
    QTcpSocket _socket;
    QString _host;
    uint16_t _port;
    QByteArray _buffer;
    bool _b_recv_pending;
    quint16 _message_id;
    quint16 _message_len;
    QMap<ReqId, std::function<void(ReqId, int, QByteArray)>> _handlers;
public slots:
    void slot_send_data(ReqId reqId, QString data);
    void slot_tcp_connect(ServerInfo si);
signals:
    void sig_con_success(bool);
    void sig_send_data(ReqId reqId, QString data);
    void sig_switch_chatdialg();
};

#endif // TCPMGR_H
