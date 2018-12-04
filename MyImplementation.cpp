#include <utility>

#include "MyImplementation.h"

/**
     * @param seniority
     * @param birth_year
     * @param employer_id
     * @param title
     * @return new employee and add it to the map.
     */
Employee *MyImplementation::addEmployee(int seniority, int birth_year, string employer_id, Jobs title) {
    map<string, TheEmpolyee *> refresh = tableGeneric.refreshEmp(TEXTEMP);
    this->reciveEmp = refresh;
    string id = idSuplier.genID();
    auto *worker = new TheEmpolyee(employer_id, title, birth_year, seniority, id);
    if (check(worker)) exit();
    else {
        this->reciveEmp.insert(pair<string, TheEmpolyee *>(worker->getID(), worker));
        tableGeneric.writetoFile(TEXTEMP, worker->stringImformation());
    }
    return worker;
}

/**
* @param id
* @return the empley with this id else return NUll.
*/
Employee *MyImplementation::getEmployee(string id) {
    this->reciveEmp = tableGeneric.refreshEmp(TEXTEMP);
    Employee *employee = nullptr;
    for (auto const &item : reciveEmp) {
        if (item.first == id) {
            employee = item.second;
        }
    }
    return employee;
}

/**
 *
 * @param model_number
 * @param crew_needed
 * @param max_passangers
 * @return new plane.
 */
Plane *MyImplementation::addPlane(int model_number, map<Jobs, int> crew_needed, map<Classes, int> max_passangers) {
    map<string, ThePlane *> refresh = tableGeneric.refreshPlan(TEXTPLANE);
    this->recivePlan = refresh;
    string id = idSuplier.genID();
    auto *plane = new ThePlane(model_number, max_passangers, crew_needed, id);
    this->recivePlan.insert(pair<string, ThePlane *>(plane->getID(), plane));
    tableGeneric.writetoFile(TEXTPLANE, plane->stringInformation());
    return plane;
}

Plane *MyImplementation::getPlane(string id) {
    this->recivePlan = tableGeneric.refreshPlan(TEXTPLANE);
    ThePlane *plane = nullptr;
    for (auto const &item : recivePlan) {
        if (item.first == id) {
            plane = item.second;
        }
    }
    return plane;
}

ThePlane *MyImplementation::CheckPlanOfTheFlight(int number) {
    for (auto const &item : recivePlan) {
        if (item.second->getModelNumber() == number)
            return item.second;
    }
    throw std::invalid_argument("there is no plain in this model");
}

void MyImplementation::CheckDateOfFlight(Date date, int howmanymodels, ThePlane *plane) {
    for (auto const &flight:reciveFlight) {
        if (flight.second->getDate().getDate() == date.getDate()) {
            if (flight.second->getModelNumber() == plane->getModelNumber()) {
                howmanymodels--;
                if(howmanymodels <= 0)
                    throw runtime_error(string("there is no place for this flight!\n"));
            }
        }
    }
}

Flight *MyImplementation::addFlight(int model_number, Date date, string source, string destination) {
    // refresh all the employees
    reciveEmp = tableGeneric.refreshEmp(TEXTEMP);
    // refresh all the flight from the file.
    reciveFlight = tableGeneric.refreshFLIGHT(TEXTFLIGHT, SCHEDULE, reciveEmp);
    // upload the plans from the file.
    this->recivePlan = tableGeneric.refreshPlan(TEXTPLANE);
    // check there is a model like we want.
    ThePlane *plane = CheckPlanOfTheFlight(model_number);
    // check there is a "open sky" in this date.
    int howmanymodels = tableGeneric.getSummary(model_number, TEXTPLANE);
    CheckDateOfFlight(date, howmanymodels, plane);
    string idFlight = idSuplier.genID();
    list<Employee *> workers = getWorker(plane, date);
    // create new file.
    auto *flight = new TheFlight(model_number, workers, date, source, destination, idFlight);
    // reduce the free sit's by 1 in fclass/sclass.
    flight->setPlaces(plane);
    // write the flight on the flight.
    tableGeneric.writetoFile(TEXTFLIGHT, flight->printinformation());
    printonSchedule(workers, date, idFlight);
    return flight;
}

void MyImplementation::printonSchedule(list<Employee *> workers, Date date, string idFlight) {
    for (auto const &employee:workers) {
        string s = "idemployee: " + employee->getID() + " date: " + date.getDate() + " idFlight: " + idFlight + "\n";
        tableGeneric.writetoFile(SCHEDULE, s);
    }
}

