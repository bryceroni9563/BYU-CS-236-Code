#ifndef PREDICATE_H
#define PREDICATE_H

#include "Parameter.h"
#include <vector>
#include <sstream>

using std::string;
using std::vector;
using std::stringstream;

class Predicate {
	string id;
    vector<Parameter> paramList;
public:
	Predicate();
	Predicate(string ident);
	Predicate(string ident, vector<Parameter> newList);
	string getID();
	vector<Parameter> getParameters();
	void addParameter(Parameter param);
	string toString();
	int getNumParams();
    Parameter getParam(int index);
};

#endif // !PREDICATE_H
