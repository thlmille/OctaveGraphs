// badargs.h
// Set of functions that determine if the arguments passed
// to the various graph functions are legitimate. Each graph
// function will map to exactly one function in this file that checks
// if its arguments are valid. This functions may be built of several
// smaller ones in this file.

static bool invalid_display_graph (const octave_value_list &args);
