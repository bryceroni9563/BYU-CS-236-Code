#include "Predicate.h"

Predicate::Predicate() {
	id = "";
	paramList = vector<Parameter>();
}

Predicate::Predicate(string ident) {
	id = ident;
	paramList = vector<Parameter>();
}

Predicate::Predicate(string ident, vector<Parameter> newList) {
	id = ident;
	paramList = newList;
}

string Predicate::getID() {
	return id;
}

vector <Parameter> Predicate::getParameters() {
	return paramList;
}

void Predicate::addParameter(Parameter param) {
	paramList.push_back(param);
}

string Predicate::toString() {
	stringstream ss;
	ss << id << "(";
	for (int i = 0; i < (int)paramList.size(); i++) {
		if (i == 0)
			ss << paramList[i].toString();
		else
			ss << "," << paramList[i].toString();
	}
	ss << ")";
	return ss.str();
}

int Predicate::getNumParams() {
	return (int)paramList.size();
}

Parameter Predicate::getParam(int index) {
    return paramList.at(index);
}
