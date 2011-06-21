#include <octave/oct.h>
#include <iostream>
#include <vector>
#include <map>

class Graph {
 private: 
  int order;
  map<int, vector<int> > adj_list;
 public:
  Graph(const Matrix &adj_rules);
};
