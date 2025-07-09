#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "global.h"
#include "httpmgr.h"

RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    ui->pass_edit->setEchoMode(QLineEdit::Password);
    ui->verify_edit->setEchoMode(QLineEdit::Password);

    ui->error_label->setProperty("state","normal");
    repolish(ui->error_label);

    connect(HttpMgr::GetInstance().get(), &HttpMgr::sig_reg_mod_finish, this, &RegisterDialog::slot_reg_mod_finish);

    initHttpHandlers();
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}



void RegisterDialog::on_get_code_button_clicked()
{
    auto email = ui->email_edit->text();
    static const QRegularExpression regex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    bool match = regex.match(email).hasMatch();
    if (match) {
        //TODO: 发送http验证码
        showTip(tr("邮箱正确"), true);
    } else {
        showTip(tr("邮箱不正确"), false);
    }
}

void RegisterDialog::slot_reg_mod_finish(ReqId id, QString result, ErrorCodes err)
{
    switch (err) {
    case ErrorCodes::SUCCESS:
        showTip("网络请求错误", false);
        break;
    default:
        break;
    }

    //解析JSON字符串, res转化为 QByteArray
    QJsonDocument jsonDoc = QJsonDocument::fromJson(result.toUtf8());
    if(jsonDoc.isEmpty()) {
        showTip(tr("json解析失败"), false);
        return;
    }

    //json解析错误
    if (!jsonDoc.isObject()) {
        showTip(tr("json解析失败"), false);
        return;
    }


    _handlers[id](jsonDoc.object());
    return;
}

void RegisterDialog::initHttpHandlers()
{
    //注册获取验证码回包的逻辑
    _handlers.insert(ReqId::ID_GET_VARIFY_CODE, [this](const QJsonObject& jsonObj){
        int error = jsonObj["eroor"].toInt();
        if(error != ErrorCodes::SUCCESS) {
            showTip(tr("参数错误"), false);
            return;
        }

        auto email = jsonObj["email"].toString();
        showTip(tr("验证码已经发送到用户邮箱"), true);

        qDebug() << "email is " << email;
    });
}


void RegisterDialog::showTip(QString str, bool b_ok)
{
    if (b_ok) {
        ui->error_label->setProperty("state","normal");
    } else {
        ui->error_label->setProperty("state","err");
    }
    ui->error_label->setText(str);
    repolish(ui->error_label);
}

