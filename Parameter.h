#ifndef PARAMETER_H
#define PARAMETER_H
#include <string>

using std::string;

class Parameter {
private:
    string type;
	string value;
    bool isConstant;
public:
	Parameter();
    Parameter(string tokenType, string val);

	string getValue();
	string getType();
	string toString();
	bool constant();
};

#endif // !PARAMETER_H
