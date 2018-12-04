//
// Created by dvir on 11/23/18.
//

#ifndef WORK2_THEFLIGHT_H
#define WORK2_THEFLIGHT_H

#include "interface.h"

class TheFlight : public Flight {
private:
    int modelNumber;
    list<Reservation *> resevation;
    list<Employee *> listofCrew;
    Date date;
    string source;
    string destination;
    string id;
    int maxFirstClass;
    int maxEconomyClass;
public:

    TheFlight(int modelNumber, const list<Employee *> &crew, const Date &date,
              const string &source, const string &destination, string &id);

    virtual int getModelNumber();

    virtual list<Reservation *> getReservations();

    virtual list<Employee *> getAssignedCrew();

    virtual Date getDate();

    virtual string getSource();

    virtual string getDestination();

    virtual string getID();

    string printinformation();

    void setReservations(list<Reservation *> list);

    void setPlaces(Plane *plane);

    int getMaxFirstClass() const;

    int getMaxEconomyClass() const;

    void decPlaceClass(Classes classes);

    void setListofCrew(const list<Employee *> &listofCrew);
};

#endif //WORK2_THEFLIGHT_H
