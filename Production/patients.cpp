#include "patients.h"

Patients::Patients()
{

}

std::string Patients::getPatient(const int number) const
{
    if(patients.size() > number)
        return *std::next(patients.begin(), number);
    else
        return "";
}

void Patients::setPatient(const std::string patient)
{
    patients.push_back(patient);
}

int Patients::getCount() const
{
    return patients.size();
}

Diseases::PatientsCharacters Patients::getPatientCharacters(const std::string name)
{
    int number = 0;
    for(const std::string iter : patients){
        if(iter == name)
            return patients_characters.at(number);
        number++;
    }
}

Diseases::PatientsCharacters Patients::getPatientCharacters(int number)
{
    return patients_characters.at(number);
}
