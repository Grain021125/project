/********************************************************************************
** Form generated from reading UI file 'chatdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATDIALOG_H
#define UI_CHATDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <clickedbtn.h>
#include "chatuserlist.h"
#include "customizeedit.h"

QT_BEGIN_NAMESPACE

class Ui_ChatDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *side_bar;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QVBoxLayout *verticalLayout_3;
    QLabel *side_head_lab;
    QLabel *side_chat_lab;
    QLabel *side_contact_lab;
    QSpacerItem *verticalSpacer;
    QWidget *chat_user_wid;
    QVBoxLayout *verticalLayout;
    QWidget *search_wid;
    QHBoxLayout *horizontalLayout_2;
    CustomizeEdit *search_edit;
    QSpacerItem *horizontalSpacer;
    ClickedBtn *add_btn;
    ChatUserList *chat_user_list;
    QListWidget *search_list;
    QListWidget *con_user_list;
    QWidget *chat_data_wid;
    QVBoxLayout *verticalLayout_4;
    QWidget *title_wid;
    QHBoxLayout *horizontalLayout_3;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_5;
    QLabel *title_lab;
    QWidget *chat_data_list;
    QWidget *tool_wid;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_2;
    QLabel *emoj_lab;
    QSpacerItem *horizontalSpacer_3;
    QLabel *file_lab;
    QSpacerItem *horizontalSpacer_4;
    QTextEdit *chatEdit;
    QWidget *send_wid;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *recv_btn;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *send_btn;
    QSpacerItem *horizontalSpacer_7;

    void setupUi(QDialog *ChatDialog)
    {
        if (ChatDialog->objectName().isEmpty())
            ChatDialog->setObjectName("ChatDialog");
        ChatDialog->resize(424, 433);
        horizontalLayout = new QHBoxLayout(ChatDialog);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        side_bar = new QWidget(ChatDialog);
        side_bar->setObjectName("side_bar");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(side_bar->sizePolicy().hasHeightForWidth());
        side_bar->setSizePolicy(sizePolicy);
        side_bar->setMinimumSize(QSize(56, 0));
        side_bar->setMaximumSize(QSize(56, 16777215));
        verticalLayout_2 = new QVBoxLayout(side_bar);
        verticalLayout_2->setSpacing(7);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(10, 30, 0, 0);
        widget = new QWidget(side_bar);
        widget->setObjectName("widget");
        verticalLayout_3 = new QVBoxLayout(widget);
        verticalLayout_3->setSpacing(30);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        side_head_lab = new QLabel(widget);
        side_head_lab->setObjectName("side_head_lab");
        side_head_lab->setMinimumSize(QSize(30, 30));
        side_head_lab->setMaximumSize(QSize(30, 30));

        verticalLayout_3->addWidget(side_head_lab);

        side_chat_lab = new QLabel(widget);
        side_chat_lab->setObjectName("side_chat_lab");
        side_chat_lab->setMinimumSize(QSize(30, 30));
        side_chat_lab->setMaximumSize(QSize(30, 30));

        verticalLayout_3->addWidget(side_chat_lab);

        side_contact_lab = new QLabel(widget);
        side_contact_lab->setObjectName("side_contact_lab");
        side_contact_lab->setMinimumSize(QSize(30, 30));
        side_contact_lab->setMaximumSize(QSize(30, 30));

        verticalLayout_3->addWidget(side_contact_lab);


        verticalLayout_2->addWidget(widget);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout->addWidget(side_bar);

        chat_user_wid = new QWidget(ChatDialog);
        chat_user_wid->setObjectName("chat_user_wid");
        chat_user_wid->setMinimumSize(QSize(0, 0));
        chat_user_wid->setMaximumSize(QSize(250, 16777215));
        verticalLayout = new QVBoxLayout(chat_user_wid);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        search_wid = new QWidget(chat_user_wid);
        search_wid->setObjectName("search_wid");
        search_wid->setMinimumSize(QSize(0, 60));
        search_wid->setMaximumSize(QSize(16777215, 60));
        horizontalLayout_2 = new QHBoxLayout(search_wid);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(9, 9, 9, 9);
        search_edit = new CustomizeEdit(search_wid);
        search_edit->setObjectName("search_edit");

        horizontalLayout_2->addWidget(search_edit);

        horizontalSpacer = new QSpacerItem(5, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        add_btn = new ClickedBtn(search_wid);
        add_btn->setObjectName("add_btn");
        add_btn->setMinimumSize(QSize(24, 24));
        add_btn->setMaximumSize(QSize(24, 24));

        horizontalLayout_2->addWidget(add_btn);


        verticalLayout->addWidget(search_wid);

        chat_user_list = new ChatUserList(chat_user_wid);
        chat_user_list->setObjectName("chat_user_list");

        verticalLayout->addWidget(chat_user_list);

        search_list = new QListWidget(chat_user_wid);
        search_list->setObjectName("search_list");

        verticalLayout->addWidget(search_list);

        con_user_list = new QListWidget(chat_user_wid);
        con_user_list->setObjectName("con_user_list");

        verticalLayout->addWidget(con_user_list);


        horizontalLayout->addWidget(chat_user_wid);

        chat_data_wid = new QWidget(ChatDialog);
        chat_data_wid->setObjectName("chat_data_wid");
        verticalLayout_4 = new QVBoxLayout(chat_data_wid);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        title_wid = new QWidget(chat_data_wid);
        title_wid->setObjectName("title_wid");
        title_wid->setMinimumSize(QSize(0, 60));
        title_wid->setMaximumSize(QSize(16777215, 60));
        horizontalLayout_3 = new QHBoxLayout(title_wid);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        widget_2 = new QWidget(title_wid);
        widget_2->setObjectName("widget_2");
        verticalLayout_5 = new QVBoxLayout(widget_2);
        verticalLayout_5->setObjectName("verticalLayout_5");
        title_lab = new QLabel(widget_2);
        title_lab->setObjectName("title_lab");

        verticalLayout_5->addWidget(title_lab);


        horizontalLayout_3->addWidget(widget_2);


        verticalLayout_4->addWidget(title_wid);

        chat_data_list = new QWidget(chat_data_wid);
        chat_data_list->setObjectName("chat_data_list");

        verticalLayout_4->addWidget(chat_data_list);

        tool_wid = new QWidget(chat_data_wid);
        tool_wid->setObjectName("tool_wid");
        tool_wid->setMinimumSize(QSize(0, 60));
        tool_wid->setMaximumSize(QSize(16777215, 60));
        horizontalLayout_4 = new QHBoxLayout(tool_wid);
        horizontalLayout_4->setSpacing(7);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(2, 2, 2, 2);
        horizontalSpacer_2 = new QSpacerItem(5, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        emoj_lab = new QLabel(tool_wid);
        emoj_lab->setObjectName("emoj_lab");
        emoj_lab->setMinimumSize(QSize(25, 25));
        emoj_lab->setMaximumSize(QSize(25, 25));

        horizontalLayout_4->addWidget(emoj_lab);

        horizontalSpacer_3 = new QSpacerItem(5, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        file_lab = new QLabel(tool_wid);
        file_lab->setObjectName("file_lab");
        file_lab->setMinimumSize(QSize(25, 25));
        file_lab->setMaximumSize(QSize(25, 25));

        horizontalLayout_4->addWidget(file_lab);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        verticalLayout_4->addWidget(tool_wid);

        chatEdit = new QTextEdit(chat_data_wid);
        chatEdit->setObjectName("chatEdit");
        chatEdit->setMaximumSize(QSize(16777215, 150));

        verticalLayout_4->addWidget(chatEdit);

        send_wid = new QWidget(chat_data_wid);
        send_wid->setObjectName("send_wid");
        send_wid->setMinimumSize(QSize(0, 60));
        send_wid->setMaximumSize(QSize(16777215, 60));
        horizontalLayout_5 = new QHBoxLayout(send_wid);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_6);

        recv_btn = new QPushButton(send_wid);
        recv_btn->setObjectName("recv_btn");
        recv_btn->setMinimumSize(QSize(100, 30));
        recv_btn->setMaximumSize(QSize(100, 30));

        horizontalLayout_5->addWidget(recv_btn);

        horizontalSpacer_5 = new QSpacerItem(10, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        send_btn = new QPushButton(send_wid);
        send_btn->setObjectName("send_btn");
        send_btn->setMinimumSize(QSize(100, 30));
        send_btn->setMaximumSize(QSize(100, 30));

        horizontalLayout_5->addWidget(send_btn);

        horizontalSpacer_7 = new QSpacerItem(10, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_7);


        verticalLayout_4->addWidget(send_wid);


        horizontalLayout->addWidget(chat_data_wid);


        retranslateUi(ChatDialog);

        QMetaObject::connectSlotsByName(ChatDialog);
    } // setupUi

    void retranslateUi(QDialog *ChatDialog)
    {
        ChatDialog->setWindowTitle(QCoreApplication::translate("ChatDialog", "Dialog", nullptr));
        side_head_lab->setText(QCoreApplication::translate("ChatDialog", "[\345\244\264\345\203\217]", nullptr));
        side_chat_lab->setText(QString());
        side_contact_lab->setText(QString());
        add_btn->setText(QString());
        title_lab->setText(QCoreApplication::translate("ChatDialog", "\350\260\267\351\233\250", nullptr));
        emoj_lab->setText(QString());
        file_lab->setText(QString());
        recv_btn->setText(QCoreApplication::translate("ChatDialog", "\346\216\245\346\224\266", nullptr));
        send_btn->setText(QCoreApplication::translate("ChatDialog", "\345\217\221\351\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatDialog: public Ui_ChatDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATDIALOG_H
