CC=/usr/local/bin/gcc
CXX=/usr/local/bin/g++
OBJS = ClassGraph.o Edge.o Exceptions.o gcalc.o graph.o Vertex.o
EXEC = gcalc
COMP_FLAG = --std=c++11 -fPIC -Wall -pedantic-errors -Werror -DNDEBUG
DEBUG_FLAG = -g
$(EXEC): $(OBJS)
	$(CXX)  $(DEBUG_FLAG) $(OBJS) -o $@
ClassGraph.o: ClassGraph.cpp ClassGraph.h Vertex.h Edge.h
	$(CXX) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp
Edge.o: Edge.cpp Edge.h Vertex.h Exceptions.h
	$(CXX) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp
Exceptions.o: Exceptions.cpp Exceptions.h
	$(CXX) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp
gcalc.o: gcalc.cpp gcalc.h ClassGraph.h Vertex.h Edge.h Exceptions.h
	$(CXX) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp
graph.o: graph.cpp graph.h ClassGraph.h Vertex.h Edge.h gcalc.h Exceptions.h
	$(CXX) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp
Vertex.o: Vertex.cpp Vertex.h Exceptions.h
	$(CXX) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp
libgraph.a: $(OBJS)
	ar -rs $@ $^
	
tar: *.cpp *.h graph.i test_in.txt test_out.txt design.pdf
	zip gcalc.zip $^ Makefile

clean:
	rm -f $(OBJS) $(EXEC) libgraph.a gcalc.zip
