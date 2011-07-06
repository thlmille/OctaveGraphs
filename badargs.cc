// badargs.cc - Implementation file for badargs.h
#include <octave/oct.h>

using namespace std;

#include "badargs.h"

bool invalid_trans_graph (const octave_value_list& args) {
  if (args.length() != 1) {
    error("trans_graph: expecting only one argument");
    return true;
  }
  if (!args(0).is_real_matrix()) {
    error("trans_graph: expecting argument to be a real matrix");
    return true;
  }
  if (!all_integers(args(0).matrix_value())) {
    error("trans_graph: nodes must be specified by integers \
greater than 0");
    return true;
  }
  return false;
}

bool invalid_undirected (const octave_value_list& args) {
  if (args.length() != 1) {
    error("undirected: expecting only one argument");
    return true;
  }
  if (!args(0).is_real_matrix()) {
    error("undirected: expecting argument to be a real matrix");
    return true;
  }
  if (!all_integers(args(0).matrix_value())) {
    error("undirected: nodes must be specified by integers \
greater than 0");
    return true;
  }
  return false;
}

bool invalid_display_graph (const octave_value_list& args) {
  if (args.length() != 1) {
    error("diplay_graph: expecting only one argument");
    return true;
  }
  if (!args(0).is_real_matrix()) {
    error("display_graph: expecting argument to be a real matrix");
    return true;
  }
  if (!all_integers(args(0).matrix_value())) {
    error("display_graph: nodes must be specified by integers \
greater than 0");
    return true;
  }
  if (args(0).columns() != 2 && args(0).columns() != 3) {
    error("display_graph: expecting each row of matrix to specify \
an adjacency rule");
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
  if (!all_integers(args(0).matrix_value())) {
    error("adj: nodes must be specified by integers greater than 0");
    return true;
  }
  if (!args(1).is_real_scalar()) {
    error("adj: expecting second argument to be an integer");
    return true;
  }
  if (!contains_node(args(0).matrix_value(), args(1).int_value())) {
    error("adj: given node does not exist");
    return true;
  }
  return false;
}

bool invalid_get_path (const octave_value_list &args) {
  if (args.length() != 3) {
    error("get_path: expecting a graph matrix and two real numbers as arguments");
    return true;
  }
  if (!args(0).is_real_matrix()) {
    error("get_path: expecting first argument to be a real matrix");
    return true;
  }
  if (!all_integers(args(0).matrix_value())) {
    error("get_path: nodes must be specifie be integer greater than 0");
    return true;
  }
  if (!args(1).is_real_scalar()) {
    error("get_path: expecting second argument to be an integer");
    return true;
  }
  if (!args(2).is_real_scalar()) {
    error("get_path: expecting third argument to be an integer");
    return true;
  }
  if (!contains_node(args(0).matrix_value(), args(1).int_value())) {
    error("get_path: node does not exist");
    return true;
  }
  if (!contains_node(args(0).matrix_value(), args(2).int_value())) {
    error("get_path: node does not exist");
    return true;
  }
  return false;
}

bool invalid_get_steps (const octave_value_list &args) {
  if (args.length() != 3) {
    error("get_steps: expecting a graph matrix and two real numbers as arguments");
    return true;
  }
  if (!args(0).is_real_matrix()) {
    error("get_steps: expecting first argument to be a real matrix");
    return true;
  }
  if (!all_integers(args(0).matrix_value())) {
    error("get_steps: nodes must be specifie be integer greater than 0");
    return true;
  }
  if (!args(1).is_real_scalar()) {
    error("get_steps: expecting second argument to be an integer");
    return true;
  }
  if (!args(2).is_real_scalar()) {
    error("get_steps: expecting third argument to be an integer");
    return true;
  }
  if (!contains_node(args(0).matrix_value(), args(1).int_value())) {
    error("get_steps: node does not exist");
    return true;
  }
  if (!contains_node(args(0).matrix_value(), args(2).int_value())) {
    error("get_steps: node does not exist");
    return true;
  }
  return false;
}

bool invalid_is_path (const octave_value_list &args) {
  if (args.length() != 3) {
    error("is_path: expecting a graph matrix and two real numbers as arguments");
    return true;
  }
  if (!args(0).is_real_matrix()) {
    error("is_path: expecting first argument to be a real matrix");
    return true;
  }
  if (!all_integers(args(0).matrix_value())) {
    error("is_path: nodes must be specifie be integer greater than 0");
    return true;
  }
  if (!args(1).is_real_scalar()) {
    error("is_path: expecting second argument to be an integer");
    return true;
  }
  if (!args(2).is_real_scalar()) {
    error("is_path: expecting third argument to be an integer");
    return true;
  }
  if (!contains_node(args(0).matrix_value(), args(1).int_value())) {
    error("is_path: node does not exist");
    return true;
  }
  if (!contains_node(args(0).matrix_value(), args(2).int_value())) {
    error("is_path: node does not exist");
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
