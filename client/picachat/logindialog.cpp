#include "logindialog.h"
#include "ui_logindialog.h"
#include "clickablelabel.h"
#include "httpmgr.h"

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    InitHttpHandlers();

    connect(ui->reg_button, &QPushButton::clicked, this, &LoginDialog::switchRegister);
    ui->pass_edit->setEchoMode(QLineEdit::Password);

    ui->forget_label->setCursor(Qt::PointingHandCursor);
    connect(ui->forget_label, &ClickableLabel::clicked, this, &LoginDialog::slot_forget_pwd);

    connect(HttpMgr::GetInstance().get(), &HttpMgr::sig_login_mod_finish, this, &LoginDialog::slot_login_mod_finish);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::InitHttpHandlers()
{
    _handlers.insert(ReqId::ID_USER_LOGIN, [this](const QJsonObject& jsonObj) {
        int error = jsonObj["error"].toInt();
        if (error != ErrorCodes::SUCCESS) {
            if (error == 1006) {
                showTip(tr("用户不存在"), false);
            }
            if (error == 1007) {
                showTip(tr("密码错误"), false);
            }
            return;
        }

        auto user = jsonObj["user"].toString();
        showTip(tr("登录成功"), true);
        qDebug() << "user is " << user;
    });
}



void LoginDialog::slot_forget_pwd()
{
    qDebug()<<"slot forget pwd";
    emit switchReset();
}

void LoginDialog::slot_login_mod_finish(ReqId id, QString res,ErrorCodes err)
{
    if(err != ErrorCodes::SUCCESS){
        showTip(tr("网络请求错误"),false);
        return;
    }
    // 解析 JSON 字符串,res需转化为QByteArray
    QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());
    //json解析错误
    if(jsonDoc.isNull()){
        showTip(tr("json解析错误"),false);
        return;
    }
    //json解析错误
    if(!jsonDoc.isObject()){
        showTip(tr("json解析错误"),false);
        return;
    }

    _handlers[id](jsonDoc.object());
}

void LoginDialog::on_login_button_clicked()
{
    qDebug() << "login button clicked";
    QString user = ui->user_edit->text();
    QString pass = ui->pass_edit->text();
    if (user == "") {
        showTip("用户名不能为空", false);
        return;
    }

    if (pass == "") {
        showTip("密码不能为空", false);
        return;
    }

    QJsonObject json_obj;
    json_obj["user"] = user;
    json_obj["password"] = pass;
    showTip("正在登录...", true);
    HttpMgr::GetInstance()->PostHttpReq(QUrl(gate_url_prefix + "/user_login"),
                                        json_obj, ReqId::ID_USER_LOGIN, Modules::LOGINMOD);
}

void LoginDialog::showTip(QString str, bool b_ok)
{
    if (b_ok) {
        ui->error_label->setProperty("state","normal");
    } else {
        ui->error_label->setProperty("state","err");
    }
    ui->error_label->setText(str);
    repolish(ui->error_label);
}

