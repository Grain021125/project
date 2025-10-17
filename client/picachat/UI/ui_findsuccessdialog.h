/********************************************************************************
** Form generated from reading UI file 'findsuccessdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINDSUCCESSDIALOG_H
#define UI_FINDSUCCESSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "clickedbtn.h"

QT_BEGIN_NAMESPACE

class Ui_FindSuccessDialog
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *head_lab;
    QLabel *name_lab;
    QSpacerItem *horizontal;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    ClickedBtn *add_friend_button;

    void setupUi(QDialog *FindSuccessDialog)
    {
        if (FindSuccessDialog->objectName().isEmpty())
            FindSuccessDialog->setObjectName("FindSuccessDialog");
        FindSuccessDialog->resize(280, 190);
        FindSuccessDialog->setMinimumSize(QSize(280, 190));
        FindSuccessDialog->setMaximumSize(QSize(280, 190));
        verticalLayout = new QVBoxLayout(FindSuccessDialog);
        verticalLayout->setObjectName("verticalLayout");
        widget = new QWidget(FindSuccessDialog);
        widget->setObjectName("widget");
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        head_lab = new QLabel(widget);
        head_lab->setObjectName("head_lab");
        head_lab->setMinimumSize(QSize(50, 50));
        head_lab->setMaximumSize(QSize(50, 50));

        horizontalLayout->addWidget(head_lab);

        name_lab = new QLabel(widget);
        name_lab->setObjectName("name_lab");

        horizontalLayout->addWidget(name_lab);

        horizontal = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontal);


        verticalLayout->addWidget(widget);

        widget_2 = new QWidget(FindSuccessDialog);
        widget_2->setObjectName("widget_2");
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        add_friend_button = new ClickedBtn(widget_2);
        add_friend_button->setObjectName("add_friend_button");
        add_friend_button->setMinimumSize(QSize(120, 35));
        add_friend_button->setMaximumSize(QSize(120, 35));

        horizontalLayout_2->addWidget(add_friend_button);


        verticalLayout->addWidget(widget_2);


        retranslateUi(FindSuccessDialog);

        QMetaObject::connectSlotsByName(FindSuccessDialog);
    } // setupUi

    void retranslateUi(QDialog *FindSuccessDialog)
    {
        FindSuccessDialog->setWindowTitle(QCoreApplication::translate("FindSuccessDialog", "Dialog", nullptr));
        head_lab->setText(QString());
        name_lab->setText(QCoreApplication::translate("FindSuccessDialog", "TextLabel", nullptr));
        add_friend_button->setText(QCoreApplication::translate("FindSuccessDialog", "\346\267\273\345\212\240\345\210\260\351\200\232\350\256\257\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FindSuccessDialog: public Ui_FindSuccessDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINDSUCCESSDIALOG_H
