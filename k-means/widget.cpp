#include "widget.h"
#include "ui_widget.h"
#include "k_means.h"
#include <ctime>
#include <cstdlib>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->verticalLayout_3->addWidget(&plot);
    countPoints = 0;
}

Widget::~Widget()
{
    delete ui;
}

/* Как только один из радиобаттонов оказывается нажатым,
 * вызываем перерисовку содержимого виджета,
 * с которым работаем.
 * */
void Widget::on_radioButton_red_clicked()
{
    repaint();
}

void Widget::on_radioButton_green_clicked()
{
    repaint();
}

void Widget::on_radioButton_blue_clicked()
{
    repaint();
}

void Widget::on_pushButtonRandomWrite_clicked()
{
    countPoints = ui->lineEditCountPoint->text().toInt();
    plot.setCountPoints(countPoints);
    plot.setNeedCreateNew(true);
    plot.repaint();
}

void Widget::on_pushButtonKMeans_clicked()
{
    k_means kmeans;
    kmeans.setCountCenters(ui->lineEditcountClasters->text().toInt());
    kmeans.setPoints(plot.getPoints());
    kmeans.setMaxx(plot.width());
    kmeans.setMaxy(plot.height());
    qDebug()<<"before compute";
    kmeans.compute();
    plot.setPoints(kmeans.getPoints());
    plot.repaint();
}
