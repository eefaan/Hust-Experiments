#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include "topview.h"
#include "calcu_usage_cpu.h"
#include "calcu_usage_memory.h"
#include <QDir>
#include <QString>
#include <QTimer>
#include <QProcess>
#include <time.h>
#include <unistd.h>
//#include <linux/reboot.h>

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



public:
    int cell_row;
    int cell_column;
    QString hostname_file;
    QString uptime_file;
    QString ostype_file;
    QString osrelease_file;
    QString cpuinfo_file;
    QString stat_file;
    QString meminfo_file;

signals:
    void sys_info(int num, QString Msg);

public slots:
    void shut();
    void reboot();
    void send_signals();
    void set_sys_info(int row_num, QString Msg);
    void set_status_time();
    void set_status_cpu_usage();
    void set_status_memory_usage();
    void set_process_list();
    void process_shut();
    void process_creat();
    void search_pid(QString text);
};

#endif // MAINWINDOW_H
