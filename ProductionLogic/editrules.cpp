#include "editrules.h"
#include "ui_editrules.h"
#include <QDebug>
#include <QFile>
#include <QScriptEngine>
#include <QScriptContext>
#include <QScriptValue>

#define END_VAR "//end var"
#define END_RULE "//end rule"

EditRules::EditRules(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditRules)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidgetRules->setColumnCount(2);
    //readCharactersFromFile(CHARACTERS_FILE_NAME);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Свойство" << "Значение");
    ui->tableWidgetRules->setHorizontalHeaderLabels(QStringList() << "Правило" << "Значение");
    readCharactersFromFile(CHARACTERS_FILE_NAME);
    on_pushButtonReadRules_clicked();
    ui->tableWidget->update();
    ui->tableWidgetRules->update();
}

void EditRules::AddRow(QString row1, QString row2){
    ui->tableWidget->setRowCount(++countRows);
    ui->tableWidget->setItem(countRows-1,0,new QTableWidgetItem(row1));
    ui->tableWidget->setItem(countRows-1,1,new QTableWidgetItem(row2));
}

EditRules::~EditRules()
{
    delete ui;
}

void EditRules::readCharactersFromFile(QString fileName){
    listPairVars.clear();
    std::pair<QString,QString> pair;
    countRows = 0;
    ui->tableWidget->clear();
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Свойство" << "Значение");
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;
    readedfile = file.readAll();
    QStringList readedfileList = readedfile.split("\n");
    QString row1;
    QString row2;
    for(QString iter : readedfileList){
        qDebug()<< "iter:"<<iter<<"\n";
        if(iter == QString(END_VAR))
            break;
        if(iter.indexOf("//") == 0){
            iter.remove(0,2);
            pair.first = iter;
            qDebug()<< "row1:"<<iter<<"\n";
            row1 = iter;
        } else if(iter.contains(" = ")){
            row2 = iter.remove(0,iter.indexOf(" = ") + 3);
            pair.second = "v"+QString::number(countRows);
            qDebug()<< "row2:"<<iter<<"\n";
            AddRow(row1,row2);
            listPairVars.push_back(pair);        }
    }
    file.close();
}

void EditRules::writeCharactersToFile(QString fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
    QByteArray writeResult = "";
    for(int i = 0; i < ui->tableWidget->rowCount(); i++){
        std::pair<QString,QString> row = getRow(i);
        writeResult += QString("//"+row.first + "\n var v" + QString::number(i) + " = " +row.second + "\n");
    }
    writeResult += QString(END_VAR);
    file.write(writeResult);
    file.close();

}

std::pair<QString,QString> EditRules::getRow(int numberRow){
    std::pair<QString,QString> result;
    result.first = ui->tableWidget->item(numberRow,0)->text();
    result.second = ui->tableWidget->item(numberRow,1)->text();
    return result;
}

void EditRules::readRulesFromFile(QString fileName)
{
    countRowsRules = 0;
    ui->tableWidgetRules->clear();
    ui->tableWidgetRules->setHorizontalHeaderLabels(QStringList() << "Правило" << "Значение");
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;
    readedfileRules = file.readAll();
    QStringList readedfileRulesList = readedfileRules.split("\n");
    QString row1;
    QString row2;
    for(QString iter : readedfileRulesList){
        if(iter == QString(END_RULE))
            break;
            AddRowRule(iter.split("!!!").at(0),iter.split("!!!").at(1));
    }
    ui->comboBoxRules->clear();
    for(int i = 0 ; i < ui->tableWidgetRules->rowCount(); i++)
        ui->comboBoxRules->addItem(getRowRule(i).first);
    file.close();
}

void EditRules::writeRulesToFile(QString fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
    QByteArray writeResult = "";
    for(int i = 0; i < ui->tableWidgetRules->rowCount(); i++){
        std::pair<QString,QString> row = getRowRule(i);
        writeResult += QString(row.first + "!!!" + row.second+"\n");
    }
    ui->comboBoxRules->clear();
    for(int i = 0 ; i < ui->tableWidgetRules->rowCount(); i++)
        ui->comboBoxRules->addItem(getRowRule(i).first);
    writeResult += QString(END_RULE);
    file.write(writeResult);
    file.close();
}

void EditRules::writeProgram(QString fileName)
{
    on_pushButtonSave_clicked();
    on_pushButtonRead_clicked();
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
    QByteArray writeResult = "";
    listPairRules.clear();
    countRows = ui->tableWidget->rowCount();
    std::pair<QString, std::pair<QString,QStringList>> pair;
    for(int i = 0; i < ui->tableWidgetRules->rowCount(); i++){
        std::pair<QString,QString> row = getRowRule(i);
        QString var = "";
        if(findVar(row.first).isEmpty())
                var = "var ";
        QString variable = findVar(row.first);
        if(variable.isEmpty()){
            variable = "v"+QString::number(countRows);
            countRows++;
        }
        pair.first = row.first;
        pair.second = {variable,findVars(row.second)};
        listPairRules.push_back(pair);
        writeResult += QString("//"+row.first + "\n "+ var + variable+ " " +changeVar(row.second) + "\n");
    }
    qDebug()<<listPairRules;
    writeResult += QString(END_RULE);
    on_pushButtonSave_clicked();
    writeResult = readedfile.toLocal8Bit() + "\n" + QString(writeResult).toLocal8Bit();
    file.write(writeResult);
    file.close();
    programJS = writeResult;
    JSRunResult(programJS,findVarRule(ui->comboBoxRules->currentText()));
}

