#include <octave/oct.h>

using namespace std;

#include "../Graph.h"
#include "../badargs.h"

DEFUN_DLD(trans_graph, args, ,
	  "Return the transpose of the given graph") {
  if (not_one_edge_matrix(args, "trans_graph"))
    return octave_value_list();
  Matrix in_graph(args(0).matrix_value());
  int temp;
  for (int i = 0; i < in_graph.rows(); ++i) {
    temp = in_graph(i, 0);
    in_graph(i, 0) = in_graph(i, 1);
    in_graph(i, 1) = temp;
  }
  return octave_value(in_graph);
}
