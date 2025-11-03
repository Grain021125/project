#include "apllyfriend.h"
#include "ui_apllyfriend.h"
#include <QScrollBar>
#include "usermgr.h"


ApllyFriend::ApllyFriend(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ApllyFriend)
{
    ui->setupUi(this);
    // 隐藏对话框标题栏
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    this->setObjectName("ApllyFriend");
    this->setModal(true);
    ui->name_edit->setPlaceholderText(tr("恋恋风辰"));
    // ui->lab_edit->setPlaceholderText("搜索、添加标签");
    ui->back_edit->setPlaceholderText("燃烧的胸毛");

    // ui->lab_edit->SetMaxLength(21);
    // ui->lab_edit->move(2, 2);
    // ui->lab_edit->setFixeditHeight(20);
    // ui->lab_edit->setMaxLength(10);
    // ui->input_tip_wid->hide();

    // _tip_cur_point = QPoint(5, 5);

    // _tip_data = { "同学","家人","菜鸟教程","C++ Primer","Rust 程序设计",
    //              "父与子学Python","nodejs开发指南","go 语言开发指南",
    //              "游戏伙伴","金融投资","微信读书","拼多多拼友" };

    // connect(ui->more_lab, &ClickeditOnceLabel::clickedit, this, &ApllyFriend::ShowMoreLabel);
    // InitTiplabs();
    // //链接输入标签回车事件
    // connect(ui->lab_edit, &Customizeeditit::returnPressedit, this, &ApllyFriend::SlotLabelEnter);
    // connect(ui->lab_edit, &Customizeeditit::textChangedit, this, &ApllyFriend::SlotLabelTextChange);
    // connect(ui->lab_edit, &Customizeeditit::edititingFinishedit, this, &ApllyFriend::SlotLabeledititFinishedit);
    // connect(ui->tip_lab, &ClickeditOnceLabel::clickedit, this, &ApllyFriend::SlotAddFirendLabelabyClickTip);

    ui->scrollArea->horizontalScrollBar()->setHidden(true);
    ui->scrollArea->verticalScrollBar()->setHidden(true);
    ui->scrollArea->installEventFilter(this);
    ui->sure_button->SetState("normal","hover","press");
    ui->sure_button->SetState("normal","hover","press");
    //连接确认和取消按钮的槽函数
    connect(ui->cancel_button, &QPushButton::clicked, this, &ApllyFriend::SlotApllyCancel);
    connect(ui->sure_button, &QPushButton::clicked, this, &ApllyFriend::SlotApllySure);
}

ApllyFriend::~ApllyFriend()
{
    qDebug()<< "ApllyFriend destruct";
    delete ui;
}

bool ApllyFriend::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->scrollArea && event->type() == QEvent::Enter)
    {
        ui->scrollArea->verticalScrollBar()->setHidden(false);
    }
    else if (obj == ui->scrollArea && event->type() == QEvent::Leave)
    {
        ui->scrollArea->verticalScrollBar()->setHidden(true);
    }
    return QObject::eventFilter(obj, event);
}

void ApllyFriend::SetSearchInfo(std::shared_ptr<SearchInfo> si)
{
    _si = si;
    auto applyname = UserMgr::GetInstance()->GetName();
    auto bakname = si->_name;
    ui->name_edit->setText(applyname);
    ui->back_edit->setText(bakname);
}

void ApllyFriend::SlotApllyCancel()
{
    qDebug() << "Slot Apply Cancel";
    this->hide();
    deleteLater();
}

void ApllyFriend::SlotApllySure()
{
    qDebug()<<"Slot Apply Sure called" ;
    this->hide();
    deleteLater();
}
