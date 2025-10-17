#include "findsuccessdialog.h"
#include "ui_findsuccessdialog.h"
#include <QDir>

FindSuccessDialog::FindSuccessDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FindSuccessDialog)
{
    ui->setupUi(this);
    // 隐藏标题栏
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    // 获取当前应用程序的路径
    QString app_path = QCoreApplication::applicationDirPath();
    QString pix_path = QDir::toNativeSeparators(app_path +
                                                QDir::separator() + "static" + QDir::separator() + "head_1.jpg");

    QPixmap head_pix(pix_path);
    head_pix = head_pix.scaled(ui->head_lab->size(),
                               Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->head_lab->setPixmap(head_pix);
    ui->add_friend_button->SetState("normal","hover","press");
    this->setModal(true);
}

FindSuccessDialog::~FindSuccessDialog()
{
    qDebug()<<"FindSuccessDlg destruct";
    delete ui;
}

void FindSuccessDialog::SetSearchInfo(std::shared_ptr<SearchInfo> si)
{
    ui->name_lab->setText(si->_name);
    _si = si;
}

void FindSuccessDialog::on_add_friend_button_clicked()
{
    // TODO: 添加好友界面弹出
}
