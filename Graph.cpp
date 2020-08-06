#include "Graph.h"

template<class T>
std::set<T> set_union(std::set<T> left, std::set<T> right){
    std::set<T> result = left;
    result.insert(right.begin(), right.end());
    return result;
}

template <class T>
std::set<T> set_intersection(std::set<T> left, std::set<T> right){
    std::set<T> intersection;
    for(auto const &a : left){
        if (right.count(a) > 0 ){
            intersection.insert(a);
        }
    }
    return intersection;
}


Graph operator+(const Graph& graph1, const Graph& graph2){
    return Graph(set_union(graph1.vertices, graph2.vertices), set_union(graph1.edges,graph2.edges));
}

Graph operator^(const Graph& graph1, const Graph& graph2){
    return Graph( set_intersection(graph1.vertices, graph2.vertices), set_intersection(graph1.edges,graph2.edges));
}

Graph Graph::operator-(const Graph& other) const{
    std::set<Vertex> vertices_diff(vertices);
    std::set<Edge> edges_diff(edges);
    for(auto const &current_vertex : other.vertices){
        if(vertices.count(current_vertex) > 0){
            for(auto const &current_edge : edges_diff){
                if((current_vertex == current_edge.getSourceVertex()) || (current_vertex == current_edge.getDestinationVertex())){
                    edges_diff.erase(current_edge);
                }
            }
            vertices_diff.erase(current_vertex);
        }
    }
    return Graph(vertices, edges);
}

Graph operator*(const Graph& left, const Graph& right){
    std::set<Vertex> vertices_product;
    std::set<Edge>   edges_product;
    for(auto const& left_vertex : left.vertices){
        for(auto const& right_vertex : right.vertices){

            std::string vertex_src_product_name= "[" + left_vertex.getName() + ";" + right_vertex.getName() + "]";
            Vertex vertex_src_product(vertex_src_product_name);
            vertices_product.insert(vertex_src_product);

            for(auto const& left_edge : left.edges){
                if( left_vertex == left_edge.getSourceVertex() ){
                    for(auto const& right_edge : right.edges) {
                        if( right_vertex == right_edge.getSourceVertex() ){
                            ///Add it to the Edge set.
                            std::string vertex_dst_product_name= "[" + left_edge.getDestinationVertex().getName() + ";"
                                                                     + right_edge.getDestinationVertex().getName() + "]";
                            Vertex vertex_dst_product(vertex_dst_product_name);
                            //vertices_product.insert(vertex_src_product); //this is myotar
                            Edge edge_product(vertex_src_product, vertex_dst_product);
                            edges_product.insert(edge_product);
                        }
                    }
                }
            }
        }
    }
    return Graph(vertices_product, edges_product);
}

Graph Graph::operator!() const{
   std::set<Vertex> complement_vertices(this->vertices);
   std::set<Edge>   complement_edges;
   for(auto const& src : complement_vertices){
       for(auto const& dst : complement_vertices){   //Todo: check if we need to check if src==dst
           Edge edge(src, dst);
           complement_edges.insert(edge);
       }
   }
   ///Up until here complement_edges contains all possible edges
   for(auto const& edge : this->edges){
       complement_edges.erase(edge);
   }
   return Graph(complement_vertices, complement_edges);
}
