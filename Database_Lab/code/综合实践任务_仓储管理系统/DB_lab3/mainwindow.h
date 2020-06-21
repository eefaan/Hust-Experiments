#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QMessageBox>

// control pages
#include "buyer_mw.h"
#include "auditor_mw.h"
#include "seller_mw.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    buyer_mw *buyer_page;
    auditor_mw *auditor_page;
    seller_mw *seller_page;
    QMessageBox *msgBox;

public:
    int sno;// users' ID
    int stype;// users'type: 1:buyer, 2:seller, 3:auditor
    void link();
    void TCPwrite(QString str);
    void TCPread();

    void proc_response_login(QString response);

signals:
    void dataReceived(QByteArray);

public slots:
    void on_loginin_clicked();
    void func_switch(QByteArray);
// repost buyer's request
    void buyer_logout();
    void buyer_flash();
    void buyer_gflash();
    void buyer_submit(QString request);
// repost seller's request
    void seller_logout();
    void seller_flash();
    void seller_gflash();
    void seller_submit(QString request);
// repost auditor's request
    void auditor_logout();
    void auditor_poflash();
    void auditor_posubmit(QString request);
    void auditor_soflash();
    void auditor_sosubmit(QString request);
    void auditor_gflash();

private:
    QTcpSocket *tcpSocket;    //客户端连接套接字
    QString package_cache;
    QString choice_cache;
};

#endif // MAINWINDOW_H
