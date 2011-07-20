#include <octave/oct.h>

using namespace std;

#include "../Graph.h"
#include "../badargs.h"

DEFUN_DLD(closure, args, ,
	  "Return row vector of nodes reachable from given node.") {

  if (not_one_edge_matrix_one_node(args, "closure"))
    return octave_value_list();

  Graph G(args(0).matrix_value());
  return octave_value(G.closure(args(1).int_value()));
}
