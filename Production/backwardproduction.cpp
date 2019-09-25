#include "backwardproduction.h"


backwardProduction::backwardProduction()
{

}

std::string backwardProduction::solution(const std::string diseasesStr, Diseases diseasesObj, Patients patients){
    std::string result;
    for(int iter1 = 0; iter1 < patients.getCount(); iter1++){
        const Diseases::PatientsCharacters characters = patients.getPatientCharacters(iter1);
        if(isAttitude(characters,diseasesObj,diseasesObj.getNumber(diseasesStr))){
           if(result.empty())
               result += patients.getPatient(iter1);
           else
               result += ","+patients.getPatient(iter1);
        }
    }
    diseasesObj.getTreatment(diseasesStr);
    return result;
}

bool backwardProduction::isAttitude(const Diseases::PatientsCharacters patientCharacters,const Diseases diseasesObj,int number){
    if(patientCharacters.trauma){
        if((patientCharacters.vosp && (patientCharacters.rush || patientCharacters.temperature > 36.8) && !patientCharacters.blooding) && number== 7)
            return true;//вывих
        else if((patientCharacters.vosp && patientCharacters.blooding) && number== 3)
            return 3;//перелом
        else if((patientCharacters.iszo && patientCharacters.stomachache) && number== 2)
            return true;//язва
        else if((patientCharacters.vosp || patientCharacters.iszo || patientCharacters.blooding || patientCharacters.temperature > 36.8 || patientCharacters.rush) && number== 8){
            return true;//здоров
        } else if(number == 9) return true;
    }
    if(patientCharacters.mental){
         if(((patientCharacters.aggression || patientCharacters.nerv) && patientCharacters.stra) && number== 0)
             return true;//ОБСЕССИВНО-КОМПУЛЬСИВНОЕ РАССТРОЙСТВО
         else if((patientCharacters.lowweight && patientCharacters.stomachache && (patientCharacters.headache || patientCharacters.aggression || patientCharacters.nerv)) && number== 5)
             return true;//анорексия
         else if((patientCharacters.lowweight || patientCharacters.aggression || patientCharacters.nerv) && number== 8){
             return true;//здоров
         } else if(number == 9) return true;
    }
    if(patientCharacters.virus){
        if((patientCharacters.rush && patientCharacters.temperature > 36.8) && number== 6)
            return true;//ветряная оспа
        else if((patientCharacters.temperature > 36.8 && (patientCharacters.cough || patientCharacters.headache)) && number== 1)
            return true;//грипп
        else if((patientCharacters.temperature < 36.8 && !patientCharacters.cough && !patientCharacters.headache && !patientCharacters.rush) && number== 8)
            return true;//полностью здоров
        else if(number == 9) return true;

    }
    return false;
}
