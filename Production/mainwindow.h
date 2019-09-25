#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "diseases.h"
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

private slots:
    void on_buttonSolutionForward_clicked();

    void on_buttonSolutionBackward_clicked();

    void on_patientComboBox_activated(const QString &arg1);

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
    Diseases::PatientsCharacters patientCharacters;
};

#endif // MAINWINDOW_H
