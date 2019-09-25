#ifndef FORWARDPRODUCTION_H
#define FORWARDPRODUCTION_H

#include "diseases.h"

class forwardProduction
{
public:
    forwardProduction();
    static std::pair<std::string,std::string> solution(const Diseases::PatientsCharacters, const Diseases diseasesObj);

private:
    Diseases diseases;
};

#endif // FORWARDPRODUCTION_H
