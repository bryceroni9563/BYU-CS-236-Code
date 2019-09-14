#include "Node.h"

Node::Node() {

}

Node::Node(int num) {
  name = num;
  visited = false;
  hasSelf = false;
}

int Node::getName() {
  return name;
}

void Node::addEdge(int newEdge) {
  if (newEdge == name) {
    hasSelf = true;
  }
  edges.insert(newEdge);
  return;
}

set<int> Node::getEdges() {
  return edges;
}

bool Node::isVisited() {
  return visited;
}

void Node::markVisited() {
  visited = true;
  return;
}

bool Node::containsSelf() {
  return hasSelf;
}
