//
// Created by dvir on 11/23/18.
//

#ifndef WORK2_THECUSTOMER_H
#define WORK2_THECUSTOMER_H

#include "IdSuplier.h"

class TheCustomer : public Customer {
private:
    string fullname;
    int priority;
    list<Reservation *> reservations ;
    string id;
public:
    TheCustomer(const string &fullname, int priority, string &id);

    string Information();

    string getID();

    virtual string getFullName();

    virtual int getPriority();

    virtual list<Reservation *> getReservations();

    void setReservations(const list<Reservation *> &reservations);

    string stringInformation();
};


#endif //WORK2_THECUSTOMER_H
