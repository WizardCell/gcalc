
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




public:

	const std::set<Vertex> &getVertices() const;
	const std::set<Edge> &getEdges() const;

	Graph() = default;
	Graph(std::set<Vertex> vertices , std::set<Edge> edges):vertices(vertices), edges(edges){}
	Graph(const Graph& other) {
        vertices = other.vertices;
        edges    = other.edges;
	}
	~Graph() = default;
	friend Graph operator+(const Graph& graph1, const Graph& graph2);
	friend Graph operator^(const Graph& graph1, const Graph& graph2);
	Graph operator-(const Graph& other) const;
	friend Graph operator*(const Graph& graph1, const Graph& graph2);
    Graph operator!() const;
};

Graph operator+(const Graph& graph1, const Graph& graph2);
Graph operator^(const Graph& graph1, const Graph& graph2);
Graph operator*(const Graph& graph1, const Graph& graph2);
#endif //PROJECT_GRAPH_H

