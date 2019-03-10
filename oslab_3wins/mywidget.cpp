//hellowidget.cpp
#include "mywidget.h"

mywidget::mywidget(QWidget *parent) : QWidget(parent)
{
    resize(300, 200);
    m_labelInfo = new QLabel( tr("<h1>Hello Widget!</h1>"), this );
    m_labelInfo->setGeometry(10, 10, 200, 40);
}

mywidget::~mywidget()
{
    delete m_labelInfo; m_labelInfo = NULL;
}
