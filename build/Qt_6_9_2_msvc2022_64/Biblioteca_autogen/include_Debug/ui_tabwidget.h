/********************************************************************************
** Form generated from reading UI file 'tabwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABWIDGET_H
#define UI_TABWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QTabWidget>

QT_BEGIN_NAMESPACE

class Ui_TabWidget
{
public:

    void setupUi(QTabWidget *TabWidget)
    {
        if (TabWidget->objectName().isEmpty())
            TabWidget->setObjectName("TabWidget");
        TabWidget->resize(640, 480);

        retranslateUi(TabWidget);

        QMetaObject::connectSlotsByName(TabWidget);
    } // setupUi

    void retranslateUi(QTabWidget *TabWidget)
    {
        TabWidget->setWindowTitle(QCoreApplication::translate("TabWidget", "TabWidget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TabWidget: public Ui_TabWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABWIDGET_H
