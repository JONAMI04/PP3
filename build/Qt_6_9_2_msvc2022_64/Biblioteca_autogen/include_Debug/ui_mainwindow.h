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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *menu_principal;
    QPushButton *botonUsuarios;
    QLabel *label_5;
    QLabel *totalLibros;
    QLabel *usuariosRegistrados;
    QLabel *label_2;
    QLabel *revistasPrestadas;
    QLabel *label_6;
    QLabel *totalTesis;
    QLabel *tesisPrestadas;
    QLabel *totalRevistas;
    QPushButton *botonMaterial;
    QLabel *label_4;
    QLabel *label_3;
    QLabel *librosPrestados;
    QLabel *label;
    QLabel *label_7;
    QWidget *nuevo_material;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QLabel *label_9;
    QLineEdit *titulo;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_5;
    QLineEdit *lineEdit_6;
    QLineEdit *lineEdit_7;
    QWidget *usuario;
    QPushButton *botonNuevoMaterial_2;
    QLineEdit *lineEdit_2;
    QPushButton *botonUsuarios_3;
    QLabel *label_10;
    QTableView *tabla_material_2;
    QPushButton *pushButton_4;
    QWidget *page_2;
    QWidget *nuevo_usuario;
    QLabel *label_11;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QWidget *material;
    QPushButton *pushButton;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QTableView *tabla_material;
    QLabel *label_8;
    QLineEdit *lineEdit;
    QPushButton *botonUsuarios_2;
    QPushButton *botonNuevoMaterial;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(935, 654);
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
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(20, 10, 911, 641));
        menu_principal = new QWidget();
        menu_principal->setObjectName("menu_principal");
        botonUsuarios = new QPushButton(menu_principal);
        botonUsuarios->setObjectName("botonUsuarios");
        botonUsuarios->setGeometry(QRect(200, 410, 100, 100));
        QFont font;
        font.setFamilies({QString::fromUtf8("Times New Roman")});
        font.setPointSize(11);
        font.setBold(false);
        botonUsuarios->setFont(font);
        label_5 = new QLabel(menu_principal);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(360, 150, 181, 55));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Times New Roman")});
        font1.setPointSize(14);
        font1.setBold(true);
        label_5->setFont(font1);
        label_5->setAlignment(Qt::AlignmentFlag::AlignCenter);
        totalLibros = new QLabel(menu_principal);
        totalLibros->setObjectName("totalLibros");
        totalLibros->setGeometry(QRect(150, 210, 80, 40));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Times New Roman")});
        font2.setPointSize(12);
        totalLibros->setFont(font2);
        totalLibros->setAlignment(Qt::AlignmentFlag::AlignCenter);
        usuariosRegistrados = new QLabel(menu_principal);
        usuariosRegistrados->setObjectName("usuariosRegistrados");
        usuariosRegistrados->setGeometry(QRect(560, 470, 80, 40));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Times New Roman")});
        font3.setPointSize(13);
        usuariosRegistrados->setFont(font3);
        usuariosRegistrados->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_2 = new QLabel(menu_principal);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(90, 260, 200, 55));
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);
        revistasPrestadas = new QLabel(menu_principal);
        revistasPrestadas->setObjectName("revistasPrestadas");
        revistasPrestadas->setGeometry(QRect(410, 320, 80, 40));
        revistasPrestadas->setFont(font2);
        revistasPrestadas->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_6 = new QLabel(menu_principal);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(610, 260, 200, 55));
        label_6->setFont(font1);
        label_6->setAlignment(Qt::AlignmentFlag::AlignCenter);
        totalTesis = new QLabel(menu_principal);
        totalTesis->setObjectName("totalTesis");
        totalTesis->setGeometry(QRect(670, 210, 80, 40));
        totalTesis->setFont(font2);
        totalTesis->setAlignment(Qt::AlignmentFlag::AlignCenter);
        tesisPrestadas = new QLabel(menu_principal);
        tesisPrestadas->setObjectName("tesisPrestadas");
        tesisPrestadas->setGeometry(QRect(670, 320, 80, 40));
        tesisPrestadas->setFont(font2);
        tesisPrestadas->setAlignment(Qt::AlignmentFlag::AlignCenter);
        totalRevistas = new QLabel(menu_principal);
        totalRevistas->setObjectName("totalRevistas");
        totalRevistas->setGeometry(QRect(410, 210, 80, 40));
        totalRevistas->setFont(font2);
        totalRevistas->setAlignment(Qt::AlignmentFlag::AlignCenter);
        botonMaterial = new QPushButton(menu_principal);
        botonMaterial->setObjectName("botonMaterial");
        botonMaterial->setGeometry(QRect(80, 410, 100, 100));
        botonMaterial->setFont(font);
        botonMaterial->setAutoFillBackground(false);
        botonMaterial->setFlat(false);
        label_4 = new QLabel(menu_principal);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(350, 260, 200, 55));
        label_4->setFont(font1);
        label_4->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_3 = new QLabel(menu_principal);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(470, 410, 251, 51));
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Times New Roman")});
        font4.setPointSize(15);
        font4.setBold(true);
        label_3->setFont(font4);
        label_3->setAlignment(Qt::AlignmentFlag::AlignCenter);
        librosPrestados = new QLabel(menu_principal);
        librosPrestados->setObjectName("librosPrestados");
        librosPrestados->setGeometry(QRect(150, 320, 80, 40));
        librosPrestados->setFont(font2);
        librosPrestados->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label = new QLabel(menu_principal);
        label->setObjectName("label");
        label->setGeometry(QRect(100, 150, 181, 55));
        label->setFont(font1);
        label->setStyleSheet(QString::fromUtf8(""));
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_7 = new QLabel(menu_principal);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(620, 150, 181, 55));
        label_7->setFont(font1);
        label_7->setAlignment(Qt::AlignmentFlag::AlignCenter);
        stackedWidget->addWidget(menu_principal);
        nuevo_material = new QWidget();
        nuevo_material->setObjectName("nuevo_material");
        pushButton_2 = new QPushButton(nuevo_material);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(10, 600, 100, 30));
        pushButton_2->setMaximumSize(QSize(160, 160));
        QFont font5;
        font5.setFamilies({QString::fromUtf8("Times New Roman")});
        font5.setPointSize(11);
        pushButton_2->setFont(font5);
        pushButton_3 = new QPushButton(nuevo_material);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(130, 600, 150, 30));
        pushButton_3->setMaximumSize(QSize(160, 160));
        pushButton_3->setFont(font5);
        label_9 = new QLabel(nuevo_material);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(220, 40, 450, 60));
        QFont font6;
        font6.setFamilies({QString::fromUtf8("Times New Roman")});
        font6.setPointSize(28);
        font6.setBold(true);
        label_9->setFont(font6);
        label_9->setAlignment(Qt::AlignmentFlag::AlignCenter);
        titulo = new QLineEdit(nuevo_material);
        titulo->setObjectName("titulo");
        titulo->setGeometry(QRect(30, 170, 250, 41));
        titulo->setClearButtonEnabled(true);
        lineEdit_3 = new QLineEdit(nuevo_material);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setGeometry(QRect(30, 230, 250, 41));
        lineEdit_3->setClearButtonEnabled(true);
        lineEdit_4 = new QLineEdit(nuevo_material);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setGeometry(QRect(30, 290, 250, 41));
        lineEdit_4->setClearButtonEnabled(true);
        lineEdit_5 = new QLineEdit(nuevo_material);
        lineEdit_5->setObjectName("lineEdit_5");
        lineEdit_5->setGeometry(QRect(30, 350, 250, 41));
        lineEdit_5->setClearButtonEnabled(true);
        lineEdit_6 = new QLineEdit(nuevo_material);
        lineEdit_6->setObjectName("lineEdit_6");
        lineEdit_6->setGeometry(QRect(30, 410, 250, 41));
        lineEdit_6->setClearButtonEnabled(true);
        lineEdit_7 = new QLineEdit(nuevo_material);
        lineEdit_7->setObjectName("lineEdit_7");
        lineEdit_7->setGeometry(QRect(30, 470, 250, 41));
        lineEdit_7->setClearButtonEnabled(true);
        stackedWidget->addWidget(nuevo_material);
        usuario = new QWidget();
        usuario->setObjectName("usuario");
        botonNuevoMaterial_2 = new QPushButton(usuario);
        botonNuevoMaterial_2->setObjectName("botonNuevoMaterial_2");
        botonNuevoMaterial_2->setGeometry(QRect(570, 170, 331, 41));
        botonNuevoMaterial_2->setFont(font2);
        lineEdit_2 = new QLineEdit(usuario);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(30, 170, 371, 41));
        lineEdit_2->setClearButtonEnabled(true);
        botonUsuarios_3 = new QPushButton(usuario);
        botonUsuarios_3->setObjectName("botonUsuarios_3");
        botonUsuarios_3->setGeometry(QRect(410, 170, 150, 41));
        botonUsuarios_3->setFont(font2);
        label_10 = new QLabel(usuario);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(220, 40, 450, 60));
        label_10->setFont(font6);
        label_10->setAlignment(Qt::AlignmentFlag::AlignCenter);
        tabla_material_2 = new QTableView(usuario);
        tabla_material_2->setObjectName("tabla_material_2");
        tabla_material_2->setGeometry(QRect(30, 220, 869, 369));
        pushButton_4 = new QPushButton(usuario);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(30, 600, 100, 30));
        pushButton_4->setMaximumSize(QSize(160, 160));
        pushButton_4->setFont(font5);
        stackedWidget->addWidget(usuario);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidget->addWidget(page_2);
        nuevo_usuario = new QWidget();
        nuevo_usuario->setObjectName("nuevo_usuario");
        label_11 = new QLabel(nuevo_usuario);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(220, 40, 450, 60));
        label_11->setFont(font6);
        label_11->setAlignment(Qt::AlignmentFlag::AlignCenter);
        pushButton_5 = new QPushButton(nuevo_usuario);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(130, 600, 150, 30));
        pushButton_5->setMaximumSize(QSize(160, 160));
        pushButton_5->setFont(font5);
        pushButton_6 = new QPushButton(nuevo_usuario);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(10, 600, 100, 30));
        pushButton_6->setMaximumSize(QSize(160, 160));
        pushButton_6->setFont(font5);
        stackedWidget->addWidget(nuevo_usuario);
        material = new QWidget();
        material->setObjectName("material");
        pushButton = new QPushButton(material);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(10, 600, 100, 30));
        pushButton->setMaximumSize(QSize(160, 160));
        pushButton->setFont(font5);
        verticalLayoutWidget = new QWidget(material);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(10, 220, 871, 371));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tabla_material = new QTableView(verticalLayoutWidget);
        tabla_material->setObjectName("tabla_material");

        verticalLayout->addWidget(tabla_material);

        label_8 = new QLabel(material);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(220, 40, 450, 60));
        label_8->setFont(font6);
        label_8->setAlignment(Qt::AlignmentFlag::AlignCenter);
        lineEdit = new QLineEdit(material);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(10, 170, 371, 41));
        lineEdit->setClearButtonEnabled(true);
        botonUsuarios_2 = new QPushButton(material);
        botonUsuarios_2->setObjectName("botonUsuarios_2");
        botonUsuarios_2->setGeometry(QRect(390, 170, 150, 41));
        botonUsuarios_2->setFont(font2);
        botonNuevoMaterial = new QPushButton(material);
        botonNuevoMaterial->setObjectName("botonNuevoMaterial");
        botonNuevoMaterial->setGeometry(QRect(550, 170, 331, 41));
        botonNuevoMaterial->setFont(font2);
        stackedWidget->addWidget(material);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(5);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Gestor de Biblioteca", nullptr));
        botonUsuarios->setText(QCoreApplication::translate("MainWindow", "Usuarios", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Total de Revistas", nullptr));
        totalLibros->setText(QString());
        usuariosRegistrados->setText(QString());
        label_2->setText(QCoreApplication::translate("MainWindow", "Libros Prestados", nullptr));
        revistasPrestadas->setText(QString());
        label_6->setText(QCoreApplication::translate("MainWindow", "Tesis Prestadas", nullptr));
        totalTesis->setText(QString());
        tesisPrestadas->setText(QString());
        totalRevistas->setText(QString());
        botonMaterial->setText(QCoreApplication::translate("MainWindow", "Material", nullptr));
#if QT_CONFIG(shortcut)
        botonMaterial->setShortcut(QString());
#endif // QT_CONFIG(shortcut)
        label_4->setText(QCoreApplication::translate("MainWindow", "Revistas Prestadas", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Usuarios Registrados", nullptr));
        librosPrestados->setText(QString());
        label->setText(QCoreApplication::translate("MainWindow", "Total de Libros", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Total de Tesis", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Atr\303\240s", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Men\303\271 Principal", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Agregar Material", nullptr));
        titulo->setInputMask(QString());
        titulo->setText(QString());
        titulo->setPlaceholderText(QCoreApplication::translate("MainWindow", "Escribir titulo...", nullptr));
        lineEdit_3->setInputMask(QString());
        lineEdit_3->setText(QString());
        lineEdit_3->setPlaceholderText(QCoreApplication::translate("MainWindow", "Escribir editorial...", nullptr));
        lineEdit_4->setInputMask(QString());
        lineEdit_4->setText(QString());
        lineEdit_4->setPlaceholderText(QCoreApplication::translate("MainWindow", "Escribir a\303\261o...", nullptr));
        lineEdit_5->setInputMask(QString());
        lineEdit_5->setText(QString());
        lineEdit_5->setPlaceholderText(QCoreApplication::translate("MainWindow", "Escribir nombre del Autor...", nullptr));
        lineEdit_6->setInputMask(QString());
        lineEdit_6->setText(QString());
        lineEdit_6->setPlaceholderText(QCoreApplication::translate("MainWindow", "Escribir apellido del Autor...", nullptr));
        lineEdit_7->setInputMask(QString());
        lineEdit_7->setText(QString());
        lineEdit_7->setPlaceholderText(QCoreApplication::translate("MainWindow", "Escribir g\303\251nero...", nullptr));
        botonNuevoMaterial_2->setText(QCoreApplication::translate("MainWindow", "Agregar Nuevo Usuario", nullptr));
        lineEdit_2->setInputMask(QString());
        lineEdit_2->setText(QString());
        lineEdit_2->setPlaceholderText(QCoreApplication::translate("MainWindow", "Buscar por T\303\254tulo, Autor, C\303\262digo o Tipo...", nullptr));
        botonUsuarios_3->setText(QCoreApplication::translate("MainWindow", "Buscar", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Gesti\303\262n de Usuarios", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Atr\303\240s", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Agregar Usuario", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "Men\303\271 Principal", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "Atr\303\240s", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Atr\303\240s", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Gesti\303\262n del Material", nullptr));
        lineEdit->setInputMask(QString());
        lineEdit->setText(QString());
        lineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Buscar por T\303\254tulo, Autor, C\303\262digo o Tipo...", nullptr));
        botonUsuarios_2->setText(QCoreApplication::translate("MainWindow", "Buscar", nullptr));
        botonNuevoMaterial->setText(QCoreApplication::translate("MainWindow", "Agregar Nuevo Material", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
