#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow x;
    MainWindow y;
    MainWindow z;
    x.set_count();
    y.set_loop();
    z.set_time();
    x.show();
    y.show();
    z.show();

    return a.exec();
}
