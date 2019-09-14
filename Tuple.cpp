#include "Tuple.h"

std::string Tuple::toString(){
    std::stringstream ss;
    for (unsigned i = 0; i < this->size(); i++) {
        ss << this->at(i);
    }
    return ss.str();
}


