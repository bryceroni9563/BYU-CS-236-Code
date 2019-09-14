#ifndef DLP_H
#define DLP_H
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include "Token.h"
#include "Parser.h"

using std::string;
using std::stringstream;

//  enum tokenTypes { LEFT_PAREN, RIGHT_PAREN, ...};
//  map<tokenType, string> m = {{LEFT_PAREN, '('}, ...};

	const string leftParen = "LEFT_PAREN";
	const string rightParen = "RIGHT_PAREN";
	const string comma = "COMMA";
	const string period = "PERIOD";
	const string questionMark = "Q_MARK";
	const string colon = "COLON";
	const string colonDash = "COLON_DASH";
	const string multiply = "MULTIPLY";
	const string add = "ADD";
	const string schemes = "SCHEMES";
	const string facts = "FACTS";
	const string rules = "RULES";
	const string queries = "QUERIES";
	const string id = "ID";
	const string stringType = "STRING";
	const string comment = "COMMENT";
	const string undefined = "UNDEFINED";
	const string eoFile = "EOF";

class DLP {
	char nextToken;
	char currChar;
	string tokenVal;
	string tokenType;
	int lineNumber;
	bool contString;
	bool contComm;
	std::vector<Token> tokenVct; 
	Parser goober;
	

public:
    DLP();
	void lab1(string filename);
	void lab2();
    vector<Predicate> getSchemesVct();
    vector<Predicate> getFactsVct();
    vector<Rule> getRulesVct();
    vector<Predicate> getQueriesVct();
};

#endif
