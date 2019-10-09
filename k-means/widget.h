#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include "plot.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_radioButton_red_clicked();

    void on_radioButton_green_clicked();

    void on_radioButton_blue_clicked();

    void on_pushButtonRandomWrite_clicked();

    void on_pushButtonKMeans_clicked();

private:
    Ui::Widget *ui;
    Plot plot;
    int countPoints;
};

#endif // WIDGET_H
