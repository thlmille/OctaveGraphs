// Graph.c - Implementation of Graph class
#include <octave/oct.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>

using namespace std;

#include "Graph.h"

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
