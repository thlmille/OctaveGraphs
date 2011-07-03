#include <octave/oct.h>

using namespace std;

#include "../Graph.h"
#include "../badargs.h"

DEFUN_DLD(get_steps, args, ,
	    "Return the number of edges one must cross to get from the \
start vertex to the end vertex") {
  if (invalid_get_steps(args))
    return octave_value_list();
  Graph G(args(0).matrix_value());
  return octave_value(G.get_steps(args(1).int_value(), args(2).int_value()));
}
