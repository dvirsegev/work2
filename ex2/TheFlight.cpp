#include <utility>


#include "TheFlight.h"

TheFlight::TheFlight(int modelNumber, const list<Employee *> &crew,
                     const Date &date, const string &source, const string &destination,
                     string &id) : modelNumber(modelNumber), listofCrew(crew), date(date), source(source),
                                   destination(destination), id(id) {}

int TheFlight::getModelNumber() {
    return this->modelNumber;
}

list<Reservation *> TheFlight::getReservations() {
    return this->resevation;
}

list<Employee *> TheFlight::getAssignedCrew() {
    return this->listofCrew;
}

Date TheFlight::getDate() {
    return this->date;
}

string TheFlight::getSource() {
    return this->source;
}

string TheFlight::getDestination() {
    return this->destination;
}

string TheFlight::getID() {
    return this->id;
}

string TheFlight::printinformation() {
    string s1 = "idFlight: " + id + " model: " + to_string(modelNumber) + " date: " + date.getDate() + " source: " +
                source + " destination: " + destination + "\n";
    return s1;
}

void TheFlight::setListofCrew(const list<Employee *> &listofCrew) {
    TheFlight::listofCrew = listofCrew;
}

void TheFlight::setReservations(list<Reservation *> list) {
    this->resevation = std::move(list);

}

void TheFlight::setPlaces(Plane *plane) {
    this->maxFirstClass = plane->getMaxFirstClass();
    this->maxEconomyClass = plane->getMaxEconomyClass();
}

int TheFlight::getMaxFirstClass() const {
    return maxFirstClass;
}

int TheFlight::getMaxEconomyClass() const {
    return maxEconomyClass;
}

void TheFlight::decPlaceClass(Classes classes) {
    switch (classes) {
        case FIRST_CLASS :
            this->maxFirstClass--;
            break;
        case SECOND_CLASS:
            this->maxEconomyClass--;
    }
}
