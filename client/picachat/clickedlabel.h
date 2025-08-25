#ifndef CLICKEDLABEL_H
#define CLICKEDLABEL_H
#include <QLabel>
#include "global.h"

class ClickedLabel:public QLabel
{
    Q_OBJECT
public:
    ClickedLabel(QWidget* parent);
    virtual void mousePressEvent(QMouseEvent *ev) override;
    virtual void mouseReleaseEvent(QMouseEvent *ev) override;
    virtual void enterEvent(QEnterEvent* event) override;
    virtual void leaveEvent(QEvent* event) override;
    void SetState(QString normal="normal", QString hover="hover", QString press="press",
                  QString select="select", QString select_hover="select_hover", QString select_press="select_press");

    ClickLbState GetCurState();
    bool SetCurState(ClickLbState state);
    void ResetNormalState();
protected:

private:
    QString _normal;
    QString _normal_hover;
    QString _normal_press;

    QString _selected;
    QString _selected_hover;
    QString _selected_press;

    ClickLbState _curstate;
signals:
    void clicked(QString, ClickLbState);

};

#endif // CLICKEDLABEL_H
