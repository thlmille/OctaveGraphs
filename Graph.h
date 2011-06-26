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

class Graph {
 private: 
  int order;
  map<int, vector<int>* > *adj_list;
 public:
  Graph (const Matrix &adj_rules);
  string print_graph ();
  RowVector adj (int node);
};
