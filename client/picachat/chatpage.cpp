#include "chatpage.h"
#include "ui_chatpage.h"

ChatPage::ChatPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChatPage)
{
    ui->setupUi(this);
    ui->emoj_lab->SetState();
    ui->file_lab->SetState();
}

ChatPage::~ChatPage()
{
    delete ui;
}
