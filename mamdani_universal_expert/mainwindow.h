#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QComboBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addRule_clicked();

    void on_makeDesigion_clicked();

    void on_removeRule_clicked();

private:
    Ui::MainWindow *ui;
    QList<QLineEdit*> listNames;
    QList<QLineEdit*> listMin1;
    QList<QLineEdit*> listMax1;
    QList<QLineEdit*> listMin2;
    QList<QLineEdit*> listMax2;
    QList<QLineEdit*> listMin3;
    QList<QLineEdit*> listMax3;
    QList<QComboBox*> listTypeFunctionsBad;
    QList<QComboBox*> listTypeFunctionsNormal;
    QList<QComboBox*> listTypeFunctionsGood;
    QList<QHBoxLayout*> listLayout;
    double calculatePercent(QList<double>);
    QList<double> getListBadPercent(QList<double>);
    QList<double> getListNormalPercent(QList<double>);
    QList<double> getListGoodPercent(QList<double>);
    QList<double> getListPercent(QList<double>, QList<int>,QList<double>, QList<double>);
    int labelwidth = 140;
    int controlwidth = 120;
};

#endif // MAINWINDOW_H
