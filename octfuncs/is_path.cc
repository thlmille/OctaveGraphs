#include <octave/oct.h>

using namespace std;

#include "../Graph.h"
#include "../badargs.h"

DEFUN_DLD(is_path, args, ,
	  "Return 1 if a path can be found from start vertex to \
end vertex, 0 otherwise") {
  if (not_one_edge_matrix_two_nodes(args, "is_path"))
    return octave_value_list();
  Graph G(args(0).matrix_value());
  return octave_value(G.is_path(args(1).int_value(), args(2).int_value()));
}
