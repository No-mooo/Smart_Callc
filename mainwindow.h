#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <stdlib.h> // !
#include <QVector>

extern "C" {
#include "smart_callc.h"
}

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_num1_clicked();
    void print_text(QString text);

    void on_num2_clicked();

    void on_num3_clicked();

    void on_num4_clicked();

    void on_num5_clicked();

    void on_num6_clicked();

    void on_num7_clicked();

    void on_num8_clicked();

    void on_num9_clicked();

    void on_num0_clicked();

    void on_point_clicked();

    void on_plus_clicked();

    void on_minus_clicked();

    void on_umn_clicked();

    void on_del_clicked();

    void on_close_barcket_clicked();

    void on_open_bracket_clicked();

    void on_rate_clicked();

    void on_cos_clicked();

    void on_mod_clicked();

    void on_sin_clicked();

    void on_asin_clicked();

    void on_tan_clicked();

    void on_log_clicked();

    void on_ln_clicked();

    void on_atan_clicked();

    void on_sqrt_clicked();

    void on_acos_clicked();

    void on_clear_clicked();

    void on_button_resul_clicked();

    void on_x_clicked();

    void on_print_grafig_clicked();

    void on_tabWidget_tabBarClicked(int index);

    void on_credit_button_clicked();

private:
    Ui::MainWindow *ui;
    double xBegin, xEnd, h, X, yBegin, yEnd, Y;
    int N;

    QVector<double> x,y;
};
#endif // MAINWINDOW_H
