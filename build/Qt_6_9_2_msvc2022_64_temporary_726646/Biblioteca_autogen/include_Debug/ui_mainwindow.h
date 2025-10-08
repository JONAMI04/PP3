/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label_6;
    QLabel *totalRevistas;
    QPushButton *botonMaterial;
    QLabel *librosPrestados;
    QLabel *label;
    QLabel *totalLibros;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_2;
    QLabel *revistasPrestadas;
    QLabel *totalTesis;
    QLabel *label_7;
    QLabel *label_3;
    QLabel *tesisPrestadas;
    QLabel *usuariosRegistrados;
    QPushButton *botonUsuarios;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(823, 633);
        MainWindow->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    qproperty-flat: false;                 /* evita aspecto plano/transparente */\n"
"    qproperty-autoFillBackground: true;    /* fuerza pintado del fondo */\n"
"    background-color: #e0e0e0;             /* pon\303\251 el color que quieras */\n"
"    color: #222;\n"
"    border: 1px solid #8f8f91;\n"
"    border-radius: 6px;\n"
"    padding: 6px 12px;\n"
"}\n"
"QPushButton:hover { background-color: #dcdcdc; }\n"
"QPushButton:pressed, QPushButton:checked { background-color: #c8c8c8; }"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8("#centralwidget {\n"
"    border-image: url(:/img/fondo.png) 0 0 0 0 stretch stretch;\n"
"}\n"
"#centralwidget QLabel {\n"
"    color: #00ff00;            /* eleg\303\255 el color */\n"
"}\n"
"#centralwidget QLabel {\n"
"    background-color: rgba(255, 235, 59, 190); /* #FFEB3B con ~75% opacidad */\n"
"    color: #212121;                            /* texto oscuro para contraste */\n"
"    border: 1px solid rgba(0,0,0,60);\n"
"    border-radius: 6px;\n"
"    padding: 2px 6px;\n"
"}"));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(570, 240, 200, 55));
        QFont font;
        font.setFamilies({QString::fromUtf8("Times New Roman")});
        font.setPointSize(14);
        font.setBold(true);
        label_6->setFont(font);
        label_6->setAlignment(Qt::AlignmentFlag::AlignCenter);
        totalRevistas = new QLabel(centralwidget);
        totalRevistas->setObjectName("totalRevistas");
        totalRevistas->setGeometry(QRect(370, 190, 80, 40));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Times New Roman")});
        font1.setPointSize(12);
        totalRevistas->setFont(font1);
        totalRevistas->setAlignment(Qt::AlignmentFlag::AlignCenter);
        botonMaterial = new QPushButton(centralwidget);
        botonMaterial->setObjectName("botonMaterial");
        botonMaterial->setGeometry(QRect(40, 390, 100, 100));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Times New Roman")});
        font2.setPointSize(11);
        font2.setBold(false);
        botonMaterial->setFont(font2);
        botonMaterial->setAutoFillBackground(false);
        botonMaterial->setFlat(false);
        librosPrestados = new QLabel(centralwidget);
        librosPrestados->setObjectName("librosPrestados");
        librosPrestados->setGeometry(QRect(110, 300, 80, 40));
        librosPrestados->setFont(font1);
        librosPrestados->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(60, 130, 181, 55));
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8(""));
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        totalLibros = new QLabel(centralwidget);
        totalLibros->setObjectName("totalLibros");
        totalLibros->setGeometry(QRect(110, 190, 80, 40));
        totalLibros->setFont(font1);
        totalLibros->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(310, 240, 200, 55));
        label_4->setFont(font);
        label_4->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(320, 130, 181, 55));
        label_5->setFont(font);
        label_5->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(50, 240, 200, 55));
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);
        revistasPrestadas = new QLabel(centralwidget);
        revistasPrestadas->setObjectName("revistasPrestadas");
        revistasPrestadas->setGeometry(QRect(370, 300, 80, 40));
        revistasPrestadas->setFont(font1);
        revistasPrestadas->setAlignment(Qt::AlignmentFlag::AlignCenter);
        totalTesis = new QLabel(centralwidget);
        totalTesis->setObjectName("totalTesis");
        totalTesis->setGeometry(QRect(630, 190, 80, 40));
        totalTesis->setFont(font1);
        totalTesis->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(580, 130, 181, 55));
        label_7->setFont(font);
        label_7->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(430, 390, 251, 51));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Times New Roman")});
        font3.setPointSize(15);
        font3.setBold(true);
        label_3->setFont(font3);
        label_3->setAlignment(Qt::AlignmentFlag::AlignCenter);
        tesisPrestadas = new QLabel(centralwidget);
        tesisPrestadas->setObjectName("tesisPrestadas");
        tesisPrestadas->setGeometry(QRect(630, 300, 80, 40));
        tesisPrestadas->setFont(font1);
        tesisPrestadas->setAlignment(Qt::AlignmentFlag::AlignCenter);
        usuariosRegistrados = new QLabel(centralwidget);
        usuariosRegistrados->setObjectName("usuariosRegistrados");
        usuariosRegistrados->setGeometry(QRect(520, 450, 80, 40));
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Times New Roman")});
        font4.setPointSize(13);
        usuariosRegistrados->setFont(font4);
        usuariosRegistrados->setAlignment(Qt::AlignmentFlag::AlignCenter);
        botonUsuarios = new QPushButton(centralwidget);
        botonUsuarios->setObjectName("botonUsuarios");
        botonUsuarios->setGeometry(QRect(160, 390, 100, 100));
        botonUsuarios->setFont(font2);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Gestor de Biblioteca", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Tesis Prestadas", nullptr));
        totalRevistas->setText(QString());
        botonMaterial->setText(QCoreApplication::translate("MainWindow", "Material", nullptr));
#if QT_CONFIG(shortcut)
        botonMaterial->setShortcut(QString());
#endif // QT_CONFIG(shortcut)
        librosPrestados->setText(QString());
        label->setText(QCoreApplication::translate("MainWindow", "Total de Libros", nullptr));
        totalLibros->setText(QString());
        label_4->setText(QCoreApplication::translate("MainWindow", "Revistas Prestadas", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Total de Revistas", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Libros Prestados", nullptr));
        revistasPrestadas->setText(QString());
        totalTesis->setText(QString());
        label_7->setText(QCoreApplication::translate("MainWindow", "Total de Tesis", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Usuarios Registrados", nullptr));
        tesisPrestadas->setText(QString());
        usuariosRegistrados->setText(QString());
        botonUsuarios->setText(QCoreApplication::translate("MainWindow", "Usuarios", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
