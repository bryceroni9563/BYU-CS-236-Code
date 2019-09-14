#include "Scheme.h"

Scheme::Scheme() {
    
}

std::string Scheme::toString() {
    stringstream ss;
    for (unsigned i = 0; i < this->size(); i++) {
        ss << this->at(i);
    }
    return ss.str();
}
