//
// Created by dvir on 11/25/18.
//

#ifndef WORK2_EMPLOYEETABLE_H
#define WORK2_EMPLOYEETABLE_H

#include <fstream>
#include "TheEmpolyee.h"
#include "TheCustomer.h"
#include "TheFlight.h"
#include "TheReservation.h"
#include "ThePlane.h"

class TableGeneric {
public:
    void writetoFile(string fileName, string string1);

    map<string, TheEmpolyee *> refreshEmp(string fileName);

    map<string, ThePlane *> refreshPlan(string fileName);

    map<string, TheFlight *> refreshFLIGHT(string flightFile, string schedule, map<string, TheEmpolyee *> reciveEmp);

    map<string, TheCustomer *> refreshCus(string fileName);

    map<string, TheReservation *> refreshReservation(string nameFile, map<string, TheFlight *> flights,
                                                     map<string, TheCustomer *> customers);

    list<Employee *> refreshWorkerDate(Date date1, string flightId, string scheduleFile,
                                       map<string, TheEmpolyee *> reciveEmp);

    int getSummary(int i, string fileName);
};
Flight *getFlights(map<string, TheFlight *> flights, string &result);
Customer * getCustomer(map<string,TheCustomer*>customers,string &result);
Jobs getJobs(string string1);

#endif //WORK2_EMPLOYEETABLE_H
