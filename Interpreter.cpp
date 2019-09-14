#include "Interpreter.h"

Interpreter::Interpreter() {
	datalog = DLP();
}

Interpreter::Interpreter(DLP dataLP) {
	datalog = dataLP;
	schemesVct = datalog.getSchemesVct();
	factsVct = datalog.getFactsVct();
	rulesVct = datalog.getRulesVct();
	queriesVct = datalog.getQueriesVct();
	forward = Graph();
	backward = Graph();
	for(Predicate scheme : schemesVct) {
		string name = scheme.getID();
		Scheme newScheme;
		Relation newRelation;
		for (Parameter p : scheme.getParameters()) {
		    newScheme.push_back(p.toString());
		}
		newRelation = Relation(name, newScheme);
		db[name] = newRelation;
  }
  for(Predicate fact : factsVct) {
	  Tuple newTup;
	  Relation toAddTo;
	  toAddTo = db.find(fact.getID())->second;
	  for (Parameter p : fact.getParameters()) {
	    newTup.push_back(p.toString());
	  }
	  (db.find(fact.getID())->second).addTuple(newTup);
  }
	numRulesPasses = 0;
}

Relation Interpreter::evalQuery(Predicate q) {
	Relation comparison = db[q.getID()];
	Parameter p;
  paramsSeen.clear();
  columnsToKeep.clear();
	for (int i = 0; i < q.getNumParams(); i++) {
		p = q.getParam(i);
		if (p.constant()) {
			comparison = comparison.selectType1(p.getValue(), i);
		}
		else {
			paramFound = false;
        for (int j = 0; j < (int)paramsSeen.size(); j++) {
          if(paramsSeen.at(j).getValue() == p.getValue()) {
            paramFound = true;
            prevFoundIndex = j;
          }
        }
        if (paramFound) {
          comparison = comparison.selectType2(i, prevFoundIndex);
        }
        else {
          paramsSeen.push_back(p);
          columnsToKeep.push_back(i);
        }
		}
	}
  vector<string> newHeader;
  for (int i = 0; i < (int)paramsSeen.size(); i++) {
    newHeader.push_back(paramsSeen.at(i).toString());
  }
  comparison = comparison.project(columnsToKeep);

  comparison.rename(newHeader);


	return comparison;
}

Relation Interpreter::evalRule(Rule r) {
  vector<Relation> evaluatedPreds;
  for (Predicate p : r.getPredicateList()) {
    evaluatedPreds.push_back(evalQuery(p));
  }
	Relation evaluated = Relation();
  if (evaluatedPreds.size() != 0) {
    evaluated = evaluatedPreds.at(0);
    if (evaluatedPreds.size() > 1) {
      for (int i = 1; i < (int)evaluatedPreds.size(); i++) {
        evaluated = evaluated.join(evaluatedPreds.at(i));
      }
    }
  }
	columnsToKeep.clear();

	for (Parameter param : r.getHeadPredicate().getParameters()) {
		int j = 0;
		for (string str : evaluated.getScheme()) {
			if (param.getValue() == str) {
				columnsToKeep.push_back(j);
			}
			j++;
		}
	}

	evaluated = evaluated.project(columnsToKeep);
  return evaluated;
}

void Interpreter::evalAllRules() {
	while (!postOrderStack.empty()){
		while (forward.getNode(postOrderStack.top()).isVisited()) {
			postOrderStack.pop();
			if (postOrderStack.empty()) {
				break;
			}
		}
		if (!postOrderStack.empty()) {
			set<int> newScc;
			vector<int> sccInVct = forward.dfsForest(postOrderStack.top());
			for (int i = 0; i < (int)sccInVct.size(); i++) {
				newScc.insert(sccInVct.at(i));
			}
			sccVct.push_back(newScc);
			postOrderStack.pop();
		}
	}
  //for (Rule r : rulesVct) {

	for (set<int> scc : sccVct) {
		cout << "SCC: R";
		set<int>::iterator it = scc.begin();
		for (int i : scc){
			if (it != scc.begin()){
				cout << ",R";
			}
			cout << i;
			it++;
		}
		cout << endl;
		numRulesPasses = 0;
		prevNumTuples = db.getNumTuples();
		it = scc.begin();
		if (scc.size() == 1 && !forward.getNode(*it).containsSelf()){
			manageTrivialRule(scc);
		}
		else {
			manageRule(scc);
		}
		//TODO: put manageRule functions back in.
		cout << numRulesPasses << " passes: R";
		//it = scc.begin();
		for (int i : scc){
			if (it != scc.begin()){
				cout << ",R";
			}
			cout << i;
			it++;
		}
		cout << endl;

  }
	cout << endl;
  return;
}

void Interpreter::evalAllQueries() {
  cout << "Query Evaluation" << endl;
  for(Predicate q : queriesVct) {
		Relation evaluated = evalQuery(q);
		evaluated.printTuples(q.toString());
	  evaluated = Relation();
  }
  return;
}

void Interpreter::makeGraph() {

	for (int i = 0; i < (int)rulesVct.size(); i++) {
		Node nextGuy = Node(i);
		forward.addNode(nextGuy);
		backward.addNode(nextGuy);
	}
	for (int i = 0; i < (int)rulesVct.size(); i++) {
		Rule r1 = rulesVct.at(i);
		for (Predicate p : r1.getPredicateList()){
			string id = p.getID();
			for (int j = 0; j < (int)rulesVct.size(); j++) {
				Rule r2 = rulesVct.at(j);
				if (r2.getHeadPredicate().getID() == id) {
					Node forNode = forward.getNode(i);
					Node backNode = backward.getNode(j);
					forNode.addEdge(j);
					backNode.addEdge(i);
					forward.updateNode(i, forNode);
					backward.updateNode(j, backNode);
				}
			}
		}
	}
	for (int i = 0; i < (int)rulesVct.size(); i++) {
		Node currNode = forward.getNode(i);
		cout << "R" << i << ":";
		int first = 0;
		for (int j : currNode.getEdges()) {
			if (first == 0){
				cout << "R" << j;
			}
			else {
				cout << ",R" << j;
			}
			first++;
		}
		cout << endl;

	}

	vector<int> postOrderNums;

	for (int i = 0; i < (int)rulesVct.size(); i++) {
		vector<int> temp = backward.dfsForest(i);
		for (int j = 0; j < (int)temp.size(); j++){
			postOrderNums.push_back(temp.at(j));
		}
	}

	for (int i : postOrderNums) {
		postOrderStack.push(i);
	}

	return;
}

void Interpreter::manageRule(set<int> scc) {
	int it = 0;
	for (int i : scc){
		Rule r = rulesVct.at(i);
		Relation evaluated = evalRule(r);
		cout << r.toString() << endl;
		string compName =  r.getHeadPredicate().getID();
		Relation comparison = db[compName];
		comparison.relUnion(evaluated.getTuples());
		db[compName] = comparison;
		if (it == (int)scc.size() - 1) {
			numRulesPasses++;
			if ((db.getNumTuples() - prevNumTuples) != 0) {
				prevNumTuples = db.getNumTuples();
				manageRule(scc);
			}
		}
		it++;
	}
	return;
}

void Interpreter::manageTrivialRule(set<int> scc) {
	for (int i : scc){
		Rule r = rulesVct.at(i);
		Relation evaluated = evalRule(r);
		cout << r.toString() << endl;
		string compName =  r.getHeadPredicate().getID();
		Relation comparison = db[compName];
		comparison.relUnion(evaluated.getTuples());
		db[compName] = comparison;
		numRulesPasses++;
	}
	return;
}
