#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <set>
#include "Token.h"
#include "Predicate.h"
#include "Rule.h"

using std::cout;
using std::string;
using std::endl;
using std::vector;
using std::set;
using std::stringstream;

class Parser {
private:
    std::vector<Token> tokenVct;
    int numSchemes;
    int numFacts;
    int numRules;
    int numQueries;
	int index;
    string currExp;
    Token currToken;
	Predicate pred;
	Rule nextRule;
    bool rulePred;
	vector<Predicate> schemesVct;
	vector<Rule> rulesVct;
	vector<Predicate> factsVct;
	vector<Predicate> queriesVct;
	set<string> domain;
    set<string>::iterator itr;

    string leftParen = "LEFT_PAREN";
	string rightParen = "RIGHT_PAREN";
	string comma = "COMMA";
	string period = "PERIOD";
	string questionMark = "Q_MARK";
	string colon = "COLON";
	string colonDash = "COLON_DASH";
	string multiply = "MULTIPLY";
	string add = "ADD";
	string schemes = "SCHEMES";
	string facts = "FACTS";
	string rules = "RULES";
	string queries = "QUERIES";
	string id = "ID";
	string stringType = "STRING";
	string comment = "COMMENT";
	string undefined = "UNDEFINED";
	string eoFile = "EOF";
public:
    Parser();
    void setTokenVct(std::vector<Token> newVct);
    void parse();
    void match(string type);
    void parseSchemes();
	void parseSchemeList();
    void parseFactList();
	void parseFacts();
	void parseStrings();
    void parseRuleList();
	void parseRules();
    void parseQueries();
	void parseQueryList();
	void parseIDList();
	void parseHeadPredicate();
	void parsePredicate(bool fromRule);
	void parsePredicateList(bool fromRule);
	void parseParameter();
    void parseExpParameter();
	void parseParameterList();
	void parseExpression();
	void parseOperator();
    void printStuff();
	int getNumSchemes();
	int getNumFacts();
	int getNumRules();
	int getNumQueries();
    int getDomainSize();
    vector<Predicate> getSchemesVct();
    vector<Predicate> getFactsVct();
    vector<Rule> getRulesVct();
    vector<Predicate> getQueriesVct();
	string printSchemes();
	string printFacts();
	string printRules();
	string printQueries();
	string printDomain();
    //bool isGoodGrammar();
};
#endif
