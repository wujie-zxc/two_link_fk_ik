#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "gmath.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum OP
    {
      X_SUB,
      X_ADD,
      Y_SUB,
      Y_ADD,
    };
    Q_ENUM(OP)
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    OP getOP();
    double getStep();
    void Print(const QString & str);

private slots:
    void on_pbn_ok_clicked();
    void on_pbn_clear_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
