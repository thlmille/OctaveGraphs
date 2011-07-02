get_path : Graph.cc badargs.cc
	./makeoct.pl get_path.cc

display_graph : Graph.cc badargs.cc
	./makeoct.pl display_graph.cc

adj : Graph.cc badargs.cc
	./makeoct.pl adj.cc

clean :
	rm -f *.o *.oct
