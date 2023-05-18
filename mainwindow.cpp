#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

#include <iostream>
#include <string>
//using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_num1_clicked()
{
    print_text(ui->num1->text());
}

void MainWindow::print_text(QString text) {
         QString save_text = ui->input_user->text();
         ui->input_user->setText(text);
         ui->input_user->setText(save_text + ui->input_user->text());
}

void MainWindow::on_num2_clicked()
{
    print_text(ui->num2->text());
}


void MainWindow::on_num3_clicked()
{
    print_text(ui->num3->text());
}


void MainWindow::on_num4_clicked()
{
    print_text(ui->num4->text());
}


void MainWindow::on_num5_clicked()
{
    print_text(ui->num5->text());
}


void MainWindow::on_num6_clicked()
{
    print_text(ui->num6->text());
}


void MainWindow::on_num7_clicked()
{
    print_text(ui->num7->text());
}


void MainWindow::on_num8_clicked()
{
    print_text(ui->num8->text());
}


void MainWindow::on_num9_clicked()
{
    print_text(ui->num9->text());
}


void MainWindow::on_num0_clicked()
{
    print_text(ui->num0->text());
}


void MainWindow::on_point_clicked()
{
    print_text(ui->point->text());
}


void MainWindow::on_plus_clicked()
{
    print_text(ui->plus->text());
}


void MainWindow::on_minus_clicked()
{
    print_text(ui->minus->text());
}


void MainWindow::on_umn_clicked()
{
    print_text(ui->umn->text());
}


void MainWindow::on_del_clicked()
{
    print_text(ui->del->text());
}


void MainWindow::on_close_barcket_clicked()
{
    print_text(ui->close_barcket->text());
}


void MainWindow::on_open_bracket_clicked()
{
    print_text(ui->open_bracket->text());
}


void MainWindow::on_rate_clicked()
{
    print_text(ui->rate->text());
}


void MainWindow::on_cos_clicked()
{
    print_text(ui->cos->text() + '(');
}


void MainWindow::on_mod_clicked()
{
    print_text(ui->mod->text());
}


void MainWindow::on_sin_clicked()
{
    print_text(ui->sin->text() + '(');
}


void MainWindow::on_asin_clicked()
{
    print_text(ui->asin->text() + '(');
}


void MainWindow::on_tan_clicked()
{
    print_text(ui->tan->text() + '(');
}


void MainWindow::on_log_clicked()
{
    print_text(ui->log->text() + '(');
}


void MainWindow::on_ln_clicked()
{
    print_text(ui->ln->text() + '(');
}


void MainWindow::on_atan_clicked()
{
    print_text(ui->atan->text() + '(');
}

void MainWindow::on_sqrt_clicked()
{
    print_text(ui->sqrt->text() + '(');
}


void MainWindow::on_acos_clicked()
{
    print_text(ui->acos->text() + '(');
}


void MainWindow::on_clear_clicked()
{
    ui->input_user->setText("");
    ui->tabWidget->setTabEnabled(1,true);
//    ui->output->setText("");
}


void MainWindow::on_button_resul_clicked()
{
    QByteArray all_expression;
    QString res;
    double result = 0;
    all_expression = ui->input_user->text().toLocal8Bit() + "=";
    char *input = all_expression.data();

    if (check_input_user(input)) {
        ui->output->setText("Error");

    } else {
        result = calculator(input, ui->value_x->value());
        res = QString::number(result, 'g', 12);
        ui->output->setText(res);
    }
}

void MainWindow::on_x_clicked()
{
    print_text(ui->x->text());
}

void MainWindow::on_print_grafig_clicked()
{
    QByteArray all_expression;
    all_expression = ui->input_user->text().toLocal8Bit() + "=";
    char *input = all_expression.data();

    h = 0.1;
    xBegin = ui->xMin->value();
    xEnd = ui->xMax->value();

    yBegin = ui->yMin->value();
    yEnd = ui->yMax->value();

    ui->widget->clearGraphs();
    x.clear();
    y.clear();

    ui->widget->xAxis->setRange(xBegin, xEnd);
    ui->widget->yAxis->setRange(yBegin, yEnd);

    X = xBegin;

    for (X = xBegin; X <= xEnd; X += h) {
        Y = calculator(input, X);

        if (Y >= yBegin && Y <= yEnd) {
            x.push_back(X);
            y.push_back(Y);
        }
    }

    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x,y);
    ui->widget->replot();

    ui->widget->setInteraction(QCP::iRangeZoom, true);
    ui->widget->setInteraction(QCP::iRangeDrag, true);
}


void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    QByteArray all_expression;
    int result = 0;

    all_expression = ui->input_user->text().toLocal8Bit() + "=";

    char *input = all_expression.data();
    result = check_input_user(input);

    if ((result || !strchr(ui->input_user->text().toStdString().c_str(), 'x')) && index != 0 ) {
        ui->tabWidget->setTabEnabled(1,false);
        ui->output->setText("Incorrect x");

    } else {
        ui->tabWidget->setTabEnabled(1, true);
    }
}


void MainWindow::on_credit_button_clicked()
{
    if (ui->sum_credit->value() > 1000 && ui->time->value() >  0 && ui->percent->value() != 0) {
            if (ui->aunt_1->isChecked()) {
                double percent = ui->percent->value() / (100 * 12);
                double sum = ui->sum_credit->value() * (percent / (1 - pow(1 + percent, -(ui->time->value()) )));

                ui->total_sum_credit->setText(QString::number(sum * ui->time->value(), 'g', 8));
                ui->total_month_sum->setText(QString::number(sum, 'g', 8));
                ui->totap_percent->setText(QString::number((sum * ui->time->value()) - ui->sum_credit->value(), 'g', 8));

            } else if (ui->dif_2->isChecked()) {

                   double sum_credit = ui->sum_credit->value();
                   double month_credit = sum_credit / ui->time->value();
                   double resul_sum = sum_credit;

                   for (int i = 0; i < ui->time->value(); i++){
                       double percent_sum = sum_credit * ui->percent->value() / (100 * 12);
                       resul_sum += percent_sum;
                       sum_credit -= month_credit + percent_sum;

                       if (i == 0) {
                            ui->total_month_sum->setText(QString::number(percent_sum + month_credit, 'g', 8) + " ... ");
                       }

                       if (i + 1 == ui->time->value()) {
                           ui->total_month_sum->setText(ui->total_month_sum->text() + QString::number(percent_sum + month_credit, 'g', 8));
                       }
                   }

                   ui->total_sum_credit->setText(QString::number(resul_sum, 'g', 8));
                   ui->totap_percent->setText(QString::number(resul_sum - ui->sum_credit->value(), 'g', 8));
            }
    }

}

