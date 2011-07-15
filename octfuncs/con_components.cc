#include <octave/oct.h>

using namespace std;

#include "../Graph.h"
#include "../badargs.h"

DEFUN_DLD(con_components, args, ,
	  "blah") {
  Graph G(args(0).matrix_value());
  return octave_value(G.con_components());
}
