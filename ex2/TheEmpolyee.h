//
// Created by dvir on 11/23/18.
//

#ifndef WORK2_THEEMPOLYEE_H
#define WORK2_THEEMPOLYEE_H

#include "IdSuplier.h"


class TheEmpolyee : public Employee {
private:
    Employee *theboss;
    Jobs jobs;
    int year;
    int seniortiy;
    string id;
public:
    // for reading
    TheEmpolyee(string & idWorker,string employer, Jobs jobs, int year, int seniortiy);

    TheEmpolyee(string &employer, Jobs jobs, int year, int seniortiy,string&id);

    Employee *setemployer(string &s);

    TheEmpolyee(string &s);

    int getSeniority();

    int getBirthYear();

    Employee *getEmployer();

    Jobs getTitle();

    string stringImformation();

    string getID();
    string PrintEnum();
};

#endif //WORK2_THEEMPOLYEE_H
