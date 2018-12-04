
//
// Created by dvir on 11/23/18.
//

#include "TheCustomer.h"


string TheCustomer::getFullName() {
    return this->fullname;
}

int TheCustomer::getPriority() {
    return this->priority;
}

list<Reservation *> TheCustomer::getReservations() {
    return this->reservations;
}

string TheCustomer::Information() {
    string string1 = " id: " + this->id + " fullname: " + fullname + " priority: " + to_string(priority) + "\n";
    return string1;
}

string TheCustomer::getID() {
    return this->id;
}

TheCustomer::TheCustomer(const string &fullname, int priority, string &id) {
    this->priority = priority;
    this->fullname = fullname;
    this->id = id;
}

void TheCustomer::setReservations(const list<Reservation *> &reservations) {
    TheCustomer::reservations = reservations;
}

string TheCustomer::stringInformation() {
    string string1 = "id: " + this->id + " fullname: " + this->fullname + " priority " + to_string(priority) + "\n";
    return string1;
}
