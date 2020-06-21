/********************************************************************************
** Form generated from reading UI file 'buyer_mw.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUYER_MW_H
#define UI_BUYER_MW_H

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

QT_BEGIN_NAMESPACE

class Ui_buyer_mw
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QTableWidget *table;
    QPushButton *flash;
    QWidget *tab_2;
    QLabel *label;
    QLabel *label_2;
    QPushButton *submit;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *gname;
    QLineEdit *gplace;
    QLineEdit *gmanu;
    QLineEdit *gnum;
    QWidget *tab_3;
    QTableWidget *gtable;
    QPushButton *gflash;
    QPushButton *logout;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *buyer_mw)
    {
        if (buyer_mw->objectName().isEmpty())
            buyer_mw->setObjectName(QStringLiteral("buyer_mw"));
        buyer_mw->resize(800, 600);
        centralwidget = new QWidget(buyer_mw);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(29, 29, 721, 491));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        table = new QTableWidget(tab);
        table->setObjectName(QStringLiteral("table"));
        table->setGeometry(QRect(10, 10, 681, 401));
        flash = new QPushButton(tab);
        flash->setObjectName(QStringLiteral("flash"));
        flash->setGeometry(QRect(570, 420, 111, 32));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        label = new QLabel(tab_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(80, 60, 57, 16));
        label_2 = new QLabel(tab_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(80, 120, 81, 16));
        submit = new QPushButton(tab_2);
        submit->setObjectName(QStringLiteral("submit"));
        submit->setGeometry(QRect(570, 420, 111, 32));
        label_3 = new QLabel(tab_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(80, 190, 81, 16));
        label_4 = new QLabel(tab_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(80, 250, 81, 16));
        gname = new QLineEdit(tab_2);
        gname->setObjectName(QStringLiteral("gname"));
        gname->setGeometry(QRect(200, 60, 113, 21));
        gplace = new QLineEdit(tab_2);
        gplace->setObjectName(QStringLiteral("gplace"));
        gplace->setGeometry(QRect(200, 130, 113, 21));
        gmanu = new QLineEdit(tab_2);
        gmanu->setObjectName(QStringLiteral("gmanu"));
        gmanu->setGeometry(QRect(200, 190, 113, 21));
        gnum = new QLineEdit(tab_2);
        gnum->setObjectName(QStringLiteral("gnum"));
        gnum->setGeometry(QRect(210, 250, 113, 21));
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
        logout->setGeometry(QRect(600, 520, 111, 32));
        buyer_mw->setCentralWidget(centralwidget);
        menubar = new QMenuBar(buyer_mw);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        buyer_mw->setMenuBar(menubar);
        statusbar = new QStatusBar(buyer_mw);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        buyer_mw->setStatusBar(statusbar);

        retranslateUi(buyer_mw);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(buyer_mw);
    } // setupUi

    void retranslateUi(QMainWindow *buyer_mw)
    {
        buyer_mw->setWindowTitle(QApplication::translate("buyer_mw", "MainWindow", Q_NULLPTR));
        flash->setText(QApplication::translate("buyer_mw", "flash", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("buyer_mw", "\351\207\207\350\264\255\345\216\206\345\217\262", Q_NULLPTR));
        label->setText(QApplication::translate("buyer_mw", "\350\264\247\345\223\201\345\220\215", Q_NULLPTR));
        label_2->setText(QApplication::translate("buyer_mw", "\347\233\256\346\240\207\345\255\230\346\224\276\345\234\260", Q_NULLPTR));
        submit->setText(QApplication::translate("buyer_mw", "submit", Q_NULLPTR));
        label_3->setText(QApplication::translate("buyer_mw", "\345\216\202\345\256\266", Q_NULLPTR));
        label_4->setText(QApplication::translate("buyer_mw", "\350\277\233\350\264\247\351\207\217", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("buyer_mw", "\351\207\207\350\264\255\347\224\263\350\257\267", Q_NULLPTR));
        gflash->setText(QApplication::translate("buyer_mw", "flash", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("buyer_mw", "\344\273\223\345\272\223\350\264\247\345\223\201", Q_NULLPTR));
        logout->setText(QApplication::translate("buyer_mw", "logout", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class buyer_mw: public Ui_buyer_mw {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUYER_MW_H
