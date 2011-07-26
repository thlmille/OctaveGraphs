octfiles = adj.oct closure.oct con_components.oct \
display_graph.oct get_path.oct get_steps.oct is_path.oct \
subgraph.oct top_sort.oct trans_graph.oct undirected.oct

all : ${octfiles}

%.oct : octfuncs/%.cc Graph.o badargs.o
	mkoctfile $^

%.o: %.cc
	mkoctfile -c $<

clean :
	rm -f *.o *.oct
	rm -f octfuncs/*.o

