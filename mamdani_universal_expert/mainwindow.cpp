#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QListIterator>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->comboBoxRules->addItem("Требуется госпитализация");
    //ui->comboBoxRules->addItem("Нужно в травмпункт");
    //ui->comboBoxRules->addItem("Требуется госпитализация");
     //ui->comboBoxRules->addItem("ОРВИ");
     //ui->comboBoxRules->addItem("Воспаление легких");
    QHBoxLayout* layout = new QHBoxLayout(this);
    QLabel* name = new QLabel("Имя",this);
    name->setFixedWidth(labelwidth);
    QLabel* min1 = new QLabel("Минимум плохо",this);
    min1->setFixedWidth(labelwidth);
    QLabel* max1 = new QLabel("Максимум плохо",this);
    max1->setFixedWidth(labelwidth);
    QLabel* min2 = new QLabel("Минимум нормально",this);
    min2->setFixedWidth(labelwidth);
    QLabel* max2 = new QLabel("Максимум нормально",this);
    max2->setFixedWidth(labelwidth);
    QLabel* min3 = new QLabel("Минимум отлично",this);
    min3->setFixedWidth(labelwidth);
    QLabel* max3 = new QLabel("Максимум отлично",this);
    max3->setFixedWidth(labelwidth);
    QLabel* functionBad = new QLabel("Функция плохо",this);
    functionBad->setFixedWidth(labelwidth);
    QLabel* functionNormal = new QLabel("Функция нормально",this);
    functionNormal->setFixedWidth(labelwidth);
    QLabel* functionGood = new QLabel("Функция хорошо",this);
    functionGood->setFixedWidth(labelwidth);
    layout->addWidget(name);
    layout->addWidget(min1);
    layout->addWidget(max1);
    layout->addWidget(min2);
    layout->addWidget(max2);
    layout->addWidget(min3);
    layout->addWidget(max3);
    layout->addWidget(functionBad);
    layout->addWidget(functionNormal);
    layout->addWidget(functionGood);
    ui->rulesLayout->addLayout(layout);
    ui->centralWidget->setFixedWidth(labelwidth*8.5);
    ui->resultEdit->setMaximumWidth(200);
    resize(minimumSizeHint());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addRule_clicked()
{
    QHBoxLayout* layout = new QHBoxLayout();
    QLineEdit* name = new QLineEdit("Имя"+QString::number(listNames.length()+1));
    name->setFixedWidth(controlwidth);
    QLineEdit* min1 = new QLineEdit("0.0");
    min1->setFixedWidth(controlwidth);
    QLineEdit* max1 = new QLineEdit("4.0");
    max1->setFixedWidth(controlwidth);
    QLineEdit* min2 = new QLineEdit("2.0");
    min2->setFixedWidth(controlwidth);
    QLineEdit* max2 = new QLineEdit("6.0");
    max2->setFixedWidth(controlwidth);
    QLineEdit* min3 = new QLineEdit("5.0");
    min3->setFixedWidth(controlwidth);
    QLineEdit* max3 = new QLineEdit("10.0");
    max3->setFixedWidth(controlwidth);
    QComboBox* typeFunctionBad = new QComboBox();
    typeFunctionBad->setFixedWidth(controlwidth);
    QComboBox* typeFunctionNormal = new QComboBox();
    typeFunctionNormal->setFixedWidth(controlwidth);
    QComboBox* typeFunctionGood = new QComboBox();
    typeFunctionGood->setFixedWidth(controlwidth);
    typeFunctionBad->addItem("Линейный спуск");
    typeFunctionBad->addItem("Линейный подъем");
    typeFunctionBad->addItem("Максимум");
    typeFunctionBad->addItem("Минимум");
    typeFunctionBad->addItem("Гора");
    typeFunctionBad->addItem("Яма");
    typeFunctionBad->setCurrentIndex(0);
    typeFunctionNormal->addItem("Линейный спуск");
    typeFunctionNormal->addItem("Линейный подъем");
    typeFunctionNormal->addItem("Максимум");
    typeFunctionNormal->addItem("Минимум");
    typeFunctionNormal->addItem("Гора");
    typeFunctionNormal->addItem("Яма");
    typeFunctionNormal->setCurrentIndex(0);
    typeFunctionGood->addItem("Линейный спуск");
    typeFunctionGood->addItem("Линейный подъем");
    typeFunctionGood->addItem("Максимум");
    typeFunctionGood->addItem("Минимум");
    typeFunctionGood->addItem("Гора");
    typeFunctionGood->addItem("Яма");
    typeFunctionGood->setCurrentIndex(0);
    listNames.append(name);
    listMin1.append(min1);
    listMax1.append(max1);
    listMin2.append(min2);
    listMax2.append(max2);
    listMin3.append(min3);
    listMax3.append(max3);
    listTypeFunctionsBad.append(typeFunctionBad);
    listTypeFunctionsNormal.append(typeFunctionNormal);
    listTypeFunctionsGood.append(typeFunctionGood);
    listLayout.append(layout);
    layout->addWidget(name);
    layout->addWidget(min1);
    layout->addWidget(max1);
    layout->addWidget(min2);
    layout->addWidget(max2);
    layout->addWidget(min3);
    layout->addWidget(max3);
    layout->addWidget(typeFunctionBad);
    layout->addWidget(typeFunctionNormal);
    layout->addWidget(typeFunctionGood);
    ui->rulesLayout->addLayout(layout);
    resize(minimumSizeHint());
}

