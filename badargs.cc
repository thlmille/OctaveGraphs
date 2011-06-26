// badargs.cc - Implementation file for badargs.h
#include <octave/oct.h>

using namespace std;

#include "badargs.h"

bool invalid_display_graph (const octave_value_list& args) {
  if (args.length() > 1) {
    error("diplay_graph: expecting only one argument");
    return true;
  }
  if (!args(0).is_real_matrix()) {
    error("display_graph: expecting argument to be a real matrix");
    return true;
  }
  if (args(0).columns() != 2 && args(0).columns() != 3) {
    error("display_graph: expecting each row of matrix to specify an adjacency rule");
    return true;
  }
  return false;
}

bool invalid_adj (const octave_value_list& args) {
  if (args.length() != 2) {
    error("adj: expecting a graph matrix and a real number as arguments");
    return true;
  }
  if (!args(0).is_real_matrix()) {
    error("adj: expecting first argument to be a real matrix");
    return true;
  }
  if (!args(1).is_real_scalar()) {
    error("adj: expecting second argument to be an integer");
    return true;
  }
  if (!contains_node(args)) {
    error("adj: given node does not exist");
    return true;
  }
  return false;
}

bool contains_node (const octave_value_list &args) {
  Matrix a(args(0).matrix_value());
  int b = args(1).int_value();
  for (int i = 0; i < a.rows(); ++i) {
    for (int j = 0; j < a.columns(); ++j) {
      if (a(i, j) == b) return true;
    }
  }
  return false;
}
