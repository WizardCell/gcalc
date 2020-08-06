#ifndef EDGE_H_
#define EDGE_H_

#include "Vertex.h"
#include <iostream>
#include <set>


//Todo: check if pair works

class Edge
{
private:
	Vertex src_vertex;
	Vertex dest_vertex;

public:
	Edge() = default;
	Edge(Vertex src_vertex, Vertex dest_vertex);
	//Todo: Constructor of name
	Edge(const Edge& other);
	~Edge() = default;

	const Vertex& getSourceVertex() const;
	const Vertex& getDestinationVertex() const;

    bool operator==(const Edge& other) const;
    bool operator<(const Edge& other) const;
    bool operator<=(const Edge& other) const;
    bool operator>(const Edge& other) const;
    bool operator>=(const Edge& other) const;




};

#endif //PROJECT_EDGE_H


