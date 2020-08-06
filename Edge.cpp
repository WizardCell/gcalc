
#include "Edge.h"




Edge::Edge(Vertex src_vertex, Vertex dest_vertex)
        : src_vertex(src_vertex.getName()), dest_vertex(dest_vertex.getName()) {

}

Edge::Edge(const Edge &other) {
    this->src_vertex = other.src_vertex;
    this->dest_vertex = other.dest_vertex;
}


const Vertex &Edge::getSourceVertex() const {
    return this->src_vertex;
}

const Vertex &Edge::getDestinationVertex() const {
    return this->dest_vertex;
}

bool Edge::operator==(const Edge& other) const{
    return ((this->src_vertex == other.src_vertex) && (this->dest_vertex == other.dest_vertex));
}

bool Edge::operator<(const Edge& other) const
{
    if(this->src_vertex < other.src_vertex){
        return true;
    }
    else if(this->src_vertex == other.src_vertex){
        return (this->dest_vertex == other.dest_vertex);
    }
}

bool Edge::operator<=(const Edge& other) const
{
    if(this->src_vertex <= other.src_vertex){
        return true;
    }
    else if(this->src_vertex == other.src_vertex){
        return (this->dest_vertex <= other.dest_vertex);
    }
}

bool Edge::operator>(const Edge& other) const
{
    if(this->src_vertex > other.src_vertex){
        return true;
    }
    else if(this->src_vertex == other.src_vertex){
        return (this->dest_vertex > other.dest_vertex);
    }
}

bool Edge::operator>=(const Edge& other) const
{
    if(this->src_vertex >= other.src_vertex){
        return true;
    }
    else if(this->src_vertex == other.src_vertex){
        return (this->dest_vertex >= other.dest_vertex);
    }
}