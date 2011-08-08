// Graph.h - header file for Graph Class
/* Graphs are represented using an adjacency list which */
/* is structured as a map of integers and pointers to vectors of */
/* integers. Each integer maps to a vector that contains the nodes */
/* it is adjacent to. */

#include <octave/oct.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>

#define nil -1
typedef map<int, vector<int>* >::iterator graph_itor;
RowVector parent_path (int start, int end, map<int, int> &parent);

class Graph {
 protected:
  int order;
  map<int, vector<int>* > *adj_list;
 public:
  ~Graph();
  Graph (const Matrix &adj_rules);
  Graph ();
  Graph transpose();
  string display_graph ();
  pair<map<int, int>, map<int, int> > get_BFS_info (int source);
  pair<map<int, int>, vector<int> > 
          get_DFS_info (vector<int> node_order);
  void DFS_visit (int,  map<int, int>&, map<int, int>&,  vector<int>&);
  octave_value_list con_components();
  RowVector adj (int node);
  RowVector get_path (int start, int end);
  bool is_path (int start, int end);
  int get_steps (int start, int end);
  RowVector top_sort();
  RowVector closure (int source);
  int get_order();
  map <int, vector<int> * > get_adj_list ();

};
