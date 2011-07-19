#include <octave/oct.h>

using namespace std;

#include "../Graph.h"
#include "../badargs.h"

DEFUN_DLD(get_path, args, ,
	  "Return a row vector of nodes that leads from \
start vertex to end vertex, return -1 if no such path exists") {
  if (not_one_edge_matrix_two_nodes(args, "get_path"))
    return octave_value_list();
  Graph G(args(0).matrix_value());
  return octave_value(G.get_path(args(1).int_value(), args(2).int_value()));
}
