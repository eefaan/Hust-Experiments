/********************************************************************************
** Form generated from reading UI file 'auditor_mw.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUDITOR_MW_H
#define UI_AUDITOR_MW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_auditor_mw
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QTableWidget *potable;
    QPushButton *poflash;
    QPushButton *posubmit;
    QWidget *tab_2;
    QPushButton *soflash;
    QTableWidget *sotable;
    QPushButton *sosubmit;
    QWidget *tab_3;
    QTableWidget *gtable;
    QPushButton *gflash;
    QPushButton *logout;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *auditor_mw)
    {
        if (auditor_mw->objectName().isEmpty())
            auditor_mw->setObjectName(QStringLiteral("auditor_mw"));
        auditor_mw->resize(800, 600);
        centralwidget = new QWidget(auditor_mw);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(20, 20, 721, 491));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        potable = new QTableWidget(tab);
        potable->setObjectName(QStringLiteral("potable"));
        potable->setGeometry(QRect(10, 10, 681, 401));
        poflash = new QPushButton(tab);
        poflash->setObjectName(QStringLiteral("poflash"));
        poflash->setGeometry(QRect(570, 420, 111, 32));
        posubmit = new QPushButton(tab);
        posubmit->setObjectName(QStringLiteral("posubmit"));
        posubmit->setGeometry(QRect(430, 420, 111, 32));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        soflash = new QPushButton(tab_2);
        soflash->setObjectName(QStringLiteral("soflash"));
        soflash->setGeometry(QRect(570, 420, 111, 32));
        sotable = new QTableWidget(tab_2);
        sotable->setObjectName(QStringLiteral("sotable"));
        sotable->setGeometry(QRect(10, 10, 681, 401));
        sosubmit = new QPushButton(tab_2);
        sosubmit->setObjectName(QStringLiteral("sosubmit"));
        sosubmit->setGeometry(QRect(430, 420, 111, 32));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        gtable = new QTableWidget(tab_3);
        gtable->setObjectName(QStringLiteral("gtable"));
        gtable->setGeometry(QRect(10, 0, 691, 431));
        gflash = new QPushButton(tab_3);
        gflash->setObjectName(QStringLiteral("gflash"));
        gflash->setGeometry(QRect(570, 430, 111, 32));
        tabWidget->addTab(tab_3, QString());
        logout = new QPushButton(centralwidget);
        logout->setObjectName(QStringLiteral("logout"));
        logout->setGeometry(QRect(591, 511, 111, 32));
        auditor_mw->setCentralWidget(centralwidget);
        menubar = new QMenuBar(auditor_mw);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        auditor_mw->setMenuBar(menubar);
        statusbar = new QStatusBar(auditor_mw);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        auditor_mw->setStatusBar(statusbar);

        retranslateUi(auditor_mw);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(auditor_mw);
    } // setupUi

    void retranslateUi(QMainWindow *auditor_mw)
    {
        auditor_mw->setWindowTitle(QApplication::translate("auditor_mw", "MainWindow", Q_NULLPTR));
        poflash->setText(QApplication::translate("auditor_mw", "flash", Q_NULLPTR));
        posubmit->setText(QApplication::translate("auditor_mw", "\346\211\271\345\207\206", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("auditor_mw", "\351\207\207\350\264\255\347\224\263\350\257\267", Q_NULLPTR));
        soflash->setText(QApplication::translate("auditor_mw", "flash", Q_NULLPTR));
        sosubmit->setText(QApplication::translate("auditor_mw", "\346\211\271\345\207\206", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("auditor_mw", "\345\207\272\345\272\223\347\224\263\350\257\267", Q_NULLPTR));
        gflash->setText(QApplication::translate("auditor_mw", "flash", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("auditor_mw", "\344\273\223\345\272\223\350\264\247\345\223\201", Q_NULLPTR));
        logout->setText(QApplication::translate("auditor_mw", "logout", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class auditor_mw: public Ui_auditor_mw {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUDITOR_MW_H
