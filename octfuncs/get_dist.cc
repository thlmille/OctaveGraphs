#include <octave/oct.h>

using namespace std;

#include "../badargs.h"
#include "../weightedGraph.h"

DEFUN_DLD(get_dist, args, ,
	  "Return total weight of shortest path between two given \
vertices.") {

  if (not_dijkstra_valid(args, "get_dist"))
    return octave_value_list();

  Graph H(args(0).matrix_value());
  weightedGraph G(H);
  G.assign_weights(args(0).matrix_value());


  return octave_value(G.get_dist(args(1).int_value(), 
				 args(2).int_value()));
}
