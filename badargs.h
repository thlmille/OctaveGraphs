// badargs.h
// Set of functions that determine if the arguments passed
// to the various graph functions are legitimate. Names are
// self explanatory.

#include <octave/oct.h>

using namespace std;

#if !defined(_BADARGS_H_)
#define _BADARGS_H_

bool contains_node (const Matrix &a, int node);

bool all_integers (const Matrix &a);

bool not_one_edge_matrix (const octave_value_list &args, const string &which);

bool not_one_edge_matrix_one_node (const octave_value_list &args,
				   const string &which);

bool not_one_edge_matrix_two_nodes (const octave_value_list &args,
				    const string &which);

bool not_one_edge_matrix_one_row_vector (const octave_value_list &args,
					 const string &which);

bool not_one_weighted_edge_matrix (const octave_value_list &args,
				   const string &which);

bool not_dijkstra_valid (const octave_value_list &args,
			 const string &which);

bool positive_weights (const Matrix &a);


#endif
