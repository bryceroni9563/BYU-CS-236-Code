#include "Parameter.h"

Parameter::Parameter() {
	type = "";
	value = "";
}

Parameter::Parameter(string tokenType, string val) {
    type = tokenType;
    if (type == "STRING")
        isConstant = true;
    else
        isConstant = false;
    value = val;
}



string Parameter::getValue() {
	return value;
}

string Parameter::getType() {
	return type;
}

string Parameter::toString() {
    return value;
}

bool Parameter::constant() {
	return isConstant;
}