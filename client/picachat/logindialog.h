#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "global.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private:
    void InitHttpHandlers();
    void showTip(QString, bool);
    Ui::LoginDialog *ui;
    QMap<ReqId, std::function<void(const QJsonObject&)>>  _handlers;

    int _uid;
    QString _token;
public slots:
    void slot_forget_pwd();
    void slot_login_mod_finish(ReqId, QString, ErrorCodes);
    void slot_tcp_con_finish(bool);
    void slot_switch_chatdialg();
signals:
    void switchRegister();
    void switchReset();
    void sig_connect_tcp(ServerInfo);
    void switchChat();
private slots:
    void on_login_button_clicked();
};

#endif // LOGINDIALOG_H