Flight *MyImplementation::getFlight(string id) {
    // refresh all the employees
    reciveEmp = tableGeneric.refreshEmp(TEXTEMP);
    this->reciveFlight = tableGeneric.refreshFLIGHT(TEXTFLIGHT, SCHEDULE, reciveEmp);
    TheFlight *flight = nullptr;
    for (auto const &item:reciveFlight) {
        if (item.first == id) {
            flight = item.second;
            flight->setReservations(item.second->getReservations());
            flight->setListofCrew(item.second->getAssignedCrew());

        }
    }
    return flight;
}

/**
 * @param full_name
 * @param priority
 * @return new customer.
 */
Customer *MyImplementation::addCustomer(string full_name, int priority) {
    if (priority > 5 || priority < 0) throw std::invalid_argument("error priority");
    string id = this->idSuplier.genID();
    TableGeneric tableGeneric;
    this->reciveCus = tableGeneric.refreshCus(TEXTCUS);
    auto *customer = new TheCustomer(full_name, priority, id);
    this->reciveCus.insert(pair<string, TheCustomer *>(customer->getID(), customer));
    tableGeneric.writetoFile(TEXTCUS, customer->Information());
    return customer;
}

/**
 *
 * @param id
 * @return the customer with this id
 */
Customer *MyImplementation::getCustomer(string id) {
    this->reciveCus = tableGeneric.refreshCus(TEXTCUS);
    Customer *customer = nullptr;
    for (auto const &item : reciveCus) {
        if (item.first == id) {
            customer = item.second;
        }
    }
    return customer;
}

/**
 *
 * @param customer the list of the customer
 * @param resev the list of the resevation
 * for every customer, set his resevations.
 */
void setResevationCustomer(map<string, TheCustomer *> customer, map<string, TheReservation *> resev) {
    std::list<Reservation *> reservation;
    for (auto const &people:customer) {
        for (auto const &item:resev) {
            if (people.second == item.second->getCustomer())
                reservation.push_back(item.second);
        }
        people.second->setReservations(reservation);

    }
}

void setResevationFlight(map<string, TheFlight *> listflights, map<string, TheReservation *> resev) {
    std::list<Reservation *> reservation;
    for (auto const &flight:listflights) {
        for (auto const &item:resev) {
            if (flight.second == item.second->getFlight())
                reservation.push_back(item.second);
        }
        flight.second->setReservations(reservation);

    }
}

Reservation *MyImplementation::addResevation(string customerId, string flightId, Classes cls, int max_baggage) {
    TheReservation *reservation = nullptr;
    // order is okay.
    if (!CheckOrder(customerId, flightId, cls, max_baggage)) throw runtime_error(string("error input"));
    else {
        // get customer and the flight he want to order.
        Customer *customer = getCustomer(customerId);
        TheFlight *flight = dynamic_cast<TheFlight *>(getFlight(flightId));
        // check if there is a place in the class he want
        if (!CheckPlace(flight, cls)) throw std::invalid_argument("there is no place in this flight");
        map<string, TheFlight *> tempFLIGHT = this->reciveFlight;
        map<string, TheCustomer *> tempCUS = this->reciveCus;
        // reload the table of reservation.
        reciveResev = tableGeneric.refreshReservation(TEXTRESEVERTION, tempFLIGHT, tempCUS);
        // put all the orders the customer have
        setResevationCustomer(reciveCus, reciveResev);
        // put all the orders that have to this flight.
        setResevationFlight(reciveFlight, reciveResev);
        IdSuplier idSuplier1;
        if (flight == nullptr || customer == nullptr)throw std::invalid_argument("error input");
        else {
            string id = idSuplier1.genID();
            // create new reservation.
            reservation = new TheReservation(customer, flight, cls, max_baggage, id);
            // enter the order to the reciveresv.
            this->reciveResev.insert(pair<string, TheReservation *>(reservation->getID(), reservation));
            // write to the file.
            tableGeneric.writetoFile(TEXTRESEVERTION, reservation->stringInformation());
        }
    }
    return reservation;
}

/**
 * @param pFlight
 * @param classes
 * @return  checkPlace in the flight.
 */
