#include <octave/oct.h>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

#include "Graph.h"

typedef map<int, vector<int>* >::iterator graph_itor;

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

void Graph::print_graph () {

  graph_itor node_itor = this->adj_list->begin();
  for (; node_itor != this->adj_list->end(); ++node_itor) {
    cout << node_itor->first <<": ";
    vector<int>::iterator adj_itor = node_itor->second->begin();
    for (; adj_itor != node_itor->second->end(); ++adj_itor) {
      cout << *adj_itor << " ";
    }
    cout << endl;
  }
}
