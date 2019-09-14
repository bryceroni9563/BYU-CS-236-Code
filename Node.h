#ifndef NODE_H
#define NODE_H
#include <string>
#include <map>
#include <set>

using std::set;
using std::string;
using std::map;

class Node {
  set<int> edges;
  bool visited;
  bool hasSelf;
  int name;
public:
  Node();
  Node(int num);
  int getName();
  void addEdge(int newEdge);
  set<int> getEdges();
  bool isVisited();
  void markVisited();
  bool containsSelf();
};

#endif
