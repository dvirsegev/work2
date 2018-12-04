//
// Created by dvir on 11/27/18.
//

#include <fstream>
#include "IdSuplier.h"


const string &IdSuplier::getId() const {
    return id;
}

 void inc(int i) {
    std::ofstream file;
    file.open(ID);
    i++;
    file << i;
    file.close();
}
/** this function return a number, that stored in a file and incrce it in one.
 that let a just one source of ID's*/
string IdSuplier ::genID() {
    int i =1;
    std::ifstream file;
    file.open(ID);
    file >>i;
    this->id = to_string(i);
    file.close();
    inc(i);
    return to_string(i);
    }