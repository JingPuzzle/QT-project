#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "expl.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    //绘图事件
    void paintEvent(QPaintEvent *);
    void getDir();
    ExpL *my_expL = new ExpL();
private:
    Ui::Widget *ui;
    string str; //读入源代码的字符串
};
#endif // WIDGET_H
