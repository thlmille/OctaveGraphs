// badargs.cc - Implementation file for badargs.h
#include <octave/oct.h>
#include <string>

using namespace std;

#include "badargs.h"

bool not_one_edge_matrix (const octave_value_list &args, const string& which) {
  if (args.length() != 1) {
    error((which + ": expecting only one argument").c_str());
    return true;
  }
  if (!args(0).is_real_matrix()) {
    error((which + ": expecting arguments to be a real matrix").c_str());
    return true;
  }
  if (!all_integers(args(0).matrix_value())) {
    error((which + ": nodes must be specified by integers greater than 0").c_str());
    return true;
  }
  if (args(0).columns() != 2 && args(0).columns() != 3) {
    error((which + ": expecting each row of matrix to specify an \
adjacency rule").c_str());
    return true;
  }
  return false;
}

bool not_one_edge_matrix_one_node (const octave_value_list &args,
				   const string& which) {
  if (args.length() != 2) {
    error((which + ":  expecting a graph matrix and a real number \
as arguments").c_str());
    return true;
  }
  if (!args(0).is_real_matrix()) {
    error((which + ": expecting first argument to be a real matrix").c_str());
    return true;
  }
  if (!all_integers(args(0).matrix_value())) {
    error((which + ": nodes must be specified by integers greater than 0").c_str());
    return true;
  }
  if (!args(1).is_real_scalar()) {
    error((which + ": expecting second argument to be an integer").c_str());
    return true;
  }
  if (!contains_node(args(0).matrix_value(), args(1).int_value())) {
    error((which + ": given node does not exist").c_str());
    return true;
  }
  return false;
}

bool not_one_edge_matrix_two_nodes (const octave_value_list &args,
				    const string& which) {
  if (args.length() != 3) {
    error((which + ": expecting a graph matrix and two real numbers \
as arguments").c_str());
    return true;
  }
  if (!args(0).is_real_matrix()) {
    error((which + ": expecting first argument to be a real matrix").c_str());
    return true;
  }
  if (!all_integers(args(0).matrix_value())) {
    error((which + ": nodes must be specified by integers greater \
than 0").c_str());
    return true;
  }
  if (!args(1).is_real_scalar()) {
    error((which + ": expecting second argument to be an integer").c_str());
    return true;
  }
  if (!args(2).is_real_scalar()) {
    error((which + ": expecting third argument to be an integer").c_str());
    return true;
  }
  if (!contains_node(args(0).matrix_value(), args(1).int_value())) {
    error((which + ": node does not exist").c_str());
    return true;
  }
  if (!contains_node(args(0).matrix_value(), args(2).int_value())) {
    error((which + ": node does not exist").c_str());
    return true;
  }
  return false;
}

bool not_one_edge_matrix_one_row_vector (const octave_value_list &args,
					 const string &which) {
  if (args.length() != 2) {
    error((which + ": expecting a graph matrix and row vector as \
arguments").c_str());
    return true;
  }
  if (!args(0).is_real_matrix()) {
    error((which + ": expecting first argument to be a real matrix").c_str());
    return true;
  }
  if (!all_integers(args(0).matrix_value())) {
    error((which + ": nodes must be specified by integers greater \
than 0").c_str());
    return true;
  }
  if (!args(1).is_real_matrix()) {
    error((which + ": expecting second argument to be a real \
RowVector").c_str());
    return true;
  }
  if (args(0).matrix_value().rows() != 1) {
    error((which + ": expecting second argument to be a real \
RowVector").c_str());
    return true;
  }
  if (!all_integers(args(1).matrix_value())) {
    error((which + ": nodes must be specified by integers greater \
than 0").c_str());
    return true;
  }
  return false;
}

bool contains_node (const Matrix& a, int node) {
  for (int i = 0; i < a.rows(); ++i) {
    for (int j = 0; j < a.columns(); ++j) {
      if (a(i, j) == node) return true;
    }
  }
  return false;
}

bool all_integers (const Matrix& a) {
  for (int i = 0; i < a.rows(); ++i) {
    for (int j = 0; j < a.columns(); ++j) {
      int hold = a(i,j);
      if (hold != a(i,j)) return false;
      if (a(i,j) < 1) return false;
    }
  }
  return true;
}
