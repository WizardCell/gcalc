
#ifndef PROJECT_GRAPH_H
#define PROJECT_GRAPH_H

#include "Vertex.h"
#include "Edge.h"

#include <map>
#include <set>


class Graph
{
private:
	std::set<Vertex>    vertices;
	std::set<Edge>      edges;
	//std::map< Vertex& , std::set<Edge&> > graph_map;

public:
	Graph() = default;
	Graph(std::set<Vertex> vertices , std::set<Edge> edges):vertices(vertices), edges(edges){}
	Graph(const Graph& other) { // todo check
        vertices = other.vertices;
        edges    = other.edges;
	}~Graph() = default;
	//todo: operator=
	friend Graph operator+(const Graph& graph1, const Graph& graph2);
	friend Graph operator^(const Graph& graph1, const Graph& graph2);
	Graph operator-(const Graph& other) const;
	friend Graph operator*(const Graph& graph1, const Graph& graph2);
    Graph operator!() const;

    //Todo: operator== ///Do it comparing the names
};

Graph operator+(const Graph& graph1, const Graph& graph2);
Graph operator^(const Graph& graph1, const Graph& graph2);
Graph operator*(const Graph& graph1, const Graph& graph2);
#endif //PROJECT_GRAPH_H

