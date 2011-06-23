// badargs.cc - Implementation file for badargs.h
#include "badargs.h"

static bool invalid_display_graph (const octave_value_list &args) {
  if (args.length() > 1) {
    error("diplay_graph: expecting only one argument");
    return true;
  }
  if (!args(0).is_real_matrix) {
    error("display_graph: expecting argument to be a real matrix");
    return true;
  }
  if (args(0).columns != 2 || args(0).columns != 3) {
    error("display_graph: expecting each row of matrix to specify an 
                adjacency rule");
  }
}
