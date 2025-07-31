#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H
#include <QLabel>
#include <global.h>

enum ClickLbState{
    Normal = 0,
    Selected = 1
};

class ClickableLabel: public QLabel
{
    Q_OBJECT
public:
    explicit ClickableLabel(QWidget* parent = nullptr);

    virtual void mousePressEvent(QMouseEvent *ev) override;
    // virtual void leaveEvent(QEvent* event) override;
    void SetState(QString normal="", QString hover="", QString press="",
                  QString select="", QString select_hover="", QString select_press="");
    ClickLbState GetCurState();
    ~ClickableLabel();

private:
    QString _normal;
    QString _normal_hover;
    QString _normal_press;
    QString _selected;
    QString _selected_hover;
    QString _selected_press;
    ClickLbState _curstate;
signals:
    void clicked();  // 点击信号
};

#endif // CLICKABLELABEL_H
