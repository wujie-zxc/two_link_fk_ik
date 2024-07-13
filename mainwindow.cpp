#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("两轴正逆解");
    ui->render->setHOST(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow::OP MainWindow::getOP()
{
    if (ui->rbn_x_sub->isChecked()) {
        return OP::X_SUB;
    }
    if (ui->rbn_x_add->isChecked()) {
        return OP::X_ADD;
    }
    if (ui->rbn_y_sub->isChecked()) {
        return OP::Y_SUB;
    }
    if (ui->rbn_y_add->isChecked()) {
        return OP::Y_ADD;
    }
}

double MainWindow::getStep()
{
    return ui->le_step->text().toDouble();
}

void MainWindow::Print(const QString &str)
{
    ui->textEdit->append(str);
}


void MainWindow::on_pbn_ok_clicked()
{
    double L1 = ui->le_L1->text().toDouble();
    double L2 = ui->le_L2->text().toDouble();
    ui->textEdit->clear();
   double deg1_, deg2_;

    deg1_ = ui->le_deg1->text().toDouble();
    deg2_ = ui->le_deg2->text().toDouble();
    ui->textEdit->append(QString("--当前关节角度: %1 : %2").arg(deg1_).arg(deg2_));
    deg1_ = deg1_ * PI/180;
    deg2_ = deg2_ *PI/180;
    double cur_x, cur_y;
    Gmath::forward_kinematics(L1, L2, deg1_, deg2_, cur_x, cur_y);
    ui->textEdit->append(QString("--正解后得到坐标:(%1 , %2)").arg(cur_x).arg(cur_y));

    double step = ui->le_step->text().toDouble();
    switch (getOP()) {
    case OP::X_SUB:
        cur_x -= step;
        break;
    case OP::X_ADD:
        cur_x += step;
        break;
    case OP::Y_SUB:
        cur_y -= step;
        break;
    case OP::Y_ADD:
        cur_y += step;
        break;
    }
    ui->textEdit->append(QString("--添加步进得到目标坐标(%1 , %2)").arg(cur_x).arg(cur_y));
    double f_deg1, f_deg2;
    Gmath::inverse_kinematics(L1, L2, cur_x, cur_y, deg1_, deg2_, f_deg1, f_deg2);
    ui->textEdit->append(QString("--逆解算出目标坐标对应的关节角: %1 : %2").arg(f_deg1*180/PI).arg(f_deg2*180/PI));
    double fx, fy;
    Gmath::forward_kinematics(L1, L2, f_deg1, f_deg2, fx, fy);
    ui->textEdit->append(QString("--验证逆解算出的关节角对应的坐标:(%1 , %2)").arg(fx).arg(fy));

    ui->render->render(L1, L2, deg1_, deg2_, f_deg1, f_deg2);
}

void MainWindow::on_pbn_clear_clicked()
{
    ui->textEdit->clear();
}
