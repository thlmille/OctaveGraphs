// Graph.c - Implementation of Graph class
#include <octave/oct.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <utility>
#include <map>

using namespace std;

#include "Graph.h"

#define nil -1
typedef map<int, vector<int>* >::iterator graph_itor;

// Graph constructor. Takes in a matrix of adjacency rules and
// builds the adjacency list for the given graph. A matrix of m rows
// is interpreted as a graph with m edges, specified by the first two
// entries in each row. The matrix adj_rules passed to this constructor
// must have dimensions m * 2 for an unweighted graph or dimensions
// m * 3 for a weighted graph.
Graph::Graph (const Matrix &adj_rules) {
  map<int, vector<int>* > *thisMap = new map<int, vector<int>* >;
  this->adj_list = thisMap;

  int num_rules = adj_rules.rows();
  for (int i = 0; i < num_rules; ++i) {
    int head_node = adj_rules(i, 0);
    int tail_node = adj_rules(i, 1);

    if ((*adj_list)[head_node] == NULL) {
      vector<int> *new_list = new vector<int>;
      new_list->push_back(tail_node);
      (*adj_list)[head_node] = new_list;
    } 
    else {
      (*adj_list)[head_node]->push_back(tail_node);
    }
    if ((*adj_list)[tail_node] == NULL) {
      vector<int> *new_list = new vector<int>;
      (*adj_list)[tail_node] = new_list;
    }
  }
  this->order = this->adj_list->size();
}

Graph::~Graph() {
  graph_itor itor = this->adj_list->begin();
  for (; itor != this->adj_list->end(); ++itor) {
    delete itor->second;
  }
  delete this->adj_list;
}

string Graph::print_graph () {
  std::stringstream out;
  out << endl << "{" << endl;
  graph_itor node_itor = this->adj_list->begin();
  for (; node_itor != this->adj_list->end(); ++node_itor) {
    out << "   " << node_itor->first <<": ";
    vector<int>::iterator adj_itor = node_itor->second->begin();
    for (; adj_itor != node_itor->second->end(); ++adj_itor) {
      out << *adj_itor << " ";
    }
    out << endl;
  }
  out << "}" << endl;
  return out.str();
}

RowVector Graph::adj (int node) {
  int num_adj_nodes = (*adj_list)[node]->size();
  RowVector adj_vector(num_adj_nodes);
  vector<int>::iterator itor = (*adj_list)[node]->begin();
  for (int i = 0; itor != (*adj_list)[node]->end(); ++itor, ++i) {
    adj_vector(i) = *itor;
  }
  return adj_vector;
}

pair<map<int, int>, map<int, int> > Graph::get_BFS_info (int source) {
  map<int, int> color; // 0 = white, 1 = gray, 2 = black
  map<int, int> distance;
  map<int, int> parent;
  graph_itor itor = this->adj_list->begin();
  for (; itor != this->adj_list->end(); ++itor) {
    parent[itor->first] = nil;
    distance[itor->first] = nil;
  }
  distance[source] = 0;
  parent[source] = nil;
  queue<int> node_hold;
  node_hold.push(source);
  while (!node_hold.empty()) {
    int curr_node = node_hold.front();
    node_hold.pop();
    vector<int>::iterator adj_itor = (*adj_list)[curr_node]->begin();
    for (; adj_itor != (*adj_list)[curr_node]->end(); ++adj_itor) {
      if (color[*adj_itor] == 0) {
	color[*adj_itor] = 1;
	distance[*adj_itor] = distance[curr_node] + 1;
	parent[*adj_itor] = curr_node;
	node_hold.push(*adj_itor);
      }
    }
    color[curr_node] = 2;
  }
  return make_pair (parent, distance);
}

bool Graph::is_path(int start, int end) {
  if (this->get_BFS_info(start).first[end] != nil) return true;
  return false;
}

RowVector Graph::get_path(int start, int end) {
  map <int, int> parent = this->get_BFS_info(start).first;
  if (parent[end] == nil) {
    RowVector no_path(1);
    no_path(0) = nil;
    return no_path;
  }
  stack<int> path_stack;
  int curr_node = end;
  while (curr_node != start) {
    path_stack.push(curr_node);
    curr_node = parent[curr_node];
  }
  path_stack.push(start);
  RowVector path(path_stack.size());
  int i = 0;
  while (!path_stack.empty()) {
    path(i) = path_stack.top();
    path_stack.pop();
    ++i;
  }
  return path;
}

int Graph::get_steps(int start, int end) {
  map<int, int> distance = this->get_BFS_info(start).second;
  return distance[end];
}
