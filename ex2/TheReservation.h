//
// Created by dvir on 11/24/18.
//

#ifndef WORK2_THERESERVATION_H
#define WORK2_THERESERVATION_H

#include "IdSuplier.h"

class TheReservation : public Reservation {
private:
    Customer *customer;
    Flight *flight;
    Classes classes;
    int maxbaggege;
    string idOrder;
public:
    TheReservation(Customer *customer, Flight *flight, Classes classes, int maxbaggege,string &id);

    virtual Customer *getCustomer();

    virtual Flight *getFlight();

    virtual Classes getClass();

    virtual int getMaxBaggage();

    virtual ~TheReservation();

    virtual string getID();
     //virtual ~Reservation() {}
    string stringInformation();
    string getstringClass(Classes classes);
};


#endif //WORK2_THERESERVATION_H
