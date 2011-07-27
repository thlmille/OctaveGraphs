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

};
