#include "forwardproduction.h"

forwardProduction::forwardProduction()
{

}

std::pair<std::string,std::string> forwardProduction::solution(const Diseases::PatientsCharacters patientCharacters, const Diseases diseasesObj)
{
    //невыясненное
    int number = 9;
    //
    if(patientCharacters.trauma){
        if(patientCharacters.vosp && (patientCharacters.rush || patientCharacters.temperature > 36.8) && !patientCharacters.blooding)
            number = 7;//вывих
        else if(patientCharacters.vosp && patientCharacters.blooding)
            number = 3;//перелом
        else if(patientCharacters.iszo && patientCharacters.stomachache)
            number = 2;//язва
        else if(patientCharacters.vosp || patientCharacters.iszo || patientCharacters.blooding || patientCharacters.temperature > 36.8 || patientCharacters.rush){
            number = 8;//здоров
        }
    }
    if(patientCharacters.mental){
         if((patientCharacters.aggression || patientCharacters.nerv) && patientCharacters.stra)
             number = 0;//ОБСЕССИВНО-КОМПУЛЬСИВНОЕ РАССТРОЙСТВО
         else if(patientCharacters.lowweight && patientCharacters.stomachache && (patientCharacters.headache || patientCharacters.aggression || patientCharacters.nerv))
             number = 5;//анорексия
         else if(patientCharacters.lowweight || patientCharacters.aggression || patientCharacters.nerv){
             number = 8;//здоров
         }
    }
    if(patientCharacters.virus){
        if(patientCharacters.rush && patientCharacters.temperature > 36.8)
            number = 6;//ветряная оспа
        else if(patientCharacters.temperature > 36.8 && (patientCharacters.cough || patientCharacters.headache))
            number = 1;//грипп
        else if(patientCharacters.temperature < 36.8 && !patientCharacters.cough && !patientCharacters.headache && !patientCharacters.rush)
            number = 8;//полностью здоров

    }
    std::pair<std::string,std::string> result{diseasesObj.getDisease(number),diseasesObj.getTreatment(number)};
    return result;
}
