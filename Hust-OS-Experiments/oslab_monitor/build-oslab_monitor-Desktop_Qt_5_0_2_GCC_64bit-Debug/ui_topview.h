/********************************************************************************
** Form generated from reading UI file 'topview.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOPVIEW_H
#define UI_TOPVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_topview
{
public:

    void setupUi(QWidget *topview)
    {
        if (topview->objectName().isEmpty())
            topview->setObjectName(QStringLiteral("topview"));
        topview->resize(400, 300);

        retranslateUi(topview);

        QMetaObject::connectSlotsByName(topview);
    } // setupUi

    void retranslateUi(QWidget *topview)
    {
        topview->setWindowTitle(QApplication::translate("topview", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class topview: public Ui_topview {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOPVIEW_H
