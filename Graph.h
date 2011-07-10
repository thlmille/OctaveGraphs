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

void DFS_visit (int, int*, map<int, int>&, map<int, int>&, map<int, int>&,
		map<int, int>&);

class Graph {
 private: 
  int order;
  map<int, vector<int>* > *adj_list;
 public:
  ~Graph();
  Graph (const Matrix &adj_rules);
  Graph ();
  Graph transpose();
  string print_graph ();
  pair<map<int, int>, map<int, int> > get_BFS_info (int source);
  pair<map<int, int>, pair<map<int, int>, map<int, int> > > 
     get_DFS_info (vector<int> node_order);
  void DFS_visit (int, int*, map<int, int>&, map<int, int>&, map<int, int>&,
		map<int, int>&);
  RowVector con_components();
  RowVector adj (int node);
  RowVector get_path (int start, int end);
  bool is_path (int start, int end);
  int get_steps (int start, int end);

};
