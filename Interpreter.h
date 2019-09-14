#ifndef INTERPRETER_H
#define INTERPRETER_H
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <stack>
#include "Database.h"
#include "DLP.h"
#include "Graph.h"

using std::string;
using std::vector;
using std::cout;
using std::stack;

class Interpreter {
	DLP datalog;
	vector<Predicate> schemesVct;
	vector<Rule> rulesVct;
	vector<Predicate> factsVct;
	vector<Predicate> queriesVct;
	vector<int> columnsToKeep;
	vector<Parameter> paramsSeen;
	vector<set<int>> sccVct;
	stack<int> postOrderStack;
	bool paramFound;
	int prevFoundIndex;
	Database db;
	int prevNumTuples;
	int numRulesPasses;
	Graph forward;
	Graph backward;
public:
	Interpreter();
	Interpreter(DLP dataLP);
	Relation evalQuery(Predicate q);
	Relation evalRule(Rule r);
	void makeGraph();
	void evalAllRules();
	void evalAllQueries();
	void manageRule(set<int> scc);
	void manageTrivialRule(set<int> scc);
};

#endif
