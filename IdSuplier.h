//s
// Created by dvir on 11/27/18.
//

#ifndef WORK2_IDSUPLIER_H
#define WORK2_IDSUPLIER_H

#include "interface.h"
#define  ID  "id.txt"
class IdSuplier {
    string id;
public:

    const string &getId() const;
    string genID();
};


#endif //WORK2_IDSUPLIER_H
