#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

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

public slots:
    void count_1_1000();
    void display_time();
    void loop_0_9();

public:
    QTimer *mytimer = new QTimer(this);
    void set_count();
    void set_time();
    void set_loop();
    int i;
    int sum;
    int loop_n;
};

#endif // MAINWINDOW_H
