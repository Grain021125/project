#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include "global.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile qss(":/style/stylesheet.qss");
    if (qss.open(QFile::ReadOnly)) {
        qDebug("open success");
        QString style = QString::fromLatin1(qss.readAll());
        a.setStyleSheet(style);
        qss.close();
    } else {
        qDebug("open failed");
    }

    // 获取当前应用程序的路径
    QString app_path = QCoreApplication::applicationDirPath();
    // 拼接文件名
    QString fileName = "config.ini";
    QString config_path = QDir::toNativeSeparators(app_path +
                                                   QDir::separator() + fileName);

    QSettings settings(config_path, QSettings::IniFormat);
    QString gate_host = settings.value("GateServer/host").toString();
    QString gate_port = settings.value("GateServer/port").toString();
    qDebug() << gate_port;
    gate_url_prefix = "http://"+gate_host+":"+gate_port;

    MainWindow w;
    w.show();

    qRegisterMetaType<ReqId>("ReqId");
    qRegisterMetaType<ErrorCodes>("ErrorCodes");
    return a.exec();
}
