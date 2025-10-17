#include "apllyfriend.h"
#include "ui_apllyfriend.h"

ApllyFriend::ApllyFriend(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ApllyFriend)
{
    ui->setupUi(this);
}

ApllyFriend::~ApllyFriend()
{
    delete ui;
}
