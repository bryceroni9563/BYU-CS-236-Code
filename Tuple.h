#ifndef TUPLE_H
#define TUPLE_H
#include <string>
#include <sstream>
#include <vector>

using std::string;

class Tuple : public std::vector<string> {
public:
    string toString();
};

#endif
