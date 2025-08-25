#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QDialog>

enum ChatUIMode {
    ContactMode = 0,
    ChatMode = 1,
    SearchMode = 3
};

namespace Ui {
class ChatDialog;
}

class ChatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChatDialog(QWidget *parent = nullptr);
    void ShowSearch(bool);
    ~ChatDialog();

private:
    void addChatUserList();

    Ui::ChatDialog *ui;
    ChatUIMode _mode;
    ChatUIMode _state;
    bool _b_loading;
};

#endif // CHATDIALOG_H
