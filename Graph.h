#ifndef GRAPHWRAP_H
#define GRAPHWRAP_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "ClassGraph.h"


Graph* create();
void destroy(Graph* graph);
Graph* addVertex(Graph* graph, const char* v);
Graph* addEdge(Graph* graph, const char* v1, const char* v2);
void disp(Graph* graph);

Graph* graphUnion(Graph* graph_in1, Graph* graph_in2, Graph* graph_out);
Graph* graphIntersection(Graph* graph_in1, Graph* graph_in2, Graph* graph_out);
Graph* graphDifference(Graph* graph_in1, Graph* graph_in2, Graph* graph_out);
Graph* graphProduct(Graph* graph_in1, Graph* graph_in2, Graph* graph_out);
Graph* graphComplement(Graph* graph_in, Graph* graph_out);

#endif // GRAPHWRAP_H