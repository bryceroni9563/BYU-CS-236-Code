#include "Relation.h"

Relation::Relation() {
    name = "";
    scheme = Scheme();
    tuples = std::set<Tuple>();
    sizeSchemes = 0;
}

Relation::Relation(string n, Scheme s){
    name = n;
    scheme = s;
    tuples = set<Tuple>();
    sizeSchemes = scheme.size();
}

void Relation::setName(string n) {
    name = n;
    return;
}

void Relation::setScheme(Scheme s) {
    scheme = s;
    sizeSchemes = scheme.size();
    return;
}

void Relation::addTuple(Tuple t) {
    tuples.insert(t);
    return;
}

void Relation::removeTuple(Tuple t) {
	tuples.erase(t);
	return;
}

void Relation::printTuples() {
	for (Tuple t : tuples) {
		for (int i = 0; i < (int)scheme.size(); i++) {
			if (i == 0)
				cout << "  ";
			else
				cout << ", ";
			cout << scheme.at(i) << "=" << t.at(i);
		}
		cout << endl;
	}
	return;
}

void Relation::printTuples(string s) {
	cout << s << "? ";
	if (getNumTuples() == 0) {
		cout << "No" << endl;
	}
	else {
		cout << "Yes(" << getNumTuples() << ")" << endl;
        set<Tuple>::iterator it = tuples.begin();
        Tuple firstTup = *it;
        if (scheme.size() == 0) {
            //do nothing
        }
        else {
		    for (Tuple t : tuples) {
                for (int i = 0; i < (int)scheme.size(); i++) {
                    if (i == 0) {
                        cout << "  ";
                    }
                    else {
                        cout << ", ";
                    }

                    cout << scheme.at(i) << "=" << t.at(i);
                }
                cout << endl;
		    }
        }
	}

	return;
}

string Relation::getName() {
    return name;
}

Scheme Relation::getScheme() {
    return scheme;
}

std::set<Tuple> Relation::getTuples() {
    return tuples;
}


Relation Relation::selectType1(string s, int i) {
  Relation tempRel = Relation(name,scheme);
	for (Tuple tup : tuples) {
		if (tup.at(i) == s) {
		    tempRel.addTuple(tup);
		}
	}
    return tempRel;
}

Relation Relation::selectType2(int i, int j) {
  Relation tempRel = Relation(name,scheme);
	for (Tuple tup : tuples) {
		if (tup.at(i) == tup.at(j)) {
			tempRel.addTuple(tup);
		}
	}
  return tempRel;
}

Relation Relation::selectType2(int i, int j, Relation newBuddy) {
	Relation tempRel = Relation(name, scheme);
	for (Tuple tup : tuples) {
		for (Tuple t : newBuddy.getTuples()) {
			if (tup.at(i) == t.at(j)) {
				for (int k = 0; k < (int)t.size(); k++) {
					tup.push_back(t.at(k));
				}
				tempRel.addTuple(tup);
			}
		}
	}
	return tempRel;
}

Relation Relation::project(vector<int> toKeep) {
  Relation tempRel = Relation();
  tempRel.setName(name);
  Scheme s;
  for (int i = 0; i < (int)toKeep.size(); i++){
    s.push_back(scheme.at(toKeep.at(i)));
  }
  tempRel.setScheme(s);
  for (Tuple tup : tuples) {
    Tuple t;
    for (int i = 0; i < (int)toKeep.size(); i++) {
      t.push_back(tup.at(toKeep.at(i)));
    }

    tempRel.addTuple(t);

  }
  return tempRel;
}

void Relation::rename(vector<string> newHeader) {
  Scheme newScheme;
  for (int i = 0; i < (int)newHeader.size(); i++) {
    newScheme.push_back(newHeader.at(i));
  }
  setScheme(newScheme);
  return;
}

void Relation::relUnion(set<Tuple> toAdd) {
	for (Tuple t : toAdd) {
		if (tuples.insert(t).second){
      for (int i = 0; i < (int)scheme.size(); i++) {
  			if (i == 0)
  				cout << "  ";
  			else
  				cout << ", ";
  			cout << scheme.at(i) << "=" << t.at(i);
  		}
  		cout << endl;
    }
	}
	return;
}

int Relation::getNumTuples() {
	return (int)tuples.size();
}

Relation Relation::join(Relation newBuddy) {
	Relation tempRel;
  tempRel = Relation(name, scheme);
  for (Tuple t : tuples){
    tempRel.addTuple(t);
  }
  tempRel.setScheme(combineSchemes(scheme, newBuddy.getScheme()));
	tempRel = tempRel.combineTuples(indicies, newBuddy);
	tempRel = tempRel.project(keepThese);
  return tempRel;
}

bool Relation::isJoinable() {
    bool canJoin = false;
    return canJoin;
}

Scheme Relation::combineSchemes(Scheme joinedScheme, Scheme s) {
	indicies.clear();
	keepThese.clear();
  int sizeOfJS = joinedScheme.size();
	int j = 0;
	for (int i = 0; i < (int)joinedScheme.size(); i++) {
		keepThese.push_back(i);
	}
  bool addThis = true;
  for (string check : s) {
    for (int i = 0; i < (int)joinedScheme.size(); i++) {
      if (joinedScheme.at(i) == check) {
        pair<int,int> newThingy(i,j);
        indicies.push_back(newThingy);
        addThis = false;
      }

    }
    if (addThis){
      keepThese.push_back(j + sizeOfJS);
    }
    addThis = true;
    joinedScheme.push_back(check);
    j++;
  }
  return joinedScheme;
}

Relation Relation::combineTuples(vector<pair<int,int>> indicies, Relation newBuddy) {
	Relation tempRel = Relation(name, scheme);
  bool allGood = true;
  for (Tuple t1 : tuples){
    for (Tuple t2 : newBuddy.getTuples()){
      Tuple t = t1;
      allGood = true;
      for (int i = 0; i < (int)indicies.size(); i++){
        if (t1.at(indicies.at(i).first) != t2.at(indicies.at(i).second)) {
          allGood = false;
        }
      }
      if (allGood){
        for (string s : t2){
          t.push_back(s);
        }
        tempRel.addTuple(t);
      }
    }
  }
	return tempRel;
}
