#ifndef SCHEME_H
#define SCHEME_H
#include <string>
#include <sstream>
#include <vector>

using std::string;
using std::stringstream;

class Scheme : public std::vector<string> {
public:
    Scheme();
    string toString();
};

#endif
