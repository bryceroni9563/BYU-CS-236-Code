#include "Token.h"

Token::Token() {
	lineNumber = 1;
	tokenType = "";
	tokenVal = "";
}

string Token::getToken() {
	std::stringstream ss;
	ss << "(" << tokenType << ",\"" << tokenVal << "\"," << lineNumber << ")";
	return ss.str();
}

void Token::setType(string newType) {
	tokenType = newType;
	return;
}

void Token::setVal(string newVal) {
	tokenVal = newVal;
	return;
}

void Token::setVal(char newVal) {
	tokenVal = newVal;
	return;
}

void Token::setLine(int lineNum) {
	lineNumber = lineNum;
	return;
}

string Token::getType(){
    return tokenType;
}

string Token::getVal(){
    return tokenVal;
}

/*char Token::getValue(){
    return tokenVal;
}*/

int Token::getLine(){
    return lineNumber;
}
