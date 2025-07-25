#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _login_dialg = new LoginDialog(this);
    setCentralWidget(_login_dialg);



    // 创建和注册消息链接
    connect(_login_dialg, &LoginDialog::switchRegister, this, &MainWindow::SlotSwitchReg);
    _reg_dialg = new RegisterDialog(this);

    _login_dialg->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    _reg_dialg->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);

    _reg_dialg->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SlotSwitchReg()
{
    setCentralWidget(_reg_dialg);
    _login_dialg->hide();
    _reg_dialg->show();
}
