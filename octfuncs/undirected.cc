#include <octave/oct.h>

using namespace std;

#include "../Graph.h"
#include "../badargs.h"

DEFUN_DLD(undirected, args, ,
       "Return undirected version of given graph by naively \
adding the reverse of every edge") {
  if (invalid_undirected(args))
    return octave_value_list();
  Matrix in_graph(args(0).matrix_value());
  Matrix undir_graph(2 * in_graph.rows(), in_graph.columns());
  for (int i = 0; i < in_graph.rows(); ++i) {
      undir_graph(2*i, 0) = in_graph(i, 0);
      undir_graph(2*i, 1) = in_graph(i, 1);
      undir_graph(2*i+1, 0) = in_graph(i, 1);
      undir_graph(2*i+1, 1) = in_graph(i, 0);
      if (in_graph.columns() == 3) {
	undir_graph(2*i, 2) = in_graph(i, 2);
	undir_graph(2*i+1, 2) = in_graph(i, 2);
      }
  }
  return octave_value(undir_graph);
}
