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

Graph::Graph() {
  this->adj_list = new map<int, vector<int>* >;
  this->order = 0;
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

Graph Graph::transpose () {
  Graph trans;
  graph_itor original_itor = this->adj_list->begin();
  for (; original_itor != this->adj_list->end(); ++original_itor) {
    vector<int>::iterator orig_node_itor = original_itor->second->begin();
    for (; orig_node_itor != original_itor->second->end(); ++orig_node_itor) {
      if ((*trans.adj_list)[*orig_node_itor] == NULL) {
	vector<int> *new_nodes = new vector<int>;
	new_nodes->push_back(original_itor->first);
	(*trans.adj_list)[*orig_node_itor] = new_nodes;
      } else {
	(*trans.adj_list)[*orig_node_itor]->push_back(original_itor->first);
      }
    }
  }
  return trans;
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

pair<map<int, int>, pair<map<int, int>, map<int, int> > > Graph::get_DFS_info
(vector<int> node_order) {
  map <int, int> color; // 0 = white, 1 = gray, 2 = black
  map<int, int> parent;
  map<int, int> start;
  map <int, int> finish;
  graph_itor itor = this->adj_list->begin();
  for (; itor != this->adj_list->end(); ++itor) {
    parent[itor->first] = nil;
  }
  int time = 0;
  vector<int>::iterator node_itor = node_order.begin();
  for (; node_itor != node_order.end(); ++node_itor) {
    if (color[*node_itor] == 0) {
      this->DFS_visit(*node_itor, &time, color, parent, start, finish);
    }
  }
  return make_pair (parent, make_pair (start, finish));
}

void Graph::DFS_visit(int curr_node, int *time,  map<int, int> &color, 
		      map<int, int>&parent, map<int, int> &start, 
		      map<int, int> &finish) {
  (*time)++;
  start[curr_node] = *time;
  color[curr_node] = 1;
  vector<int>::iterator adj_itor = (*adj_list)[curr_node]->begin();
  for (; adj_itor != (*adj_list)[curr_node]->end(); ++adj_itor) {
    if (color[*adj_itor] == 0) {
      parent[*adj_itor] = curr_node;
      DFS_visit(*adj_itor, time, color, parent, start, finish);
    }
  }
  color[curr_node] = 2;
  (*time)++;
  finish[curr_node] = *time;
}

bool sort_help (int i, int j) {return i < j;}

// Sort finish times in descending order
vector<int> order_finish_times (const map<int, int> &finish) {
  map<int, int> con_finish;
  vector<int> finish_times;
  map<int, int>::const_iterator fin_itor = finish.begin();
  for (; fin_itor != finish.end(); ++fin_itor) {
    con_finish[fin_itor->second] = fin_itor->first;
    finish_times.push_back(fin_itor->second);
  }
  sort (finish_times.begin(), finish_times.end(), sort_help);
  vector<int> sorted;
  int i = 0;
  int j = finish_times.size() - 1;
  for (; i < finish_times.size(); ++i, --j) {
    sorted.push_back(con_finish[finish_times[j]]);
  }
  return sorted;
}

octave_value_list Graph::con_components() {
  vector<int> node_order;
  graph_itor itor = this->adj_list->begin();
  for (; itor != this->adj_list->end(); ++itor) {
    node_order.push_back(itor->first);
  }
  map<int, int> finish = this->get_DFS_info(node_order).second.second;
  vector<int> sorted = order_finish_times(finish);
  Graph trans = this->transpose();
  map<int, int> parents = trans.get_DFS_info(sorted).first;
  int num_comps;
  map<int, int>::iterator parent_itor = parents.begin();
  for (; parent_itor != parents.end(); ++parent_itor) {
    if (*parent_itor == nil) ++num_comps;
  }
  octave_value_list the_comps;
  int curr_node = *parents.begin();
  for (int i = 1; i <= num_comps; ++i) {

  }
}

RowVector Graph::top_sort() {
  vector<int> node_order;
  graph_itor itor = this->adj_list->begin();
  for (; itor != this->adj_list->end(); ++itor) {
    node_order.push_back(itor->first);
  }
  map<int, int> finish = this->get_DFS_info(node_order).second.second;
  vector<int> sorted = order_finish_times (finish);
  RowVector sorted_nodes(this->order);
  for (int i = 0; i < this->order; ++i) {
    sorted_nodes(i) = sorted[i];
  }
  return sorted_nodes;
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
