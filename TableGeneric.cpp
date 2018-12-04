//
// Created by dvir on 11/25/18.
//

#include <cstring>
#include "TableGeneric.h"

/**
 *
 * @param fileName name of the file
 * @param string1 the output
 */
void TableGeneric::writetoFile(string fileName, string string1) {
    fstream file;
    file.open(fileName, fstream::out | fstream::app);
    file << string1;
    file.close();
}

/**
 *
 * @param fileName
 * @return map of stringID and employee.
 */
map<string, TheEmpolyee *> TableGeneric::refreshEmp(string fileName) {
    map<string, TheEmpolyee *> restore;
    string type, result, bossid, id;
    fstream file;
    int year = 0, senority = 0, count = 0;
    Jobs jobs = OTHER;
    // check if file is open
    if (!file.is_open()) {
        file.open(fileName, fstream::in | fstream::app);
    }
    // type- first word, result - second word
    while (file >> type >> result) {
        if (type == "job:") {
            jobs = getJobs(result);
        }
        if (type == "boss:") {
            bossid = result;
        }
        if (type == "year:") {
            year = stoi(result);
        }
        if (type == "senority:") {
            senority = stoi(result);
        }
        if (type == "id:") {
            id = (result);
        }
        count++;
        // create new employee
        if (count == 5) {
            TheEmpolyee *employee = new TheEmpolyee(id, bossid, jobs, year, senority);
            restore.insert((std::pair<string, TheEmpolyee *>(id, employee)));
            count = 0;
        }
    }
    file.close();
    return restore;
}
int TableGeneric::getSummary(int model, string fileName) {
    int count = 0;
    fstream file;
    if (!file.is_open()) {
        file.open(fileName, fstream::in | fstream::app);
    }
    string result, type;
    int text;
    while (file >> type >> result) {
        if(type == "model:") {
            text = stoi(result);
            if(text == model)
                count++;
        }
    }
    file.close();
    return count;
}
/**
 *
 * @param fileName name of the file
 * @return map of string and Planes.
 */
map<string, ThePlane *> TableGeneric::refreshPlan(string fileName) {
    map<string, ThePlane *> restore;
    fstream file;
    int model = 0, count = 0, fclass = 0, sclass = 0, need = 0;
    string result, type, id;
    map<Jobs, int> jobs;
    Jobs job = OTHER;
    if (!file.is_open()) {
        file.open(fileName, fstream::in | fstream::app);
    }
    while (file >> type >> result) {
        if (type == "model:") {
            model = stoi(result);
        }
        if (type == "id:") {
            id = result;
        }
        if (type == "fclass:") {
            fclass = stoi(result);
        }
        if (type == "sclass:") {
            sclass = stoi(result);
        }
        if (type == "need:") {
            need = stoi(result);
        }
        if (type == "job:") {
            job = getJobs(result);
            jobs[job] = need;
        }
        count++;
        if (count == 14) {
            jobs[job] = need;
            map<Classes, int> classes;
            classes[FIRST_CLASS] = fclass;
            classes[SECOND_CLASS] = sclass;
            ThePlane *plan = new ThePlane(model, classes, jobs, id);
            restore.insert((std::pair<string, ThePlane *>(id, plan)));
            count = 0;
        }
    }
    file.close();
    return restore;
}

// auto *flight = new TheFlight(model_number, workers, date, source, destination, idFlight);
//string s1 = "idFlight:" + id + "model:" + to_string(modelNumber) + "date" + date.getDate() + "source" +
//                source + "dest" + destination;
map<string, TheFlight *>
TableGeneric::refreshFLIGHT(string flightFile, string scheduleFile, map<string, TheEmpolyee *> reciveEmp) {
    map<string, TheFlight *> restore;
    string type, result, id, source, destination, date;
    fstream file;
    int model = 0, count = 0;
    if (!file.is_open()) {
        file.open(flightFile, fstream::in | fstream::app);
    }
    // read the file and create the flight.
    while (file >> type >> result) {
        if (type == "source:") {
            source = result;
        }
        if (type == "model:") {
            model = stoi(result);
        }
        if (type == "idFlight:") {
            id = (result);
        }
        if (type == "date:") {
            date = result;
        }
        if (type == "destination:") {
            destination = result;
        }
        count++;
        // if we read all the line.
        if (count == 5) {
            Date date1(date);
            list<Employee *> workers = refreshWorkerDate(date1, id, scheduleFile, reciveEmp);
            auto *flight = new TheFlight(model, workers, date1, source, destination, id);
            restore.insert((pair<string, TheFlight *>(id, flight)));
            count = 0;
        }
    }
    file.close();
    return restore;
}

