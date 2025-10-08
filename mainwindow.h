#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// Declaración adelantada: NO definimos la clase aquí
class Material;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_botonMaterial_clicked();

    void on_pushButton_clicked();

    void on_botonNuevoMaterial_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_botonUsuarios_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_botonNuevoMaterial_2_clicked();

private:
    Ui::MainWindow *ui;
    Material* materialWin_ = nullptr;   // ventana “Material”
};

#endif // MAINWINDOW_H