void MainWindow::on_makeDesigion_clicked()
{
    if(listNames.length() == 0)
    {
        QMessageBox msgBox;
        msgBox.setText("Вы не задали ни одного правила");
        msgBox.exec();
        return;
    } else {
        QLineEdit* iter;
        QList<double> listValues;
        int numberIter = 0;
        foreach(iter, listNames)
        {
            bool bOk;
            double mininput = 9999999;
            if(listMin3.at(numberIter)->text().toDouble() < mininput)
                mininput = listMin3.at(numberIter)->text().toDouble();
            if(listMin2.at(numberIter)->text().toDouble() < mininput)
                mininput = listMin2.at(numberIter)->text().toDouble();
            if(listMin1.at(numberIter)->text().toDouble() < mininput)
                mininput = listMin1.at(numberIter)->text().toDouble();
            double maxinput = -9999999;
            if(listMax3.at(numberIter)->text().toDouble() > maxinput)
                maxinput = listMax3.at(numberIter)->text().toDouble();
            if(listMax2.at(numberIter)->text().toDouble() > maxinput)
                maxinput = listMax2.at(numberIter)->text().toDouble();
            if(listMax1.at(numberIter)->text().toDouble() > maxinput)
                maxinput = listMax1.at(numberIter)->text().toDouble();
            double value = QInputDialog::getDouble( this,
                                                     "Введите данные",
                                                     "Какой показатель "+iter->text()+"?",
                                                     0.0,
                                                     mininput,
                                                     maxinput,
                                                     1,
                                                     &bOk
                                                    );
            if(!bOk)
                return;
            listValues.append(value);
            numberIter++;
        }
        double badpercent = calculatePercent(getListBadPercent(listValues));
        double normalpercent = calculatePercent(getListNormalPercent(listValues));
        double goodpercent = calculatePercent(getListGoodPercent(listValues));
        QMessageBox msgBox;
        msgBox.setText(ui->resultEdit->text()+":\n"+
                       +"Плохо: "+QString::number(badpercent)+"%\n"+
                       +"Нормально: "+QString::number(normalpercent)+"%\n"+
                       +"Хорошо: "+QString::number(goodpercent)+"%");
        msgBox.exec();
    }
}

void MainWindow::on_removeRule_clicked()
{
    bool bOk;
    if(listNames.length() == 0)
    {
        QMessageBox msgBox;
        msgBox.setText("Вы не задали ни одного правила");
        msgBox.exec();
        return;
    }
    int value = QInputDialog::getInt( this,
                                         "Какое правило вы хотите удалить?",
                                         "Номер правила",
                                         1,
                                         1,
                                         listNames.length(),
                                         1,
                                         &bOk
                                        );
    if (bOk) {
        ui->rulesLayout->removeWidget(listNames.at(value-1));
        delete listNames.at(value-1);
        listNames.removeAt(value-1);
        ui->rulesLayout->removeWidget(listMin1.at(value-1));
        delete listMin1.at(value-1);
        listMin1.removeAt(value-1);
        ui->rulesLayout->removeWidget(listMax1.at(value-1));
        delete listMax1.at(value-1);
        listMax1.removeAt(value-1);
        ui->rulesLayout->removeWidget(listMin2.at(value-1));
        delete listMin2.at(value-1);
        listMin2.removeAt(value-1);
        ui->rulesLayout->removeWidget(listMax2.at(value-1));
        delete listMax2.at(value-1);
        listMax2.removeAt(value-1);
        ui->rulesLayout->removeWidget(listMin3.at(value-1));
        delete listMin3.at(value-1);
        listMin3.removeAt(value-1);
        ui->rulesLayout->removeWidget(listMax3.at(value-1));
        delete listMax3.at(value-1);
        listMax3.removeAt(value-1);
        ui->rulesLayout->removeWidget(listTypeFunctionsBad.at(value-1));
        delete listTypeFunctionsBad.at(value-1);
        listTypeFunctionsBad.removeAt(value-1);
        ui->rulesLayout->removeWidget(listTypeFunctionsNormal.at(value-1));
        delete listTypeFunctionsNormal.at(value-1);
        listTypeFunctionsNormal.removeAt(value-1);
        ui->rulesLayout->removeWidget(listTypeFunctionsGood.at(value-1));
        delete listTypeFunctionsGood.at(value-1);
        listTypeFunctionsGood.removeAt(value-1);
        delete listLayout.at(value-1);
        listLayout.removeAt(value-1);
        resize(minimumSizeHint());
    }
}

