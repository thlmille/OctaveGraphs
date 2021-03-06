#include <octave/oct.h>

using namespace std;

#include "../Graph.h"
#include "../badargs.h"

DEFUN_DLD(adj, args, ,
	  "Return a row vector of vertices adjacent to a given vertex.") {
  if (not_one_edge_matrix_one_node(args, "adj"))
    return octave_value_list();
  Graph G(args(0).matrix_value());
  return octave_value(G.adj(args(1).int_value()));
}

