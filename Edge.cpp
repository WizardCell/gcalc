
#include "Edge.h"
#include "Vertex.h"

#include <iostream>
#include <set>



Edge::Edge(Vertex src_Vertex, Vertex dest_Vertex)
	: src_Vertex(src_Vertex.getName()), dest_Vertex(dest_Vertex.getName()), pair(src_Vertex, dest_Vertex)
{

}

Edge::Edge(const Edge& other)
{
	this->src_Vertex = other.src_Vertex;
	this->dest_Vertex = other.dest_Vertex;
	pair = std::make_pair(src_Vertex, dest_Vertex);
}

Edge::~Edge()
{

}

const Vertex& Edge::getSourceVertex() const
{
	return this->src_Vertex;
}

const Vertex& Edge::getDestinationVertex() const
{
	return this->dest_Vertex;
}

int main()
{
	Vertex v1("mhmd");
	Vertex v2("mhmd");
	std::set<Vertex&> vertices;
	vertices.emplace(v1);
	vertices.emplace(v2);
	std::cout << vertices.size();
	return 0;
}
