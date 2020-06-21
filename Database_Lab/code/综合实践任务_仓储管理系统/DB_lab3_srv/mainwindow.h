#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSignalMapper>
#include <QDebug>
//#include <QPluginLoader>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QDateTime>
#include <QThread>

const int para_num = 10;

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

// db setting
private:
    QSqlDatabase db;
    QString db_ip;
    int db_port;
    QString db_name;
    QString db_account;
    QString db_password;
    QSqlQuery *query;
    QSqlQuery *query_temp;

public slots:
    void start_conn();
    void stop_conn();
    void export_db();
    void func_switch(int cur);

public:
    void server_write(QString str, int i);
    void l_login(int i);
//    void l_register();
    void b_flash(int i);
    void b_submit(int i);

    void s_flash(int i);
    void s_submit(int i);

    void g_flash(int i);

    void a_poflash(int i);
    void a_posubmit(int i);
    void a_soflash(int i);
    void a_sosubmit(int i);
    QSignalMapper * myMapper;


private:
    QTcpServer *tcpServer;        //这个是用来监听的服务器套接字
    int cur;    //服务套接字组的下标
    QTcpSocket *tcpSocket[para_num];        //实际用来连接的服务器套接字
    QString choice[para_num];                        //以下是杂类，用来放一些缓存和解包
    QString Bag[para_num];
    QString section1[para_num];
    QString section2[para_num];
    QString section3[para_num];
    QString section4[para_num];
    QString section5[para_num];

};

#endif // MAINWINDOW_H
