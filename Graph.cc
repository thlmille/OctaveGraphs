#include <iostream>
#include <vector>
#include <map>

using namespace std;

#include <Graph.h>

typedef graph_itor map<int, vector<int>* >::iterator;

Graph::Graph (const Matrix &adj_rules) {
  this->adj_list = new map<int, vector<int>* >;

  int num_rules = adj_rules.rows();
  for (int i = 0; i < num_rules; ++i) {
    int head_node = adj_rules(i, 0);
    int tail_node = adj_rules(i, 1);

    if (adj_list[head_node] == NULL) {
      vector<int> *new_list = new vector<int>;
      new_list->push_back(tail_node);
      adj_list[head_node] = new_list;
    } 
    else {
      adj_list[head_node]->push_back(tail_node);
    }
  }  
}

void Graph::print_Graph () {

  graph_itor itor = this->adj_list.begin();
  for (; itor != adj_list.end(); ++itor) {
    cout << itor.first <<": ";
    vector<int>::iterator adj_itor = (*itor.second).begin();
    for (; itor != (*itor.second).end(); ++itor) {
      cout << *itor << " ";
    }
    cout << endl;
  }

}
