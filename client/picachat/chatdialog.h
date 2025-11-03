#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QDialog>
#include "statewidget.h"

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
    void AddlabGroup(StateWidget* lb);
    void ClearLabelState(StateWidget* lb);

    Ui::ChatDialog *ui;
    ChatUIMode _mode;
    ChatUIMode _state;
    bool _b_loading;

    QList<StateWidget*> _lb_list;
    QWidget* _last_widget;

public slots:
    void slot_side_chat();
    void slot_side_contact();
    void slot_text_changed(const QString &str);
    void slot_switch_apply_friend_page();
    void slot_show_search(bool show);
};

#endif // CHATDIALOG_H
