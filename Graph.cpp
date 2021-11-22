#include "graph.h"
#include "gcalc.h"

Graph *create() {
    try {
        return new Graph();
    } catch (const std::bad_alloc &e) {
        std::cout << "Error: bad allocation" << std::endl;
    } catch (const std::exception &exp) {
        std::cout << "Error: Unknown error." << std::endl;
    }
    return nullptr;
}

void destroy(Graph* graph) {
    delete graph;
}

Graph *addVertex(Graph *graph, const char* v_name) {
    try {
        if (graph == nullptr) {
            std::cout << "Error: Graph is null" << std::endl;
            return nullptr;
        }
        std::set<Vertex> vertex_set;
        std::set<Edge> edges_set;

        std::string v_string(v_name);

        Vertex v(v_string);

        if(graph->getVertices().count(v) > 0){
            throw RedefinedVertex();
        }

        vertex_set.insert(v);

        Graph to_unify(vertex_set, edges_set);

        *graph = *graph + to_unify;
        return graph;
    }catch (const IllegalName &e) {
        std::cout << e.what() << std::endl;
    } catch (const UndefinedVariable &e) {
        std::cout << e.what() << std::endl;
    } catch (const UnrecognizedCommand &e) {
        std::cout << e.what() << std::endl;
    } catch (const EdgeMissingBeginPoint &e) {
        std::cout << e.what() << std::endl;
    } catch (const EdgeMissingEndPoint &e) {
        std::cout << e.what() << std::endl;
    } catch (const SelfEdge &e) {
        std::cout << e.what() << std::endl;
    } catch (const ParallelEdges &e) {
        std::cout << e.what() << std::endl;
    } catch (const RedefinedVertex &e) {
        std::cout << e.what() << std::endl;
    } catch (const std::bad_alloc &e) {
        std::cout << "Error: bad allocation" << std::endl;
    } catch (const std::exception &exp) {
        std::cout << "Error: Unknown error." << std::endl;
    }
    return nullptr;
}

Graph *addEdge(Graph *graph, const char* v1_input, const char* v2_input) {
    try{
        if(graph == nullptr){
            std::cout << "Error: Graph is null" << std::endl;
            return nullptr;
        }
        std::set<Vertex> vertex_set;
        std::set<Edge> edges_set;

        std::string v1_name(v1_input);
        Vertex v1(v1_name);
        std::string v2_name(v2_input);
        Vertex v2(v2_name);
        if(graph->getVertices().count(v1) == 0){
            throw EdgeMissingBeginPoint(v1_name, v2_name);
        }
        if(graph->getVertices().count(v2) == 0){
            throw EdgeMissingEndPoint(v1_name, v2_name);
        }
        vertex_set.insert(v1);
        vertex_set.insert(v2);

        Edge edge(v1,v2);
        if(graph->getEdges().count(edge) > 0){
            throw ParallelEdges();
        }
        edges_set.insert(edge);

        Graph to_unify(vertex_set, edges_set);
        *graph = *graph + to_unify;

        return graph;
    }catch (const IllegalName &e) {
        std::cout << e.what() << std::endl;
    } catch (const UndefinedVariable &e) {
        std::cout << e.what() << std::endl;
    } catch (const UnrecognizedCommand &e) {
        std::cout << e.what() << std::endl;
    } catch (const EdgeMissingBeginPoint &e) {
        std::cout << e.what() << std::endl;
    } catch (const EdgeMissingEndPoint &e) {
        std::cout << e.what() << std::endl;
    } catch (const SelfEdge &e) {
        std::cout << e.what() << std::endl;
    } catch (const ParallelEdges &e) {
        std::cout << e.what() << std::endl;
    } catch (const RedefinedVertex &e) {
        std::cout << e.what() << std::endl;
    } catch (const std::bad_alloc &e) {
        std::cout << "Error: bad allocation" << std::endl;
    } catch (const std::exception &exp) {
        std::cout << "Error: Unknown error." << std::endl;
    }
    return nullptr;
}

void disp(Graph *graph) {
    if(graph == nullptr){
        std::cout << "Error: Graph is null" << std::endl;
        return;
    }
    printGraph(*graph, std::cout);
}

Graph *graphUnion(Graph *graph_in1, Graph *graph_in2, Graph *graph_out) {
    if( graph_in1 == nullptr || graph_in2 == nullptr || graph_out == nullptr ){
        std::cout << "Error: Graph is null" << std::endl;
        return nullptr;
    }

    *graph_out = *graph_in1 + *graph_in2;
    return graph_out;
}

Graph *graphIntersection(Graph *graph_in1, Graph *graph_in2, Graph *graph_out) {
    if( graph_in1 == nullptr || graph_in2 == nullptr || graph_out == nullptr ){
        std::cout << "Error: Graph is null" << std::endl;
        return nullptr;
    }


    *graph_out = *graph_in1 ^ *graph_in2;
    return graph_out;

}

Graph *graphDifference(Graph *graph_in1, Graph *graph_in2, Graph *graph_out) {
    if( graph_in1 == nullptr || graph_in2 == nullptr || graph_out == nullptr ){
        std::cout << "Error: Graph is null" << std::endl;
        return nullptr;
    }

    *graph_out = *graph_in1 - *graph_in2;
    return graph_out;

}

Graph *graphProduct(Graph *graph_in1, Graph *graph_in2, Graph *graph_out) {
    if(graph_in1 == nullptr || graph_in2 == nullptr || graph_out == nullptr){
        std::cout << "Error: Graph is null" << std::endl;
        return nullptr;
    }
    *graph_out = *graph_in1 * *graph_in2;
    return graph_out;
}

Graph *graphComplement(Graph *graph_in, Graph *graph_out) {
    if(graph_in == nullptr || graph_out == nullptr) {
        std::cout << "Error: Graph is null" << std::endl;
        return nullptr;
    }
    *graph_out = !(*graph_in);
    return graph_out;
}

