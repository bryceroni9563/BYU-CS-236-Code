#ifndef GRAPH_H
#define GRAPH_H
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include "Node.h"

using std::string;
using std::map;
using std::pair;
using std::vector;
using std::cout;
using std::endl;

class Graph /*: public map<int,Node>*/ {
  map<int,Node> graph;
  vector<int> postOrderNums;
public:
  Graph();
  void addNode(Node toAdd);
  Node getNode(int name);
  void updateNode(int i, Node newGuy);
  vector<int> dfsForest(int i);
  void dfs(Node n);
};

#endif
