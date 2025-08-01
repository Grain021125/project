#ifndef GLOBAL_H
#define GLOBAL_H


#include <QWidget>
#include <functional>
#include "Qstyle"
#include <QRegularExpression>
#include <QNetworkReply>
#include <QJsonObject>
#include <QUrl>
#include <QDir>
#include <QSettings>
#include <QTimer>




// 刷新qss
extern std::function<void(QWidget*)> repolish;

enum ReqId{
    ID_GET_VARIFY_CODE = 1001, //获取验证码
    ID_REG_USER = 1002, //注册用户
    ID_USER_LOGIN = 1003 //用户登录
};

enum Modules{
    REGISTERMOD = 0,
    LOGINMOD = 1
};

enum ErrorCodes{
    SUCCESS = 0,
    ERR_JSON = 1, //json解析失败
    ERR_NETWORK = 2, //网络错误
};

extern QString gate_url_prefix;

#endif // GLOBAL_H
