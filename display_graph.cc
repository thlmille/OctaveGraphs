#include <octave/oct.h>

using namespace std;

#include "Graph.h"
#include "badargs.h"

DEFUN_DLD(display_graph, args, , 
	  "Show the adjacency list representation of a graph.") {
  if (invalid_display_graph(args)) 
    return octave_value_list();
  Matrix b(args(0).matrix_value());
  Graph G(b);
  return octave_value(G.print_graph());

}
