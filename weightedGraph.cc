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

void weightedGraph::assign_weights (const Matrix &adj_rules) {
  map< pair<int, int>, double> weights;
  for (int i = 0; i < adj_rules.rows(); ++i) {
    weights[ make_pair(adj_rules(i, 0), adj_rules(i, 1)) ] = 
      adj_rules(i, 2); 
  }
  this->edge_weights = weights;
}

weightedGraph::~weightedGraph () {}

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

// Support class for make_heap that gives smallest
//   numbers the highest priority and nil the lowest
class smallfirst {
public:
  bool operator() (pair<int, double> *a, pair<int, double> *b) {
    if (a->second == nil) return true;

    if (b->second == nil) return false;
    if (a->second > b->second) return true;
    return false;
  }
};


// Implementation of Dijkstra's Algorithm, relies on STL heap
//   algorithms
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
    int curr_node = node_heap.front()->first;
    pop_heap (node_heap.begin(), node_heap.end(), smallfirst());
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
    delete fin_it->second;
  }

  return make_pair (parent, distance);
}

double weightedGraph::get_dist (int start, int end) {
  return this->get_dijkstra_info(start).second[end];
}

RowVector weightedGraph::dijkstra_path (int start, int end) {
  map<int, int> parent = this->get_dijkstra_info(start).first;
  return parent_path(start, end, parent);
}


// Implementation of Prim's algorithm for calculating a
//   minimum spanning tree
Matrix weightedGraph::mst () {
  // Initialize values and pointers, use pointers like
  //   in dijkstra's algorithm
  vector<pair<int, double>* > node_heap;
  map<int, pair<int, double>* > node_handles;
  graph_itor it = this->adj_list->begin();
  for (; it != this->adj_list->end(); ++it) {
    pair <int, double>* temp = new pair <int, double>;
    temp->first = it->first;
    temp->second = nil;
    node_heap.push_back(temp);
    node_handles[it->first] = temp;
  }
  node_handles[this->adj_list->begin()->first]->second = 0;

  make_heap(node_heap.begin(), node_heap.end(), smallfirst());

  // Parent map to keep track of nodes
  map <int, int> parent;

  // Keep track of nodes that have been removed from heap
  map <int, bool> out_heap;

  // Main loop of Prim's mst algorithm
  while (!node_heap.empty()) {
    int curr_node = node_heap.front()->first;
    pop_heap(node_heap.begin(), node_heap.end(), smallfirst());
    node_heap.pop_back();
    out_heap[curr_node] = true;
    vector<int>::iterator node_it =
      (*adj_list)[curr_node]->begin();
    for (; node_it != (*adj_list)[curr_node]->end(); ++node_it) {
      if (!out_heap[*node_it] &&
	  this->weight(curr_node, *node_it) <
	  node_handles[*node_it]->second ||
	  node_handles[*node_it]->second == nil) {
	parent[*node_it] = curr_node;
	node_handles[*node_it]->second = this->weight(curr_node, *node_it);
	make_heap(node_heap.begin(), node_heap.end(), smallfirst());
      }
    }
  }

  // Extract edges from parent map and return as matrix
  vector<pair<int, int> > mst_edges;
  map<int, int>::iterator pit = parent.begin();
  for (; pit != parent.end(); ++pit) {
    cout << pit->first << " " << pit->second << endl;
    if (pit->second != nil) {
      mst_edges.push_back(make_pair(pit->first, pit->second));
    }
  }

  // Construct graph matrix
  Matrix ret(mst_edges.size(), 2);
  for (int i = 0; i < mst_edges.size(); ++i) {
    ret(i, 0) = mst_edges[i].first;
    ret(i, 1) = mst_edges[i].second;
  }
  return ret;
}
