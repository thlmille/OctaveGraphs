#include <octave/oct.h>

using namespace std;

#include "Graph.h"

DEFUN_DLD(display_graph, args, , 
	  "Show the adjacency list representation of a graph.") {

  Matrix b(args(0).matrix_value());
  Graph G(b);
  G.print_graph();
  return octave_value(0);

}
