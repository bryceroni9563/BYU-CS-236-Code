#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <sstream>


using std::string;

class Token
{
private:
	int lineNumber;
	string tokenType;
	string tokenVal;
    friend class Parser;
public:
	Token();
	string getToken();
	void setType(string newType);
	void setVal(string newVal);
	void setVal(char newVal);
	void setLine(int lineNum);
    string getType();
    string getVal();
    //char getValue();
    int getLine();
};
#endif
