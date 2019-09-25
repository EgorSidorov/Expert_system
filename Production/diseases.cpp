#include "diseases.h"

Diseases::Diseases()
{

}

void Diseases::addDiseaseTreatment(const std::string disease, const std::string treatment)
{
    diseases.push_back(disease);
    diseases_treatments.insert({diseases.size() - 1, treatment});
}

std::string Diseases::getDisease(const int number) const
{
    if(diseases.size() > number)
        return *std::next(diseases.begin(), number);
    else
        return "";
}

int Diseases::getNumber(std::string desease)
{
    int number = 0;
    for(auto iter : diseases){
        if(iter == desease)
            return number;
        number++;
    }
    return -1;
}

std::string Diseases::getTreatment(const int number) const
{
    if(diseases_treatments.find(number) != diseases_treatments.end())
        return diseases_treatments.find(number)->second;
}

std::string Diseases::getTreatment(const std::string disease) const
{
    int number = 0;
    for(const std::string value : diseases){
        if(value == disease){
            return getTreatment(number);
        }
        number++;
    }
    return "";
}

int Diseases::getCount() const
{
    return diseases_treatments.size();
}

void Diseases::removeDisease(const int number)
{
    diseases.remove(diseases_treatments[number]);
    diseases_treatments.erase(number);
}

