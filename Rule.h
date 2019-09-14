#ifndef RULE_H
#define RULE_H

#include "Predicate.h"
#include <vector>
#include <string>

using std::string;
using std::vector;

class Rule {
private:
	Predicate headP;
	vector<Predicate> pList;
public:
	Rule();
	Rule(Predicate pred);
	Rule(Predicate pred, std::vector<Predicate> predList);
	void addPredicate(Predicate pred);
	vector<Predicate> getPredicateList();
	Predicate getHeadPredicate();
	string toString();
    int getNumPred();
};
#endif // !RULE_H
