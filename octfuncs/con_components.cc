#include <octave/oct.h>

using namespace std;

#include "../Graph.h"
#include "../badargs.h"

DEFUN_DLD(con_components, args, ,
	  "Returns a list of row vectors that are the strongly \
connected components of the given graph.") {
  Graph G(args(0).matrix_value());

  // This extra step stops the seg_faults on exit, I haven't
  //   the slightest idea why.
  octave_value_list ret = G.con_components();

  return octave_value(ret);
}
