/********************************************************************************
** Form generated from reading UI file 'material.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATERIAL_H
#define UI_MATERIAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Material
{
public:
    QWidget *centralwidget;

    void setupUi(QMainWindow *Material)
    {
        if (Material->objectName().isEmpty())
            Material->setObjectName("Material");
        Material->resize(823, 633);
        Material->setStyleSheet(QString::fromUtf8("#centralwidget {\n"
"    border-image: url(:/img/fondo.png) 0 0 0 0 stretch stretch;\n"
"}"));
        centralwidget = new QWidget(Material);
        centralwidget->setObjectName("centralwidget");
        Material->setCentralWidget(centralwidget);

        retranslateUi(Material);

        QMetaObject::connectSlotsByName(Material);
    } // setupUi

    void retranslateUi(QMainWindow *Material)
    {
        Material->setWindowTitle(QCoreApplication::translate("Material", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Material: public Ui_Material {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATERIAL_H
