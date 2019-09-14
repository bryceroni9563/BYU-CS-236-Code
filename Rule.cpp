#include "Rule.h"

Rule::Rule() {
	headP = Predicate();
	pList = vector<Predicate>();
}

Rule::Rule(Predicate pred) {
	headP = pred;
	pList = vector<Predicate>();
}

Rule::Rule(Predicate pred, vector<Predicate> predList) {
	headP = pred;
	pList = predList;
}

void Rule::addPredicate(Predicate pred) {
	pList.push_back(pred);
}

vector<Predicate> Rule::getPredicateList() {
	return pList;
}

Predicate Rule::getHeadPredicate() {
	return headP;
}

string Rule::toString() {
	stringstream ss;
	ss << headP.toString() << " :- ";
	for (int i = 0; i < (int)pList.size(); i++) {
		if (i == 0) {
			ss << pList[i].toString();
		}
		else {
			ss << "," + pList[i].toString();
		}
		
	}
    ss << ".";
	return ss.str();
}

int Rule::getNumPred() {
    return pList.size();
}
