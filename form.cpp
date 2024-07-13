#include "form.h"
#include "ui_form.h"
#include "mainwindow.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;
}

void Form::render(double l1, double l2, double deg1, double deg2,  double deg3, double deg4)
{
    L1 = l1;
    L2 = l2;
    deg1_ = deg1;
    deg2_ = deg2;
    deg3_ = deg3;
    deg4_ = deg4;
    update();
}

void Form::paintEvent(QPaintEvent *event)
{
    (void)event;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);
    //painter.scale(1, -1); // 翻转Y轴，使得Y+向上
    double scaleFactor = std::min(width() / (2.0 * (L1 + L2)), height() / (2.0 * (L1 + L2)));
    painter.scale(scaleFactor, -scaleFactor);

    // 绘制工作空间
    QPen workspacePen(Qt::darkGreen, 2, Qt::DotLine);
    painter.setPen(workspacePen);
    painter.drawEllipse(QPointF(0, 0), L1 + L2, L1 + L2);

    // 绘制坐标轴
    QPen axisPen(Qt::black, 1, Qt::DashLine);
    painter.setPen(axisPen);
    painter.drawLine(-width() / 2, 0, width() / 2, 0);
    painter.drawLine(0, -height() / 2, 0, height() / 2);

    // 计算逆解前的连杆位置
    double theta1_rad = deg1_ ;
    double theta2_rad = deg2_ ;

    double x1 = L1 * cos(theta1_rad);
    double y1 = L1 * sin(theta1_rad);
    double x2 = x1 + L2 * cos(theta1_rad + theta2_rad);
    double y2 = y1 + L2 * sin(theta1_rad + theta2_rad);

    // 绘制逆解前的连杆
    QPen pen;
    pen.setColor(Qt::darkBlue);
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.drawLine(0, 0, x1, y1);
    painter.drawLine(x1, y1, x2, y2);

    // 绘制连接处和末端的圆
    pen.setColor(Qt::black);
    pen.setStyle(Qt::DashLine);
    pen.setWidth(1);
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(QPointF(x1, y1), 10, 10); // 连接处空心圆
    painter.setBrush(Qt::yellow);
    painter.drawEllipse(QPointF(x2, y2), 10, 10); // 末端实心圆

    // 计算逆解后的连杆位置
    double new_theta1_rad = deg3_ ;
    double new_theta2_rad = deg4_ ;

    double x3 = L1 * cos(new_theta1_rad);
    double y3 = L1 * sin(new_theta1_rad);
    double x4 = x3 + L2 * cos(new_theta1_rad + new_theta2_rad);
    double y4 = y3 + L2 * sin(new_theta1_rad + new_theta2_rad);
    // 绘制逆解后的连杆
    pen.setColor(Qt::red);
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.drawLine(0, 0, x3, y3);
    painter.drawLine(x3, y3, x4, y4);

    // 绘制连接处和末端的圆
    pen.setColor(Qt::gray);
    painter.setBrush(Qt::NoBrush);
    pen.setWidth(1);
    painter.drawEllipse(QPointF(x3, y3), 10, 10); // 连接处空心圆
    painter.setBrush(Qt::yellow);
    painter.drawEllipse(QPointF(x4, y4), 10, 10); // 末端实心圆

}
