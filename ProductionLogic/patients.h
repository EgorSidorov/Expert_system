#ifndef PATIENTS_H
#define PATIENTS_H

#include <list>
#include <string>
#include <map>
#include "diseases.h"

class Patients
{
public:
    Patients();
    std::string getPatient(const int number) const;
    void setPatient(const std::string patient);
    int getCount() const;
    Diseases::PatientsCharacters getPatientCharacters(const std::string name);
    Diseases::PatientsCharacters getPatientCharacters(int number);

private:
    std::list<std::string> patients{
        "Петр",
        "Иван",
        "Мария",
        "Екатерина",
        "Татьяна",
        "Сергей",
        "Антон",
        "Николай"
    };

    std::map <int,Diseases::PatientsCharacters> patients_characters{
        {0,Diseases::PatientsCharacters(true,false,false,36.7,false,false,false,false,false,false,false,true,false,false,true)},//язва
        {1,Diseases::PatientsCharacters(true,false,false,36.9,false,false,false,false,false,false,true,false,false,true,false)},//вывих
        {2,Diseases::PatientsCharacters(true,false,false,37.2,false,false,false,false,true,false,true,false,false,false,false)},//перелом
        {3,Diseases::PatientsCharacters(false,false,true,37.0,false,true,false,false,false,false,false,false,true,false,false)},//грипп
        {4,Diseases::PatientsCharacters(false,false,true,36.6,false,false,false,false,false,false,false,false,false,false,false)},
        {5,Diseases::PatientsCharacters(false,false,true,37.5,false,false,false,false,false,false,false,false,false,false,false)},
        {6,Diseases::PatientsCharacters(false,true,false,36.8,false,false,false,true,false,true,false,false,false,false,false)},//обсессивно-комп. расстр.
        {7,Diseases::PatientsCharacters(false,false,true,37.3,false,false,false,false,true,false,false,false,false,false,false)}//оспа
    };
};

#endif // PATIENTS_H
