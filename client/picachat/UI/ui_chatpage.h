/********************************************************************************
** Form generated from reading UI file 'chatpage.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATPAGE_H
#define UI_CHATPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "clickedlabel.h"

QT_BEGIN_NAMESPACE

class Ui_ChatPage
{
public:
    QVBoxLayout *verticalLayout;
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
    ClickedLabel *emoj_lab;
    QSpacerItem *horizontalSpacer_3;
    ClickedLabel *file_lab;
    QSpacerItem *horizontalSpacer_4;
    QTextEdit *chatEdit;
    QWidget *send_wid;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *recv_btn;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *send_btn;
    QSpacerItem *horizontalSpacer_7;

    void setupUi(QWidget *ChatPage)
    {
        if (ChatPage->objectName().isEmpty())
            ChatPage->setObjectName("ChatPage");
        ChatPage->resize(421, 467);
        verticalLayout = new QVBoxLayout(ChatPage);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        chat_data_wid = new QWidget(ChatPage);
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
        horizontalLayout_3->setContentsMargins(11, 2, 2, 2);
        widget_2 = new QWidget(title_wid);
        widget_2->setObjectName("widget_2");
        verticalLayout_5 = new QVBoxLayout(widget_2);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(2, 2, 2, 2);
        title_lab = new QLabel(widget_2);
        title_lab->setObjectName("title_lab");
        title_lab->setMinimumSize(QSize(0, 0));
        QFont font;
        font.setBold(false);
        title_lab->setFont(font);
        title_lab->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

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

        emoj_lab = new ClickedLabel(tool_wid);
        emoj_lab->setObjectName("emoj_lab");
        emoj_lab->setMinimumSize(QSize(25, 25));
        emoj_lab->setMaximumSize(QSize(25, 25));

        horizontalLayout_4->addWidget(emoj_lab);

        horizontalSpacer_3 = new QSpacerItem(5, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        file_lab = new ClickedLabel(tool_wid);
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
        horizontalLayout_5->setSpacing(4);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(6, 6, 6, 6);
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


        verticalLayout->addWidget(chat_data_wid);


        retranslateUi(ChatPage);

        QMetaObject::connectSlotsByName(ChatPage);
    } // setupUi

    void retranslateUi(QWidget *ChatPage)
    {
        ChatPage->setWindowTitle(QCoreApplication::translate("ChatPage", "Form", nullptr));
        title_lab->setText(QCoreApplication::translate("ChatPage", "\350\260\267\351\233\250", nullptr));
        emoj_lab->setText(QString());
        file_lab->setText(QString());
        recv_btn->setText(QCoreApplication::translate("ChatPage", "\346\216\245\346\224\266", nullptr));
        send_btn->setText(QCoreApplication::translate("ChatPage", "\345\217\221\351\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatPage: public Ui_ChatPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATPAGE_H
