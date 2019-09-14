#include "Graph.h"

Graph::Graph() {

}

void Graph::addNode(Node toAdd) {
  graph.insert(pair<int,Node>(toAdd.getName(),toAdd));
  return;
}

Node Graph::getNode(int name) {
  return graph[name];
}

void Graph::updateNode(int i, Node newGuy) {
  graph[i] = newGuy;
  return;
}

vector<int> Graph::dfsForest(int i) {
  postOrderNums.clear();
  //for (int i = 0; i < (int)graph.size(); i++){
    if (!graph[i].isVisited()){
      //cout << i << endl;
      dfs(graph[i]);
    }
//  }
  return postOrderNums;
}

void Graph::dfs(Node n) {
  n.markVisited();
  graph[n.getName()] = n;
  for (int i : n.getEdges()) {
    if (graph[i].isVisited() == false) {
      //cout << "IDK, man" << endl;
      dfs(graph[i]);
    }
  }

  postOrderNums.push_back(n.getName());
  return;
}
