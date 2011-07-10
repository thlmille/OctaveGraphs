#include <octave/oct.h>

using namespace std;

#include "../Graph.h"
#include "../badargs.h"

DEFUN_DLD(top_sort, args, ,
	  "Return RowVector that is topological sort of nodes") {
  if (invalid_top_sort(args))
    return octave_value_list();
  Graph G(args(0).matrix_value());
  return octave_value(G.top_sort());
}
