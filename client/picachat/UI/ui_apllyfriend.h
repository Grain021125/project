/********************************************************************************
** Form generated from reading UI file 'apllyfriend.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APLLYFRIEND_H
#define UI_APLLYFRIEND_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <customizeedit.h>
#include "clickedbtn.h"

QT_BEGIN_NAMESPACE

class Ui_ApllyFriend
{
public:
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollcontent;
    QVBoxLayout *verticalLayout_2;
    QLabel *apply_lab;
    QWidget *apply_wid;
    QVBoxLayout *verticalLayout_3;
    QFrame *line;
    QLabel *message_lab;
    CustomizeEdit *name_edit;
    QLabel *back_lab;
    CustomizeEdit *back_edit;
    QLabel *label_lab;
    QWidget *lab_group_wid;
    QSpacerItem *verticalSpacer;
    QWidget *apply_sure_wid;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    ClickedBtn *sure_button;
    QSpacerItem *horizontalSpacer;
    ClickedBtn *cancel_button;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QDialog *ApllyFriend)
    {
        if (ApllyFriend->objectName().isEmpty())
            ApllyFriend->setObjectName("ApllyFriend");
        ApllyFriend->resize(361, 621);
        ApllyFriend->setMinimumSize(QSize(361, 621));
        ApllyFriend->setMaximumSize(QSize(361, 621));
        verticalLayout = new QVBoxLayout(ApllyFriend);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(ApllyFriend);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setMinimumSize(QSize(0, 500));
        scrollArea->setWidgetResizable(true);
        scrollcontent = new QWidget();
        scrollcontent->setObjectName("scrollcontent");
        scrollcontent->setGeometry(QRect(0, 0, 359, 498));
        verticalLayout_2 = new QVBoxLayout(scrollcontent);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, -1, 0, -1);
        apply_lab = new QLabel(scrollcontent);
        apply_lab->setObjectName("apply_lab");
        apply_lab->setMinimumSize(QSize(0, 25));
        apply_lab->setMaximumSize(QSize(16777215, 25));
        apply_lab->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(apply_lab);

        apply_wid = new QWidget(scrollcontent);
        apply_wid->setObjectName("apply_wid");
        verticalLayout_3 = new QVBoxLayout(apply_wid);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, -1, 0, -1);
        line = new QFrame(apply_wid);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_3->addWidget(line);

        message_lab = new QLabel(apply_wid);
        message_lab->setObjectName("message_lab");
        message_lab->setMaximumSize(QSize(16777215, 30));

        verticalLayout_3->addWidget(message_lab);

        name_edit = new CustomizeEdit(apply_wid);
        name_edit->setObjectName("name_edit");
        name_edit->setMinimumSize(QSize(0, 35));
        name_edit->setMaximumSize(QSize(16777215, 35));

        verticalLayout_3->addWidget(name_edit);

        back_lab = new QLabel(apply_wid);
        back_lab->setObjectName("back_lab");
        back_lab->setMaximumSize(QSize(16777215, 30));

        verticalLayout_3->addWidget(back_lab);

        back_edit = new CustomizeEdit(apply_wid);
        back_edit->setObjectName("back_edit");
        back_edit->setMinimumSize(QSize(0, 35));
        back_edit->setMaximumSize(QSize(16777215, 35));

        verticalLayout_3->addWidget(back_edit);

        label_lab = new QLabel(apply_wid);
        label_lab->setObjectName("label_lab");
        label_lab->setMaximumSize(QSize(16777215, 30));

        verticalLayout_3->addWidget(label_lab);

        lab_group_wid = new QWidget(apply_wid);
        lab_group_wid->setObjectName("lab_group_wid");

        verticalLayout_3->addWidget(lab_group_wid);


        verticalLayout_2->addWidget(apply_wid);

        scrollArea->setWidget(scrollcontent);

        verticalLayout->addWidget(scrollArea);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        apply_sure_wid = new QWidget(ApllyFriend);
        apply_sure_wid->setObjectName("apply_sure_wid");
        apply_sure_wid->setMinimumSize(QSize(0, 50));
        horizontalLayout = new QHBoxLayout(apply_sure_wid);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        sure_button = new ClickedBtn(apply_sure_wid);
        sure_button->setObjectName("sure_button");
        sure_button->setMinimumSize(QSize(100, 30));

        horizontalLayout->addWidget(sure_button);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        cancel_button = new ClickedBtn(apply_sure_wid);
        cancel_button->setObjectName("cancel_button");
        cancel_button->setMinimumSize(QSize(100, 30));

        horizontalLayout->addWidget(cancel_button);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addWidget(apply_sure_wid);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        retranslateUi(ApllyFriend);

        QMetaObject::connectSlotsByName(ApllyFriend);
    } // setupUi

    void retranslateUi(QDialog *ApllyFriend)
    {
        ApllyFriend->setWindowTitle(QCoreApplication::translate("ApllyFriend", "Dialog", nullptr));
        apply_lab->setText(QCoreApplication::translate("ApllyFriend", "\347\224\263\350\257\267\346\267\273\345\212\240\345\245\275\345\217\213", nullptr));
        message_lab->setText(QCoreApplication::translate("ApllyFriend", "\345\217\221\351\200\201\346\267\273\345\212\240\346\234\213\345\217\213\347\224\263\350\257\267:", nullptr));
        back_lab->setText(QCoreApplication::translate("ApllyFriend", "\345\244\207\346\263\250\345\220\215:", nullptr));
        label_lab->setText(QCoreApplication::translate("ApllyFriend", "\346\240\207\347\255\276", nullptr));
        sure_button->setText(QCoreApplication::translate("ApllyFriend", "\347\241\256\350\256\244", nullptr));
        cancel_button->setText(QCoreApplication::translate("ApllyFriend", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ApllyFriend: public Ui_ApllyFriend {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APLLYFRIEND_H
