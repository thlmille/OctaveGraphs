get_path : Graph.cc badargs.cc
	./makeoct.pl octfuncs/get_path.cc

display_graph : Graph.cc badargs.cc
	./makeoct.pl octfuncs/display_graph.cc

adj : Graph.cc badargs.cc
	./makeoct.pl octfuncs/adj.cc

clean :
	rm -f *.o *.oct
	rm -f octfuncs/*.o