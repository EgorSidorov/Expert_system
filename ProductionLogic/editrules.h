#ifndef EDITRULES_H
#define EDITRULES_H

#include <QDialog>

#define CHARACTERS_FILE_NAME "characters.js"
#define RULES_FILE_NAME "rules.txt"
#define JS_PROGRAM "program.js"
#define JS_PROGRAM_BACK "programback.js"

namespace Ui {
class EditRules;
}

class EditRules : public QDialog
{
    Q_OBJECT

public:
    explicit EditRules(QWidget *parent = nullptr);
    ~EditRules();

    std::list<std::string> charactersName;
    std::list<std::string> charactersValue;

    void readCharactersFromFile(QString fileName);
    void writeCharactersToFile(QString fileName);

    void AddRow(QString, QString);
    std::pair<QString, QString> getRow(int numberRow);

    std::list<std::string> rulesName;
    std::list<std::string> rulesValue;

    void readRulesFromFile(QString fileName);
    void writeRulesToFile(QString fileName);

    void AddRowRule(QString, QString);
    std::pair<QString, QString> getRowRule(int numberRow);
    QString JSRunResult(QString program, QString variable);
private slots:
    void on_pushButtonSave_clicked();

    void on_pushButtonRead_clicked();

    void on_pushButtonAdd_clicked();

    void on_pushButtonRemove_clicked();

    void on_pushButtonAddRule_clicked();

    void on_pushButtonRemoveRule_clicked();

    void on_pushButtonSaveRules_clicked();

    void on_pushButtonReadRules_clicked();

    void on_pushButtonmakeProgram_clicked();

    void on_pushButtonmakeProgramBack_clicked();

private:
    Ui::EditRules *ui;
    int countRows = 0;
    int countRowsRules = 0;
    std::list<std::pair<QString,QString>> listPairVars;
    std::list<std::pair<QString, std::pair<QString,QStringList>>> listPairRules;
    QString findVar(QString name);
    QString changeVar(QString str);
    QString readedfile;
    QString readedfileRules;
    void writeProgram(QString fileName);
    void writeProgramBack(QString fileName);
    QStringList findVars(QString str);
    QString findVarRule(QString name);
    QString programJS;
    void findNeedRule(QString goal);
};

#endif // EDITRULES_H
