#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include "global.h"

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();

private slots:
    void on_get_code_button_clicked();

    void on_sure_button_clicked();

    void on_cancel_button_clicked();

public slots:
    void slot_reg_mod_finish(ReqId id, QString result, ErrorCodes err);

signals:
    void sigSwitchLogin();

private:
    void initHttpHandlers();
    void showTip(QString str, bool b_ok);
    void ChangeTipPage();
    Ui::RegisterDialog *ui;
    QTimer *_count_timer;
    int _count_time = 3;

    QMap<ReqId, std::function<void(const QJsonObject&)>> _handlers;
};

#endif // REGISTERDIALOG_H
