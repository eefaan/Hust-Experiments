#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>

class mywidget : public QWidget
{
    Q_OBJECT
public:
    explicit mywidget(QWidget *parent = 0);
    ~mywidget();
    //label
    QLabel *m_labelInfo;
};

#endif // MYWIDGET_H
