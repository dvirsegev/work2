//
// Created by dvir on 11/29/18.
//

#include "interface.h"


bool Date::operator<(const Date &d) const {
    int myYear = atoi(date.substr(0, 3).c_str());
    int otherYear = atoi(d.date.substr(0, 3).c_str());
    int myMonth = atoi(date.substr(5, 6).c_str());
    int otherMonth = atoi(d.date.substr(5, 6).c_str());
    int myDay = atoi(date.substr(8, 9).c_str());
    int otherDay = atoi(d.date.substr(8, 9).c_str());
    if (myYear < otherYear)
        return true;
    if (myYear == otherYear && myMonth < otherMonth)
        return true;
    return myYear == otherYear && myMonth == otherMonth && myDay < otherDay;
}

bool Date::operator>(const Date &d) const {
    return (!operator<(d) && !operator==(d));
}

bool Date::operator==(const Date &d) const {
    int myYear = atoi(date.substr(0, 3).c_str());
    int otherYear = atoi(d.date.substr(0, 3).c_str());
    int myMonth = atoi(date.substr(5, 6).c_str());
    int otherMonth = atoi(d.date.substr(5, 6).c_str());
    int myDay = atoi(date.substr(8, 9).c_str());
    int otherDay = atoi(d.date.substr(8, 9).c_str());
    return myYear == otherYear && myMonth == otherMonth && myDay == otherDay;
}

Date::Date(string date) {
    if (date.empty() || date.length() > 13 || date.length() <8 || date.size() == 0 )
        throw runtime_error(string("empty string \n"));
    else
        this->date = std::move(date);
}
