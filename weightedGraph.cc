// weightedGraph implementation file

#include <octave/oct.h>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <utility>
#include <map>
#include <algorithm>

using namespace std;

#include "weightedGraph.h"

weightedGraph::weightedGraph (Graph &G) {
  (*this->adj_list) = G.get_adj_list();
  this->order = G.get_order();
}

weightedGraph::~weightedGraph() {
  graph_itor itor = this->adj_list->begin();
  for (; itor != this->adj_list->end(); ++itor) {
    delete itor->second;
  }
  delete this->adj_list;
}

void weightedGraph::assign_weights (const Matrix &adj_rules) {
  map< pair<int, int>, double> weights;
  for (int i = 0; i < adj_rules.rows(); ++i) {
    weights[ make_pair(adj_rules(i, 0), adj_rules(i, 1)) ] = 
      adj_rules(i, 2); 
  }
  this->edge_weights = weights;
}

double weightedGraph::weight (int a, int b) {
  return this->edge_weights[make_pair(a, b)];
}

void weightedGraph::relax (int u, int v, map<int, int> &parent,
			   map<int, pair<int, double> *> &node_handles) {
  if (node_handles[v]->second == nil) {
    node_handles[v]->second = node_handles[u]->second
      + this->weight(u, v);
    parent[v] = u;
    return;
  }
  if (node_handles[v]->second > node_handles[u]->second +
      this->weight(u, v)) {
    node_handles[v]->second = node_handles[u]->second + 
      this->weight(u, v);
    parent[v] = u;
  }
}

void weightedGraph::initialize_shortest_paths (map<int, int> &parent,
					       map<int, double> &distance,
					       int source) {
  graph_itor it = this->adj_list->begin();
  for (; it != this->adj_list->end(); ++it) {
    distance[it->first] = nil;
    parent[it->first] = nil;
  }
  distance[source] = 0;
}

// Support class for std::priority_queue that gives smallest
//   numbers the highest priority and nil the lowest
class smallfirst {
public:
  bool operator() (pair<int, double> *a, pair<int, double> *b) {
    if (a->second == nil) return false;
    if (a->second < b->second) return false;
    return true;
  }
};

pair< map<int, int>, map<int, double> > 
weightedGraph::get_dijkstra_info (int source) {
  // initialize
  map<int, int> parent;
  map<int, double> distance;
  this->initialize_shortest_paths(parent, distance, source);

  // use pointers so we can change values in heap
  vector<pair<int, double>* > node_heap;
  // use map to keep track of distance values for each node
  map<int, pair<int, double>* > node_handles;

  // load node_heap and node_handles
  map<int, double>::iterator it = distance.begin();
  for (; it != distance.end(); ++it) {
    pair<int, double> *temp = new pair<int, double>;
    temp->first = it->first;
    temp->second = it->second;
    node_heap.push_back(temp);
    node_handles[it->first] = (temp);
  }

  make_heap(node_heap.begin(), node_heap.end(), smallfirst());

  // main loop of dijkstra
  while (!node_heap.empty()) {
    int curr_node = node_heap.back()->first;
    node_heap.pop_back();
    vector<int>::iterator node_it = 
      (*adj_list)[curr_node]->begin();
    for (; node_it != (*adj_list)[curr_node]->end(); ++node_it) {
      this->relax(curr_node, *node_it, parent, node_handles);
      make_heap(node_heap.begin(), node_heap.end(), smallfirst());
    }
  }

  // copy info back to distance map
  map<int, pair<int, double>* >::iterator fin_it = node_handles.begin();
  for (; fin_it != node_handles.end(); ++fin_it) {
    distance[fin_it->first] = fin_it->second->second;
  }
  return make_pair (parent, distance);
}

