// badargs.h
// Set of functions that determine if the arguments passed
// to the various graph functions are legitimate. Each graph
// function will map to exactly one function in this file that checks
// if its arguments are valid. This functions may be built of several
// smaller ones in this file.

using namespace std;

#if !defined(_BADARGS_H_)
#define _BADARGS_H_

#include <octave/oct.h>

bool invalid_trans_graph (const octave_value_list &args);

bool invalid_display_graph (const octave_value_list &args);

bool invalid_adj (const octave_value_list &args);

bool invalid_get_path (const octave_value_list &args);

bool invalid_is_path (const octave_value_list &args);

bool invalid_get_steps (const octave_value_list &args);

bool all_integers (const Matrix &a);

bool contains_node (const Matrix &a, int node);

#endif
