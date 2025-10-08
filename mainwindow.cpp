#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_botonMaterial_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->material);

}


void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->menu_principal);
}


void MainWindow::on_botonNuevoMaterial_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->nuevo_material);
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->material);
}


void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->menu_principal);
}


void MainWindow::on_botonUsuarios_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->usuario);
}


void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->menu_principal);
}


void MainWindow::on_pushButton_6_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->usuario);
}


void MainWindow::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->menu_principal);
}


void MainWindow::on_botonNuevoMaterial_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->nuevo_usuario);
}

