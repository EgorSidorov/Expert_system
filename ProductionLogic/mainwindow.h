#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "diseases.h"
#include "editrules.h"
#include "patients.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void on_buttonSolutionForward_clicked();

    void on_buttonSolutionBackward_clicked();

    void on_patientComboBox_activated(const QString &arg1);

    void on_actionEditRules_triggered();

private:
    QString QtConvertStr(const std::string str){
        return QString::fromUtf8(str.c_str());
    }
    void LoadPatients();
    void LoadThreatments();
    void getPatientCharactestFromUI(Diseases::PatientsCharacters&);
    void setPatientCharactestToUI(Diseases::PatientsCharacters);


    Ui::MainWindow *ui;
    Diseases diseases;
    Patients patients;
    QAction* ruleAction;
    Diseases::PatientsCharacters patientCharacters;
};

#endif // MAINWINDOW_H
