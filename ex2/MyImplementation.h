//
// Created by dvir on 11/27/18.
//

#ifndef WORK2_MYIMPLEMENTATION_H
#define WORK2_MYIMPLEMENTATION_H

#include "IdSuplier.h"
#include "TableGeneric.h"
#include <iostream>

#define  TEXTEMP "employye.txt"
#define TEXTPLANE "plane.txt"
#define TEXTCUS "cust.txt"
#define TEXTFLIGHT "flight.txt"
#define TEXTRESEVERTION "resevertion.txt"
#define SCHEDULE "schedule.txt"


class MyImplementation : public Ex2 {
private:
    map<string, TheEmpolyee *> reciveEmp;
    map<string, ThePlane *> recivePlan;
    map<string, TheCustomer *> reciveCus;
    map<string, TheReservation *> reciveResev;
    map<string, TheFlight *> reciveFlight;
    IdSuplier idSuplier;
    TableGeneric tableGeneric;
public:
    Employee *addEmployee(
            int seniority,
            int birth_year,
            string employer_id,
            Jobs title);

    Employee *getEmployee(string id);

    Plane *addPlane(
            int model_number,
            map<Jobs, int> crew_needed,
            map<Classes, int> max_passangers);

    Plane *getPlane(string id);

    Flight *addFlight(
            int model_number,
            Date date,
            string source,
            string destination);

    Flight *getFlight(string id);

    Customer *addCustomer(
            string full_name,
            int priority);

    Customer *getCustomer(string id);

    Reservation *addResevation(
            string customerId,
            string flightId,
            Classes cls,
            int max_baggage);

    Reservation *getReservation(string id);

    void exit();

    int check(TheEmpolyee *pEmpolyee);

    ThePlane *CheckPlanOfTheFlight(int number);

    bool CheckOrder(string &customerId, string &flightId, Classes classes, int baggage);

    bool CheckPlace(TheFlight *pFlight, Classes classes);

    void CheckDateOfFlight(Date date, int howmanymodels, ThePlane *plane);

    list<Employee *> getWorker(ThePlane *pPlane, Date date);

    list<Employee *> getWorkThatDay(Date date);
    void printonSchedule(list < Employee * > workers,Date date,string idFlight);

    int getSummary(int number);
};

#endif //WORK2_MYIMPLEMENTATION_H
