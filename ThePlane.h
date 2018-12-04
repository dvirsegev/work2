//
// Created by dvir on 11/23/18.
//

#ifndef WORK2_THEPLANE_H
#define WORK2_THEPLANE_H

#include "IdSuplier.h"

class ThePlane : public Plane {
private:
    int modelnumber;
    map<Classes,int > classes;
    map<Jobs, int> crew;
    string id;
public:
    ThePlane(int modelnumber, const map<Classes,int>&classes, const map<Jobs, int> &crew,string& id);

    virtual int getModelNumber();

    virtual map<Jobs, int> getCrewNeeded();

    string getID();

    virtual int getMaxFirstClass();

    virtual ~ThePlane();

    virtual int getMaxEconomyClass();
    string PrintEnum(Jobs jobs);
    string stringInformation();
};


#endif //WORK2_THEPLANE_H
