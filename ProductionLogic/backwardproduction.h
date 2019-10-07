#ifndef BACKWARDPRODUCTION_H
#define BACKWARDPRODUCTION_H

#include "diseases.h"
#include "patients.h"
#include <list>

class backwardProduction
{
public:
    backwardProduction();
    static std::string solution(const std::string diseasesStr, Diseases diseasesObj, Patients patients);
    static bool isAttitude(const Diseases::PatientsCharacters characters, const Diseases diseasesObj, int diseasenumber);
};

#endif // BACKWARDPRODUCTION_H
