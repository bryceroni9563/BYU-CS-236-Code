#ifndef RELATION_H
#define RELATION_H
#include <string>
#include <set>
#include <iostream>
#include <vector>
#include <utility>
#include "Scheme.h"
#include "Tuple.h"

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::set;
using std::pair;

class Relation {
  string name;
  Scheme scheme;
  set<Tuple> tuples;
  int sizeSchemes;
	vector<pair<int,int>> indicies;
	vector<int> keepThese;
public:
  Relation();
  Relation(string n, Scheme s);
  void setName(string n);
  void setScheme(Scheme s);
  void addTuple(Tuple t);
	void removeTuple(Tuple t);
	void printTuples();
  void printTuples(string s);
	void relUnion(set<Tuple> toAdd);
  string getName();
  Scheme getScheme();
  set<Tuple> getTuples();
	Relation selectType1(string s, int i);
	Relation selectType2(int i, int j);
	Relation selectType2(int i, int j, Relation newBuddy);
	Relation project(vector<int> toKeep);
	void rename(vector<string> newHeader);
	int getNumTuples();
  Relation join(Relation newBuddy);
  bool isJoinable();
  Scheme combineSchemes(Scheme joinedScheme, Scheme s);
  Relation combineTuples(vector<pair<int,int>> indicies, Relation newBuddy);
};

#endif
