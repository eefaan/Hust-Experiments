/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QTableWidget *tableWidget;
    QWidget *tab_2;
    QTableWidget *table_proc;
    QLabel *label_pNum;
    QLabel *label_pRun;
    QLabel *label_pSleep;
    QPushButton *proc_creat;
    QPushButton *proc_shut;
    QLabel *label_pZombie;
    QLineEdit *Edit_pid;
    QLabel *label_4;
    QWidget *tab_3;
    QCustomPlot *widget_cpu;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QCustomPlot *widget_mem;
    QCustomPlot *widget_swap;
    QLabel *label_now;
    QLabel *label_cpu;
    QLabel *label_memory;
    QPushButton *button_shut;
    QPushButton *button_reboot;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(721, 560);
        MainWindow->setAutoFillBackground(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setEnabled(true);
        centralWidget->setMouseTracking(true);
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setEnabled(true);
        tabWidget->setGeometry(QRect(0, 0, 721, 461));
        tabWidget->setMouseTracking(true);
        tabWidget->setLayoutDirection(Qt::LeftToRight);
        tabWidget->setAutoFillBackground(false);
        tabWidget->setElideMode(Qt::ElideNone);
        tabWidget->setUsesScrollButtons(false);
        tabWidget->setDocumentMode(false);
        tabWidget->setTabsClosable(false);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        tab->setMouseTracking(true);
        tableWidget = new QTableWidget(tab);
        if (tableWidget->columnCount() < 1)
            tableWidget->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        if (tableWidget->rowCount() < 6)
            tableWidget->setRowCount(6);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(4, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(5, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setItem(0, 0, __qtablewidgetitem7);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(0, 0, 721, 431));
        tableWidget->setMaximumSize(QSize(1000, 431));
        tableWidget->setSizeIncrement(QSize(0, 0));
        tableWidget->setMouseTracking(true);
        tableWidget->setContextMenuPolicy(Qt::DefaultContextMenu);
        tableWidget->setLayoutDirection(Qt::LeftToRight);
        tableWidget->setAutoFillBackground(true);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tab_2->setMouseTracking(true);
        table_proc = new QTableWidget(tab_2);
        if (table_proc->columnCount() < 5)
            table_proc->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        table_proc->setHorizontalHeaderItem(0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        table_proc->setHorizontalHeaderItem(1, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        table_proc->setHorizontalHeaderItem(2, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        table_proc->setHorizontalHeaderItem(3, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        table_proc->setHorizontalHeaderItem(4, __qtablewidgetitem12);
        table_proc->setObjectName(QStringLiteral("table_proc"));
        table_proc->setGeometry(QRect(0, 0, 581, 431));
        label_pNum = new QLabel(tab_2);
        label_pNum->setObjectName(QStringLiteral("label_pNum"));
        label_pNum->setGeometry(QRect(590, 130, 111, 16));
        label_pRun = new QLabel(tab_2);
        label_pRun->setObjectName(QStringLiteral("label_pRun"));
        label_pRun->setGeometry(QRect(590, 170, 111, 16));
        label_pSleep = new QLabel(tab_2);
        label_pSleep->setObjectName(QStringLiteral("label_pSleep"));
        label_pSleep->setGeometry(QRect(590, 210, 111, 16));
        proc_creat = new QPushButton(tab_2);
        proc_creat->setObjectName(QStringLiteral("proc_creat"));
        proc_creat->setGeometry(QRect(590, 370, 121, 32));
        proc_shut = new QPushButton(tab_2);
        proc_shut->setObjectName(QStringLiteral("proc_shut"));
        proc_shut->setGeometry(QRect(590, 400, 121, 32));
        label_pZombie = new QLabel(tab_2);
        label_pZombie->setObjectName(QStringLiteral("label_pZombie"));
        label_pZombie->setGeometry(QRect(590, 250, 111, 16));
        Edit_pid = new QLineEdit(tab_2);
        Edit_pid->setObjectName(QStringLiteral("Edit_pid"));
        Edit_pid->setGeometry(QRect(600, 330, 101, 21));
        label_4 = new QLabel(tab_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(590, 300, 76, 19));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        widget_cpu = new QCustomPlot(tab_3);
        widget_cpu->setObjectName(QStringLiteral("widget_cpu"));
        widget_cpu->setGeometry(QRect(10, 30, 691, 121));
        label = new QLabel(tab_3);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 111, 16));
        label_2 = new QLabel(tab_3);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 150, 111, 16));
        label_3 = new QLabel(tab_3);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 290, 111, 16));
        widget_mem = new QCustomPlot(tab_3);
        widget_mem->setObjectName(QStringLiteral("widget_mem"));
        widget_mem->setGeometry(QRect(10, 170, 691, 121));
        widget_swap = new QCustomPlot(tab_3);
        widget_swap->setObjectName(QStringLiteral("widget_swap"));
        widget_swap->setGeometry(QRect(10, 310, 691, 121));
        tabWidget->addTab(tab_3, QString());
        label_now = new QLabel(centralWidget);
        label_now->setObjectName(QStringLiteral("label_now"));
        label_now->setGeometry(QRect(0, 460, 591, 16));
        label_cpu = new QLabel(centralWidget);
        label_cpu->setObjectName(QStringLiteral("label_cpu"));
        label_cpu->setGeometry(QRect(0, 480, 591, 16));
        label_memory = new QLabel(centralWidget);
        label_memory->setObjectName(QStringLiteral("label_memory"));
        label_memory->setGeometry(QRect(0, 500, 591, 16));
        button_shut = new QPushButton(centralWidget);
        button_shut->setObjectName(QStringLiteral("button_shut"));
        button_shut->setGeometry(QRect(600, 490, 111, 32));
        button_reboot = new QPushButton(centralWidget);
        button_reboot->setObjectName(QStringLiteral("button_reboot"));
        button_reboot->setGeometry(QRect(600, 460, 111, 32));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 721, 24));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        statusBar->setEnabled(true);
        statusBar->setAutoFillBackground(false);
        statusBar->setSizeGripEnabled(true);
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "content", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "PC name", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "launch time", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "running time", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "system version", 0));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->verticalHeaderItem(4);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "CPU type", 0));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->verticalHeaderItem(5);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "CPU HZ", 0));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        tableWidget->setSortingEnabled(__sortingEnabled);

        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "TopView", 0));
        QTableWidgetItem *___qtablewidgetitem7 = table_proc->horizontalHeaderItem(0);
        ___qtablewidgetitem7->setText(QApplication::translate("MainWindow", "PID", 0));
        QTableWidgetItem *___qtablewidgetitem8 = table_proc->horizontalHeaderItem(1);
        ___qtablewidgetitem8->setText(QApplication::translate("MainWindow", "name", 0));
        QTableWidgetItem *___qtablewidgetitem9 = table_proc->horizontalHeaderItem(2);
        ___qtablewidgetitem9->setText(QApplication::translate("MainWindow", "status", 0));
        QTableWidgetItem *___qtablewidgetitem10 = table_proc->horizontalHeaderItem(3);
        ___qtablewidgetitem10->setText(QApplication::translate("MainWindow", "pre", 0));
        QTableWidgetItem *___qtablewidgetitem11 = table_proc->horizontalHeaderItem(4);
        ___qtablewidgetitem11->setText(QApplication::translate("MainWindow", "memUsed", 0));
        label_pNum->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        label_pRun->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        label_pSleep->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        proc_creat->setText(QApplication::translate("MainWindow", "create proc", 0));
        proc_shut->setText(QApplication::translate("MainWindow", "shut proc", 0));
        label_pZombie->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        label_4->setText(QApplication::translate("MainWindow", "Search:", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Process", 0));
        label->setText(QApplication::translate("MainWindow", "CPU Usage:", 0));
        label_2->setText(QApplication::translate("MainWindow", "Memory Usage:", 0));
        label_3->setText(QApplication::translate("MainWindow", "Swap Usage:", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "Graph", 0));
        label_now->setText(QApplication::translate("MainWindow", "TIME", 0));
        label_cpu->setText(QApplication::translate("MainWindow", "CPU_USAGE", 0));
        label_memory->setText(QApplication::translate("MainWindow", "MEM_USAGE", 0));
        button_shut->setText(QApplication::translate("MainWindow", "shut", 0));
        button_reboot->setText(QApplication::translate("MainWindow", "reboot", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
