#include <octave/oct.h>

using namespace std;

#include "../badargs.h"
#include "../weightedGraph.h"

DEFUN_DLD(dijkstra_path, args, ,
	  "Return row vector of nodes that give shortest path \
between two specified nodes in Graph") {

  if (not_dijkstra_valid(args, "dijkstra_path"))
    return octave_value_list();

  Graph H(args(0).matrix_value());
  weightedGraph G(H);
  G.assign_weights(args(0).matrix_value());



  return octave_value(G.dijkstra_path(args(1).int_value(),
				      args(2).int_value()));

}
