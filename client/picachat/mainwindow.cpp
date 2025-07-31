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

    // 连接登陆页面忘记密码信号
    connect(_login_dialg, &LoginDialog::switchReset, this, &MainWindow::SlotSwitchReset);
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

void MainWindow::SlotSwitchReset()
{
    //创建一个CentralWidget, 并将其设置为MainWindow的中心部件
    // _reset_dialg = new ResetDialog(this);
    // _reset_dialg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    // setCentralWidget(_reset_dlg);
    // _login_dialg->hide();
    // _reset_dialg->show();
    // //注册返回登录信号和槽函数
    // connect(_reset_dialg, &ResetDialog::switchLogin, this, &MainWindow::SlotSwitchLogin2);
}

