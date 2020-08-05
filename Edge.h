#ifndef PROJECT_EDGE_H
#define PROJECT_EDGE_H

#include "Vertex.h"


class Edge
{
private:
	Vertex src_Vertex;
	Vertex dest_Vertex;
	std::pair<Vertex, Vertex> pair; //TODO: reference not working

public:
	Edge() = default;
	Edge(Vertex src_Vertex, Vertex dest_Vertex);
	Edge(const Edge& other);
	~Edge();

	const Vertex& getSourceVertex() const;
	const Vertex& getDestinationVertex() const;





};

#endif //PROJECT_EDGE_H
