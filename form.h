#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QPaintEvent >
#include <QPainter>

namespace Ui {
class Form;
}

class MainWindow;
class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

    void setHOST(MainWindow *host) { host_ = host; }
    void render(double L1, double L2, double deg1, double deg2, double deg3, double deg4);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::Form *ui;
    MainWindow *host_{nullptr};
    double deg1_{0.};
    double deg2_{0.};
    double deg3_{0.};
    double deg4_{0.};
    double L1{130};
    double L2{224};
};

#endif // FORM_H
