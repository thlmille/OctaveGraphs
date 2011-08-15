#include <octave/oct.h>

using namespace std;

#include "../badargs.h"
#include "../weightedGraph.h"

DEFUN_DLD(mst, args, ,
	  "Return a matrix of edges that form a minimum spanning \
tree for the given graph") {

  if (not_one_weighted_edge_matrix(args, "mst"))
      return octave_value_list();


  Graph H(args(0).matrix_value());
  weightedGraph G(H);
  G.assign_weights(args(0).matrix_value());

  return octave_value(G.mst());
}