double MainWindow::calculatePercent(QList<double> listMarks)
{
    double sum = 0;
    foreach(double iter, listMarks)
        sum += iter;
    return sum/listMarks.length()*100;
}

QList<double> MainWindow::getListBadPercent(QList<double> list)
{
    QList<int> typeList;
    QList<double> minList;
    QList<double> maxList;
    foreach(QComboBox* iter, listTypeFunctionsBad)
        typeList.append(iter->currentIndex());
    foreach(QLineEdit* iter, listMin1)
        minList.append(iter->text().toDouble());
    foreach(QLineEdit* iter, listMax1)
        maxList.append(iter->text().toDouble());
    return getListPercent(list,typeList,minList,maxList);
}

QList<double> MainWindow::getListNormalPercent(QList<double> list)
{
    QList<int> typeList;
    QList<double> minList;
    QList<double> maxList;
    foreach(QComboBox* iter, listTypeFunctionsNormal)
        typeList.append(iter->currentIndex());
    foreach(QLineEdit* iter, listMin2)
        minList.append(iter->text().toDouble());
    foreach(QLineEdit* iter, listMax2)
        maxList.append(iter->text().toDouble());
    return getListPercent(list,typeList,minList,maxList);
}

QList<double> MainWindow::getListGoodPercent(QList<double> list)
{
    QList<int> typeList;
    QList<double> minList;
    QList<double> maxList;
    foreach(QComboBox* iter, listTypeFunctionsGood)
        typeList.append(iter->currentIndex());
    foreach(QLineEdit* iter, listMin3)
        minList.append(iter->text().toDouble());
    foreach(QLineEdit* iter, listMax3)
        maxList.append(iter->text().toDouble());
    return getListPercent(list,typeList,minList,maxList);
}

QList<double> MainWindow::getListPercent(QList<double> listValues, QList<int> listTypes, QList<double> listMin, QList<double> listMax)
{
    QList<double> answerList;
    int numberiter = 0;
    foreach(int iter, listTypes)
    {
        double nowvalue = listValues.at(numberiter);
        double minvalue = listMin.at(numberiter);
        double maxvalue = listMax.at(numberiter);
        double delta = maxvalue-minvalue;
        if(nowvalue >= minvalue && nowvalue <= maxvalue){
            switch(iter){
            case 0:
                answerList.append(1-fabs((nowvalue-minvalue)/delta));
                break;
            case 1:
                answerList.append(fabs((nowvalue-minvalue)/delta));
                break;
            case 2:
                answerList.append(1.0);
                break;
            case 3:
                answerList.append(0.0);
                break;
            case 4:
                if(fabs((nowvalue-minvalue)/delta) <= 0.5)
                {
                    answerList.append(fabs((nowvalue-minvalue)/(delta/2)));
                } else {
                    answerList.append(1-fabs((nowvalue-minvalue-delta/2)/(delta/2)));
                }
                break;
            case 5:
                if(fabs((nowvalue-minvalue)/delta) <= 0.5)
                {
                    answerList.append(1-fabs((nowvalue-minvalue)/(delta/2)));
                } else {
                    answerList.append(fabs((nowvalue-minvalue-delta/2)/(delta/2)));
                }
                break;
            }
        } else {
            answerList.append(0.0);
        }
        numberiter++;
    }
    return answerList;
}
