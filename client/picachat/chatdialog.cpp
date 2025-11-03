#include "chatdialog.h"
#include "ui_chatdialog.h"
#include <QRandomGenerator>
#include "chatuserwid.h"

ChatDialog::ChatDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChatDialog)
    ,_mode(ChatUIMode::ChatMode),
    _state(ChatUIMode::ChatMode),_b_loading(false)
{
    ui->setupUi(this);
    ui->add_button->SetState("normal", "hover", "press");
    ui->side_chat_lab->SetState();
    ui->side_contact_lab->SetState();

    ui->stackedWidget->setCurrentWidget(ui->chat_page);
    _state = ChatUIMode::ChatMode;
    ShowSearch(false);

    addChatUserList();

    QAction *searchAction = new QAction(ui->search_edit);
    searchAction->setIcon(QIcon(":/res/search.png"));
    ui->search_edit->addAction(searchAction,QLineEdit::LeadingPosition);
    ui->search_edit->setPlaceholderText(QStringLiteral("搜索"));

    // 当需要显示清除图标时，更改为实际的清除图标
    connect(ui->search_edit, &QLineEdit::textChanged, [this](const QString &text) {
        if (!text.isEmpty()) {
            ui->search_edit->setClearButtonEnabled(true);
            ShowSearch(true);
        } else {
            ui->search_edit->setClearButtonEnabled(false);
            ShowSearch(false);
        }
    });
    ui->search_edit->SetMaxLength(15);

    QPixmap pixmap(":/res/head_1.jpg");
    ui->side_head_lab->setPixmap(pixmap); // 将图片设置到QLabel上
    QPixmap scaledPixmap = pixmap.scaled( ui->side_head_lab->size(), Qt::KeepAspectRatio); // 将图片缩放到label的大小
    ui->side_head_lab->setPixmap(scaledPixmap); // 将缩放后的图片设置到QLabel上
    ui->side_head_lab->setScaledContents(true); // 设置QLabel自动缩放图片内容以适应大小

    ui->side_chat_lab->setProperty("state","normal");

    ui->side_chat_lab->SetState("normal","hover","pressed","selected_normal","selected_hover","selected_pressed");

    ui->side_contact_lab->SetState("normal","hover","pressed","selected_normal","selected_hover","selected_pressed");

    AddlabGroup(ui->side_chat_lab);
    AddlabGroup(ui->side_contact_lab);


    //连接加载联系人的信号和槽函数
    // connect(ui->con_user_list, &ContactUserList::sig_loading_contact_user,
    //         this, &ChatDialog::slot_loading_contact_user);

    //连接联系人页面点击好友申请条目的信号
    connect(ui->con_user_list, &ContactUserList::sig_switch_apply_friend_page,
            this,&ChatDialog::slot_switch_apply_friend_page);

    //连接清除搜索框操作
    connect(ui->friend_apply_page, &ApplyFriendPage::sig_show_search, this, &ChatDialog::slot_show_search);


    connect(ui->side_chat_lab, &StateWidget::clicked, this, &ChatDialog::slot_side_chat);
    connect(ui->side_contact_lab, &StateWidget::clicked, this, &ChatDialog::slot_side_contact);

    // 链接搜索框输入变化
    connect(ui->search_edit, &QLineEdit::textChanged, this, &ChatDialog::slot_text_changed);

    ui->side_chat_lab->SetSelected(true);

}

void ChatDialog::slot_side_chat()
{
    qDebug()<< "receive side chat clicked";
    ClearLabelState(ui->side_chat_lab);
    ui->stackedWidget->setCurrentWidget(ui->chat_page);
    _state = ChatUIMode::ChatMode;
    ShowSearch(false);
}


void ChatDialog::slot_side_contact(){
    qDebug()<< "receive side contact clicked";
    ClearLabelState(ui->side_contact_lab);
    // 设置
    if(_last_widget == nullptr){
        ui->stackedWidget->setCurrentWidget(ui->friend_apply_page);
        _last_widget = ui->friend_apply_page;
    }else{
        ui->stackedWidget->setCurrentWidget(_last_widget);
    }

    _state = ChatUIMode::ContactMode;
    ShowSearch(false);
}

void ChatDialog::ClearLabelState(StateWidget *lb)
{
    for(auto & ele: _lb_list){
        if(ele == lb){
            continue;
        }

        ele->ClearState();
    }
}

void ChatDialog::AddlabGroup(StateWidget *lb)
{
    _lb_list.push_back(lb);
}

void ChatDialog::ShowSearch(bool bsearch)
{
    if(bsearch){
        ui->chat_user_list->hide();
        ui->con_user_list->hide();
        ui->search_list->show();
        _mode = ChatUIMode::SearchMode;
    }else if(_state == ChatUIMode::ChatMode){
        ui->chat_user_list->show();
        ui->con_user_list->hide();
        ui->search_list->hide();
        _mode = ChatUIMode::ChatMode;
    }else if(_state == ChatUIMode::ContactMode){
        ui->chat_user_list->hide();
        ui->search_list->hide();
        ui->con_user_list->show();
        _mode = ChatUIMode::ContactMode;
    }
}

void ChatDialog::addChatUserList()
{
    // 创建QListWidgetItem，并设置自定义的widget
    for(int i = 0; i < 30; i++){
        int randomValue = QRandomGenerator::global()->bounded(100); // 生成0到99之间的随机整数
        int str_i = randomValue%strs.size();
        int head_i = randomValue%heads.size();
        int name_i = randomValue%names.size();
        auto *chat_user_wid = new ChatUserWid();
        chat_user_wid->SetInfo(names[name_i], heads[head_i], strs[str_i]);
        QListWidgetItem *item = new QListWidgetItem;
        //qDebug()<<"chat_user_wid sizeHint is " << chat_user_wid->sizeHint();
        item->setSizeHint(chat_user_wid->sizeHint());
        ui->chat_user_list->addItem(item);
        ui->chat_user_list->setItemWidget(item, chat_user_wid);
    }
}

void ChatDialog::slot_text_changed(const QString &str)
{
    //qDebug()<< "receive slot text changed str is " << str;
    if (!str.isEmpty()) {
        ShowSearch(true);
    }
}

void ChatDialog::slot_switch_apply_friend_page()
{
    qDebug()<<"receive switch apply friend page sig";
    _last_widget = ui->friend_apply_page;
    ui->stackedWidget->setCurrentWidget(ui->friend_apply_page);
}

void ChatDialog::slot_show_search(bool show)
{
    ShowSearch(show);
}

ChatDialog::~ChatDialog()
{
    delete ui;
}
