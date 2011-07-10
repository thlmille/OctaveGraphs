top_sort : Graph.cc badargs.cc
	./makeoct.pl octfuncs/top_sort.cc

con_components : Graph.cc badargs.cc
	./makeoct.pl octfuncs/con_components.cc

is_path : Graph.cc badargs.cc
	./makeoct.pl octfuncs/is_path.cc

get_steps : Graph.cc badargs.cc
	./makeoct.pl octfuncs/get_steps.cc

get_path : Graph.cc badargs.cc
	./makeoct.pl octfuncs/get_path.cc

display_graph : Graph.cc badargs.cc
	./makeoct.pl octfuncs/display_graph.cc

adj : Graph.cc badargs.cc
	./makeoct.pl octfuncs/adj.cc

clean :
	rm -f *.o *.oct
	rm -f octfuncs/*.o

