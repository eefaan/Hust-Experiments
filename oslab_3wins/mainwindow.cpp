#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QTimer>
#include <QString>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    i(0),
    sum(0),
    loop_n(0)
{    
    ui->setupUi(this);
    mytimer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::set_count()
{
    connect(this->mytimer, SIGNAL(timeout()), this, SLOT(display_time()));
}

void MainWindow::set_time()
{
    connect(this->mytimer, SIGNAL(timeout()), this, SLOT(count_1_1000()));
}

void MainWindow::set_loop()
{
    connect(this->mytimer, SIGNAL(timeout()), this, SLOT(loop_0_9()));
}

void MainWindow::count_1_1000()
{
    QString str_sum;
    if(this->i<1000){
        this->i+=1;
        this->sum+=i;
    }
    str_sum.setNum(this->sum,10);
    ui->label->setText(str_sum);
}

void MainWindow::display_time()
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");
    qDebug()<<str;
    ui->label->setText(str);
}

void MainWindow::loop_0_9()
{
    QString str;
    if(this->loop_n<10){
        str.setNum(this->loop_n,10);
        qDebug()<<str;
        ui->label->setText(str);
        this->loop_n+=1;
    }
    if(this->loop_n==10){
        this->loop_n=0;
    }
}
