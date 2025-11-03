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
    ID_USER_LOGIN = 1003, //用户登录
    ID_CHAT_LOGIN = 1004, //登录聊天服务器
    ID_CHAT_LOGIN_RSP = 1005, //登录聊天服务器回包
    ID_SEARCH_USER_REQ = 1006 //查找用户回包
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

struct ServerInfo{
    int Uid;
    QString Host;
    QString Port;
    QString Token;
};

//自定义QListWidgetItem的几种类型
enum ListItemType{
    CHAT_USER_ITEM, //聊天用户
    CONTACT_USER_ITEM, //联系人用户
    SEARCH_USER_ITEM, //搜索到的用户
    ADD_USER_TIP_ITEM, //提示添加用户
    INVALID_ITEM,  //不可点击条目
    GROUP_TIP_ITEM, //分组提示条目
    LINE_ITEM,  //分割线
    APPLY_FRIEND_ITEM, //好友申请
};

enum ClickLbState{
    Normal = 0,
    Selected = 1
};

extern QString gate_url_prefix;

enum class ChatRole
{
    Self,
    Other
};

struct MsgInfo{
    QString msgFlag;//"text,image,file"
    QString content;//表示文件和图像的url,文本信息
    QPixmap pixmap;//文件和图片的缩略图
};

inline const std::vector<QString>  strs ={"hello world !",
                             "nice to meet u",
                             "New year，new life",
                             "You have to love yourself",
                             "My love is written in the wind ever since the whole world is you"};
inline const std::vector<QString> heads = {
    ":/res/head_1.jpg",
    ":/res/head_2.jpg",
    ":/res/head_3.jpg",
    ":/res/head_4.jpg",
    ":/res/head_5.jpg"
};
inline const std::vector<QString> names = {
    "llfc",
    "zack",
    "golang",
    "cpp",
    "java",
    "nodejs",
    "python",
    "rust"
};

#endif // GLOBAL_H