list<Employee *> TableGeneric::refreshWorkerDate(Date date1, string flightId, string scheduleFile,
                                                 map<string, TheEmpolyee *> reciveEmp) {
    fstream file;
    list<Employee *> emplooyees;
    int count = 0;
    string type, result, idFlight, idWorker, date;
    if (!file.is_open()) {
        file.open(scheduleFile, fstream::in | fstream::app);
    }
    // read the file and create the date.
    while (file >> type >> result) {
        if (type == "idemployee:") {
            idWorker = result;
        }
        if (type == "date:") {
            date = result;
        }
        if (type == "idFlight:") {
            idFlight = result;
        }
        count++;
        // if we read all the line.
        if (count == 3) {
            if ((date1.getDate() == date) && (flightId == idFlight)) {
                for (auto const &person:reciveEmp) {
                    if (person.first == idWorker) {
                        emplooyees.push_back(person.second);
                    }
                }
            }
            count = 0;
        }
    }
    file.close();
    return emplooyees;
}

/**
 * @param fileName name of the file
 * @return map of stringID and Customers.
 */
map<string, TheCustomer *> TableGeneric::refreshCus(string fileName) {
    map<string, TheCustomer *> restore;
    string type, result, fullname, id;
    fstream file;
    int priority = 0, count = 0;
    if (!file.is_open()) {
        file.open(fileName, fstream::in | fstream::app);
    }
    while (file >> type >> result) {
        if (type == "fullname:") {
            fullname = result;
        }
        if (type == "priority:") {
            priority = stoi(result);
        }
        if (type == "id:") {
            id = (result);
        }
        count++;
        if (count == 3) {
            TheCustomer *cus = new TheCustomer(fullname, priority, id);
            restore.insert((pair<string, TheCustomer *>(id, cus)));
            count = 0;
        }
    }
    return restore;
}

map<string, TheReservation *> TableGeneric::refreshReservation(string fileName, map<string, TheFlight *> flights,
                                                               map<string, TheCustomer *> customers) {
    map<string, TheReservation *> restore;
    string type, result, idRes;
    fstream file;
    Customer *customer = nullptr;
    Classes classes = SECOND_CLASS;
    Flight *flight = nullptr;
    int maxBags = 0, count = 0;
    if (!file.is_open()) {
        file.open(fileName, fstream::in | fstream::app);
    }
    while (file >> type >> result) {
        if (type == "fclass:") {
            classes = FIRST_CLASS;
        }
        if (type == "Sclass:") {
            classes = SECOND_CLASS;
        }
        if (type == "maxbages:") {
            maxBags = stoi(result);
        }
        if (type == "id-order:") {
            idRes = (result);
        }
        if (type == "id-flight:") {
            flight = getFlights(flights, result);
        }
        if (type == "id-customer:") {
            customer = getCustomer(customers, result);
        }
        count++;
        if (count == 5) {
            auto *pReservation = new TheReservation(customer, flight, classes, maxBags, idRes);
            restore.insert((pair<string, TheReservation *>(idRes, pReservation)));
            count = 0;
        }
    }
    return restore;
}



Flight *getFlights(map<string, TheFlight *> flights, string &result) {
    for (auto const &flight:flights) {
        if (flight.first == result)
            return flight.second;
    }
    return nullptr;
}

Customer *getCustomer(map<string, TheCustomer *> customers, string &result) {
    for (auto const &cus:customers) {
        if (cus.first == result)
            return cus.second;
    }
    return nullptr;
}

/**
 * @param string1 name of work
 * @return the JOB.
 */
Jobs getJobs(string string1) {
    if (string1 == "manager") return MANAGER;
    if (string1 == "navigator") return NAVIGATOR;
    if (string1 == "fly_attendant") return FLY_ATTENDANT;
    if (string1 == "pilot") return PILOT;
    return OTHER;
}
