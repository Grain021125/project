#ifndef USERMGR_H
#define USERMGR_H

#include <QObject>
#include "singleton.h"
#include "userdata.h"

class UserMgr: public QObject,  public Singleton<UserMgr>
{
    Q_OBJECT
    friend class Singleton<UserMgr>;
public:
    ~UserMgr();
    QString GetName();
    void SetName(QString name);
    void SetUid(int uid);
    void SetToken(QString token);
    std::vector<std::shared_ptr<ApplyInfo>> GetApplyList();
private:
    UserMgr();
    QString _name;
    QString _token;
    int _uid;
    std::vector<std::shared_ptr<ApplyInfo>> _apply_list;
};

#endif // USERMGR_H
