#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // TimerBtn *testBtn = new TimerBtn(this);
    // testBtn->setText("Manual Test");
    // testBtn->setGeometry(10, 10, 100, 30);
    // testBtn->show();
    _login_dialg = new LoginDialog(this);
    setCentralWidget(_login_dialg);
    _login_dialg->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);

    // 创建和注册消息链接
    connect(_login_dialg, &LoginDialog::switchRegister, this, &MainWindow::SlotSwitchReg);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SlotSwitchReg()
{
    _reg_dialg = new RegisterDialog(this);
    _reg_dialg->hide();
    _reg_dialg->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);

    connect(_reg_dialg, &RegisterDialog::sigSwitchLogin, this, &MainWindow::SlotSwitchLogin);
    setCentralWidget(_reg_dialg);
    _login_dialg->hide();
    _reg_dialg->show();
}

void MainWindow::SlotSwitchLogin()
{
    _login_dialg = new LoginDialog(this);
    _login_dialg->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    setCentralWidget(_login_dialg);

    _reg_dialg->hide();
    _login_dialg->show();


    //连接登录界面注册信号
    connect(_login_dialg, &LoginDialog::switchRegister, this, &MainWindow::SlotSwitchReg);
}

