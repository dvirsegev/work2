//
// Created by dvir on 11/24/18.
//

#include "TheReservation.h"

Customer *TheReservation::getCustomer() {
    return this->customer;
}

Flight *TheReservation::getFlight() {
    return this->flight;
}

Classes TheReservation::getClass() {
    return this->classes;
}

int TheReservation::getMaxBaggage() {
    return this->maxbaggege;
}

TheReservation::TheReservation(Customer *customer, Flight *flight, Classes classes, int maxbaggege,string& id)
: customer(customer), flight(flight), classes(classes), maxbaggege(maxbaggege), idOrder(id) {}

string TheReservation::stringInformation() {
      string s1 = "id-order: " + this->idOrder + " id-customer: " + customer->getID() + " id-flight: "
            + this->flight->getID() +  " class: " + getstringClass(this->classes) + " maxbages: "
            + to_string(maxbaggege);
    return s1;
}


string TheReservation::getstringClass(Classes classes) {
    if(classes == FIRST_CLASS) return "fclass";
    return "sclass";
}

string TheReservation::getID() {
    return this->idOrder;
}

TheReservation::~TheReservation() {

}
