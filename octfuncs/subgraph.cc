#include <octave/oct.h>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

#include "../Graph.h"
#include "../badargs.h"

// Use binary search to determine if given vector contains given int
bool contains (vector<int> space, int item) {
  return binary_search (space.begin(), space.end(), item);
}

// Return a c++ vector from a given octave RowVector
vector<int> get_vector (RowVector from) {
  vector<int> ret;
  for (int i = 0; i < from.length(); ++i) {
    ret.push_back(from(i));
  }
  return ret;
}

DEFUN_DLD(subgraph, args, ,
	  "Return an edge matrix that represents the given graph's \
subgraph containing only the nodes in the given row vector") {

  Matrix in_graph = args(0).matrix_value();
  Matrix temp = args(1).matrix_value();
  RowVector nodes = temp.row(0);

  // Put nodes into a sorted vector
  vector<int> sorted_nodes = get_vector(nodes);

  sort(sorted_nodes.begin(), sorted_nodes.end());

  // Go through matrix, record which rows are valid and count them.
  // Valid rows are rules made from two nodes that are both in the
  //   given row vector.
  vector<bool> valid_rows(in_graph.rows());
  int valcount = 0;
  for (int i = 0; i < in_graph.rows(); ++i) {
    if (contains(sorted_nodes, in_graph(i, 0)) && 
	contains(sorted_nodes, in_graph(i, 1))) {
      valid_rows[i] = true;
      valcount++;
    }
  }

  // Copy valid edges from old matrix into subgraph matrix
  Matrix sub(valcount, in_graph.columns());
  int sub_index = 0;
  for (int i = 0; i < in_graph.rows(); ++i) {
    if (valid_rows[i]) {
      for (int j = 0; j < in_graph.columns(); ++j) {
	sub(sub_index, j) = in_graph(i, j);
      }
      ++sub_index;
    }
  }
  return octave_value(sub);
}
