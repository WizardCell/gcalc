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
	
tar: ClassGraph.cpp Edge.cpp Exceptions.cpp gcalc.cpp graph.cpp Vertex.cpp ClassGraph.h Edge.h Exceptions.h gcalc.h graph.h Vertex.h graph.i
	zip gcalc.zip $^ Makefile

clean:
	rm -f $(OBJS) $(EXEC)
	