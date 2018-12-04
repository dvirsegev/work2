//
// Created by dvir on 11/23/18.
//

#include "ThePlane.h"

int ThePlane::getModelNumber() {
    return this->modelnumber;
}

map<Jobs, int> ThePlane::getCrewNeeded() {
    return crew;
}

int ThePlane::getMaxFirstClass() {
    return this->classes.find(FIRST_CLASS)->second;
}

int ThePlane::getMaxEconomyClass() {
    return this->classes.find(SECOND_CLASS)->first;
}

ThePlane::ThePlane(int modelnumber, const map<Classes, int> &classes, const map<Jobs, int> &crew, string&id)
        : modelnumber(
        modelnumber), classes(classes), crew(crew) {
    this->id = id;
}

string ThePlane::getID() {
    return this->id;
}

string ThePlane::stringInformation() {
    string string1 = " id: " + this->id + " model: " + to_string(modelnumber) + " fclass: " +
                     to_string(classes.find(FIRST_CLASS)->second) + " sclass: " +
                     to_string(classes.find(SECOND_CLASS)->second);
    for (const auto &item : crew) {
        string1 += " need: " + to_string(item.second) + " job: " + PrintEnum(item.first) ;
    }
    string1 +="\n";
    return string1;
}

string ThePlane::PrintEnum(Jobs jobs) {
    switch (jobs) {
        case (MANAGER):
            return "manager";
        case (NAVIGATOR):
            return "navigator";
        case (FLY_ATTENDANT):
            return "fly_attendant";
        case (PILOT):
            return "pilot";
        default:
            return "other";

    }
}

ThePlane::~ThePlane() {
}
