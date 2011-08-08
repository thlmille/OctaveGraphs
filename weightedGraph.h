// weightedGraph header file
#include <iostream>
#include <map>
#include <utility>
#include <string>
#include <vector>

using namespace std;

#include "Graph.h"

class weightedGraph: public Graph {
 private:
  map < pair<int, int>, double> edge_weights;
 public:
  weightedGraph (Graph &G);
  void assign_weights (const Matrix &adj_rules);
  ~weightedGraph ();
  pair< map<int, int>, map<int, double> > 
  get_dijkstra_info (int source);
  void relax (int u, int v, map<int, int> &parent,
	      map <int, pair<int, double>* > &node_handles);
  double weight(int a, int b);
  void initialize_shortest_paths (map<int, int> &parent,
				  map<int, double> &distance,
				  int source);
  double get_dist (int start, int end);
  RowVector dijkstra_path(int start, int end);
};
