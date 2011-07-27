// weightedGraph implementation file

#include <octave/oct.h>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <map>

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


