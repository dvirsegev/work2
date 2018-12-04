//
// Created by dvir on 11/23/18.
//

#include "TheEmpolyee.h"


int TheEmpolyee::getSeniority() {
    this->seniortiy;
}

int TheEmpolyee::getBirthYear() {
    this->year;
}

Employee *TheEmpolyee::getEmployer() {
    return this->theboss;
}

Jobs TheEmpolyee::getTitle() {
    return this->jobs;
}


string TheEmpolyee::getID() {
    return id;
}

string TheEmpolyee::stringImformation() {
    string string1 = " id: " + this->id + " boss: " + theboss->getID() + " job: " + PrintEnum()+
            " year: " + to_string(this->year) + " senority: " + to_string(this->seniortiy) + "\n";
    return string1;
}

Employee *TheEmpolyee::setemployer(string &s) {
    return new TheEmpolyee(s);
}

TheEmpolyee::TheEmpolyee(string &s) {
    if(s == "")  this->id = "null";
    else
        this->id = s;
    this->theboss = NULL;
}

TheEmpolyee::TheEmpolyee(string &employer, Jobs jobs, int year, int seniortiy, string &id) {
    this->jobs = jobs;
    this->year = year;
    this->seniortiy = seniortiy;
    this->id =id;
    this->theboss = setemployer(employer);
}
string TheEmpolyee::PrintEnum() {
    switch (this->jobs) {
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

TheEmpolyee::TheEmpolyee(string &idWorker, string employer, Jobs jobs, int year, int seniortiy) {
    this->theboss = setemployer(employer);
    this->jobs = jobs;
    this->year = year;
    this->seniortiy = seniortiy;
    this->id = idWorker;
}