bool MyImplementation::CheckPlace(TheFlight *pFlight, Classes classes) {
    switch (classes) {
        case FIRST_CLASS:
            if (pFlight->getMaxFirstClass() > 0) {
                pFlight->decPlaceClass(classes);
                return true;
            }
        case SECOND_CLASS:
            if (pFlight->getMaxEconomyClass() > 0)
                pFlight->decPlaceClass(classes);
            return true;
        default:
            return false;
    }
}

/**
 *
 * @param id order.
 * @return the order itself.
 */
Reservation *MyImplementation::getReservation(string id) {
    this->reciveFlight = tableGeneric.refreshFLIGHT(TEXTFLIGHT, SCHEDULE, reciveEmp);
    this->reciveCus = tableGeneric.refreshCus(TEXTCUS);
    this->reciveResev = tableGeneric.refreshReservation(TEXTRESEVERTION, reciveFlight, reciveCus);
    Reservation *reservation = nullptr;
    for (auto const &item : reciveResev) {
        if (item.first == id)
            reservation = item.second;
    }
    return reservation;
}

/**
 * release memory and finish the program.
 */
void MyImplementation::exit() {
    this->reciveResev.clear();
    this->reciveCus.clear();
    this->reciveFlight.clear();
    this->recivePlan.clear();
    this->reciveEmp.clear();
}

int MyImplementation::check(TheEmpolyee *pEmpolyee) {
    for (auto const &item : reciveEmp) {
        if (item.second->getID() == pEmpolyee->getID()) {
            return 1;
        }
    }
    return 0;
}

bool MyImplementation::CheckOrder(string &customerId, string &flightId, Classes classes, int baggage) {
    reciveCus = tableGeneric.refreshCus(TEXTCUS);
    reciveFlight = tableGeneric.refreshFLIGHT(TEXTFLIGHT, SCHEDULE, this->reciveEmp);
    if (baggage < 0) return false;
    return (reciveCus.find(customerId) != reciveCus.end()) && (reciveFlight.find(flightId) != reciveFlight.end());
}

list<Employee *> MyImplementation::getWorker(ThePlane *pPlane, Date date) {
    list<Employee *> employyes;
    int maxWorker = 0;
    map<string, TheEmpolyee *> workerscanWork = reciveEmp;
    list<Employee *> alreadywork = getWorkThatDay(std::move(date));
    map<string, TheEmpolyee *>::iterator it;
    for (auto const &person : alreadywork) {
        workerscanWork.erase(person->getID());
    }
    for (auto const &item : pPlane->getCrewNeeded()) {
        maxWorker += item.second;
        int i = 0;
        if (item.second == 0)
            continue;
        switch (item.first) {
            case PILOT: {
                for (auto const &person:workerscanWork) {
                    if (i == item.second) break;
                    if (person.second->getTitle() == PILOT) {
                        employyes.push_back(person.second);
                        i++;
                    }
                }
                break;
            }
            case NAVIGATOR: {
                for (auto const &person:workerscanWork) {
                    if (i == item.second) break;
                    if (person.second->getTitle() == NAVIGATOR) {
                        employyes.push_front(person.second);
                        i++;
                    }
                }
                break;
            }
            case FLY_ATTENDANT: {
                for (auto const &person:workerscanWork) {
                    if (i == item.second) break;
                    if (person.second->getTitle() == FLY_ATTENDANT) {
                        employyes.push_back(person.second);
                        i++;
                    }
                }
                break;
            }
            case MANAGER: {
                int i = 0;
                for (auto const &person:workerscanWork) {
                    if (i == item.second) break;
                    if (person.second->getTitle() == MANAGER) {
                        employyes.push_back(person.second);
                        i++;
                    }
                }
                break;
            }
            default:
                for (auto const &person:workerscanWork) {
                    if (i == item.second) break;
                    if (person.second->getTitle() == PILOT) {
                        employyes.push_back(person.second);
                        i++;
                    }
                }
        }
    }
    if (employyes.size() != maxWorker) throw invalid_argument("not enought worker for this flight!\n");
    return employyes;
}

list<Employee *> MyImplementation::getWorkThatDay(Date date) {
    list<Employee *> employeess;
    for (auto const &flights: reciveFlight) {
        if (flights.second->getDate() == date) {
            for (auto const &person: flights.second->getAssignedCrew()) {
                employeess.push_back(person);
            }
        }
    }
    return employeess;
}