void EditRules::writeProgramBack(QString fileName)
{
    on_pushButtonSave_clicked();
    on_pushButtonRead_clicked();
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
    QByteArray writeResult = "";
    listPairRules.clear();
    countRows = ui->tableWidget->rowCount();
    std::pair<QString, std::pair<QString,QStringList>> pair;
    for(int i = 0; i < ui->tableWidgetRules->rowCount(); i++){
        std::pair<QString,QString> row = getRowRule(i);
        QString var = "";
        if(findVar(row.first).isEmpty())
                var = "var ";
        QString variable = findVar(row.first);
        if(variable.isEmpty()){
            variable = "v"+QString::number(countRows);
            countRows++;
        }
        pair.first = row.first;
        pair.second = {variable,findVars(row.second)};
        listPairRules.push_back(pair);
        //writeResult += QString("//"+row.first + "\n "+ var + variable+ " " +changeVar(row.second) + "\n");
    }
    QString writeBack = "";
    countRows = ui->tableWidget->rowCount();
    for(int i = 0; i < ui->tableWidgetRules->rowCount(); i++){
        std::pair<QString,QString> row = getRowRule(i);
        if(ui->comboBoxRules->currentText() == row.first){
            QString var = "";
            if(findVar(row.first).isEmpty())
                    var = "var ";
            QString variable = findVar(row.first);
            if(variable.isEmpty()){
                variable = "v"+QString::number(countRows);
                countRows++;
            }

            writeBack.prepend( QString("//"+row.first + "\n "+ var + variable+ " " +changeVar(row.second) + "\n"));

        }
    }
    writeResult+=writeBack;
    qDebug()<<listPairRules;
    writeResult += QString(END_RULE);
    on_pushButtonSave_clicked();
    writeResult = readedfile.toLocal8Bit() + "\n" + QString(writeResult).toLocal8Bit();
    file.write(writeResult);
    file.close();
    programJS = writeResult;
    JSRunResult(programJS,findVarRule(ui->comboBoxRules->currentText()));
}

void EditRules::findNeedRule(QString goal){

}

QStringList EditRules::findVars(QString str){
    qDebug()<<str;
    QStringList result;
    for(auto iter : listPairVars)
        if(str.contains(iter.first)){
            result.append(findVar(iter.first));
            str.replace(iter.first, "");
        }
    for(auto iter : listPairRules)
        if(str.contains(iter.first)){
            result.append(findVarRule(iter.first));
            str.replace(iter.first, "");
        }
    qDebug()<<result;
return result;
}

QString EditRules::JSRunResult(QString program, QString variable){
    qDebug()<<"\n"<<"js run, var:"+variable+"'n program:"+program;
    QScriptEngine engine;
    QScriptContext* context = engine.pushContext();
    engine.evaluate(program);
    QString result = context->activationObject().property(variable).toString();
    qDebug()<<result;
    ui->lineEditResult->setText(result);
    //qDebug()<<result;
    engine.popContext();
    return result;
}

QString EditRules::changeVar(QString str){
    for(auto iter : listPairVars)
        if(str.contains(iter.first))
            str.replace(iter.first, findVar(iter.first));
    for(auto iter : listPairRules)
        if(str.contains(iter.first))
            str.replace(iter.first, findVarRule(iter.first));
    return str;
}

QString EditRules::findVar(QString name){
    for(auto iter : listPairVars)
        if(iter.first == name)
            return iter.second;
    return "";
}


QString EditRules::findVarRule(QString name){
    for(auto iter : listPairRules)
        if(iter.first == name)
            return iter.second.first;
    return "";
}

void EditRules::AddRowRule(QString row1, QString row2)
{
    ui->tableWidgetRules->setRowCount(++countRowsRules);
    ui->tableWidgetRules->setItem(countRowsRules-1,0,new QTableWidgetItem(row1));
    ui->tableWidgetRules->setItem(countRowsRules-1,1,new QTableWidgetItem(row2));
}

std::pair<QString, QString> EditRules::getRowRule(int numberRow)
{
    std::pair<QString,QString> result;
    result.first = ui->tableWidgetRules->item(numberRow,0)->text();
    result.second = ui->tableWidgetRules->item(numberRow,1)->text();
    return result;
}

void EditRules::on_pushButtonSave_clicked()
{
    writeCharactersToFile(CHARACTERS_FILE_NAME);
}

void EditRules::on_pushButtonRead_clicked()
{
    readCharactersFromFile(CHARACTERS_FILE_NAME);
}

void EditRules::on_pushButtonAdd_clicked()
{
    AddRow("","");
}

void EditRules::on_pushButtonRemove_clicked()
{
    if(countRows>0)
        ui->tableWidget->setRowCount(--countRows);
}

void EditRules::on_pushButtonAddRule_clicked()
{
    AddRowRule("","");
}

void EditRules::on_pushButtonRemoveRule_clicked()
{
    if(countRowsRules>0)
            ui->tableWidgetRules->setRowCount(--countRowsRules);
}

void EditRules::on_pushButtonSaveRules_clicked()
{
    writeRulesToFile(RULES_FILE_NAME);
}

void EditRules::on_pushButtonReadRules_clicked()
{
    readRulesFromFile(RULES_FILE_NAME);
}

void EditRules::on_pushButtonmakeProgram_clicked()
{
     writeProgram(JS_PROGRAM);

}

void EditRules::on_pushButtonmakeProgramBack_clicked()
{
    writeProgramBack(JS_PROGRAM_BACK);
}
