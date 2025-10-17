#ifndef APLLYFRIEND_H
#define APLLYFRIEND_H

#include <QDialog>
#include "friendlabel.h"
#include "userdata.h"

namespace Ui {
class ApllyFriend;
}

class ApllyFriend : public QDialog
{
    Q_OBJECT

public:
    explicit ApllyFriend(QWidget *parent = nullptr);
    ~ApllyFriend();

private:
    Ui::ApllyFriend *ui;
};

#endif // APLLYFRIEND_H
