#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "backwardproduction.h"
#include "forwardproduction.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    LoadPatients();
    LoadThreatments();
    ui->editTemperature->setInputMask("00.0");
    on_patientComboBox_activated(ui->patientComboBox->currentText());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::LoadPatients()
{
    for(int i = 0; i < patients.getCount(); i++){
        ui->patientComboBox->addItem(QtConvertStr(patients.getPatient(i)));
    }
}

void MainWindow::LoadThreatments()
{
    for(int i = 0; i < patients.getCount(); i++){
        ui->comboBoxkindThreatment->addItem(QtConvertStr(diseases.getDisease(i)));
    }
}

void MainWindow::getPatientCharactestFromUI(Diseases::PatientsCharacters& patientCharacters)
{
    patientCharacters.temperature = ui->editTemperature->text().toFloat();
    patientCharacters.nerv = ui->isNerv->isChecked();
    patientCharacters.rush = ui->isRush->isChecked();
    patientCharacters.stra = ui->isStra->isChecked();
    patientCharacters.vosp = ui->isVosp->isChecked();
    patientCharacters.cough = ui->isCough->isChecked();
    patientCharacters.blooding = ui->isBlooding->isChecked();
    patientCharacters.headache = ui->isHeadache->isChecked();
    patientCharacters.lowweight = ui->isLowweight->isChecked();
    patientCharacters.aggression = ui->isAggression->isChecked();
    patientCharacters.stomachache = ui->isStomachAche->isChecked();
    patientCharacters.trauma = ui->isTrauma->isChecked();
    patientCharacters.mental = ui->isMental->isChecked();
    patientCharacters.virus = ui->isVirus->isChecked();
    patientCharacters.iszo = ui->isIszo->isChecked();
}

void MainWindow::setPatientCharactestToUI(Diseases::PatientsCharacters patientCharacters)
{
    ui->editTemperature->setText(QString::number(patientCharacters.temperature,'d',1));
    ui->isNerv->setChecked(patientCharacters.nerv);
    ui->isRush->setChecked(patientCharacters.rush);
    ui->isStra->setChecked(patientCharacters.stra);
    ui->isVosp->setChecked(patientCharacters.vosp);
    ui->isCough->setChecked(patientCharacters.cough);
    ui->isBlooding->setChecked(patientCharacters.blooding);
    ui->isHeadache->setChecked(patientCharacters.headache);
    ui->isLowweight->setChecked(patientCharacters.lowweight);
    ui->isAggression->setChecked(patientCharacters.aggression);
    ui->isStomachAche->setChecked(patientCharacters.stomachache);
    ui->isTrauma->setChecked(patientCharacters.trauma);
    ui->isMental->setChecked(patientCharacters.mental);
    ui->isVirus->setChecked(patientCharacters.virus);
    ui->isIszo->setChecked(patientCharacters.iszo);
}


void MainWindow::on_buttonSolutionForward_clicked()
{
    getPatientCharactestFromUI(patientCharacters);
    std::pair<std::string,std::string> result = forwardProduction::solution(patientCharacters,diseases);
    ui->editDiseases->setText(QtConvertStr(result.first));
    ui->editTreatment->setText(QtConvertStr(result.second));
}

void MainWindow::on_buttonSolutionBackward_clicked()
{
    getPatientCharactestFromUI(patientCharacters);
    std::string result = backwardProduction::solution(ui->comboBoxkindThreatment->currentText().toUtf8().constData(),diseases,patients);
    ui->editListPatients->setText(QtConvertStr(result));
}

void MainWindow::on_patientComboBox_activated(const QString &arg1)
{
    patientCharacters = patients.getPatientCharacters(arg1.toUtf8().constData());
    setPatientCharactestToUI(patientCharacters);
}
