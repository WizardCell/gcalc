#ifndef MATAM_GCALC_H
#define MATAM_GCALC_H

#include <iostream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <cassert>
#include <fstream>
#include <stdio.h>

#include "Graph.h"
#include "Exceptions.h"

#define NULLCHAR    '\0'




std::set<Vertex> createSetFromVertexVector(std::vector<std::string>& names_vector){ ///Do I need to keep '&'?
    try {
        std::set<Vertex> new_set;
        for (auto &curr_name : names_vector) {
            Vertex curr_element(curr_name);
            new_set.insert(curr_element);
        }
        return new_set;
    }catch(...){
        throw;
    }
}

Graph executeOperation(Graph& G2, Graph& G3, const char operation){
    switch (operation){
        case('!'):
            return !G3;
        case('+'):
            return G2+G3;
        case('^'):
            return G2^G3;
        case('-'):
            return G2-G3;
        case('*'):
            return G2*G3;
        default:
            //std::cout<<"something very bad happened"<<std::endl;
            // todo remove when we are sure
            return G2;
    }
}


    std::string ltrim(const std::string &s) {
        const std::string WHITESPACE = " \n\v\f\r\t";
        size_t start = s.find_first_not_of(WHITESPACE);
        return (start == std::string::npos) ? "" : s.substr(start);
    }

    std::string rtrim(const std::string &s) {
        const std::string WHITESPACE = " \n\v\f\r\t";
        size_t end = s.find_last_not_of(WHITESPACE);
        return (end == std::string::npos) ? "" : s.substr(0, end + 1);
    }

    std::string trim(const std::string &s) {
        return rtrim(ltrim(s));
    }

    bool isAlphanumeric(const std::string &s) {
        for (auto &character : s) {
            if (!isalnum(character) || !isalpha(s[0])) {
                return false;
            }
        }
        return true;
    }

    std::vector<std::string> split(const std::string& str, const std::string& delimiter){
        std::vector<std::string> tokens;
        size_t prev = 0, pos = 0;
        do
        {
            pos = str.find(delimiter, prev);
            if (pos == std::string::npos) pos = str.length();
            std::string token = str.substr(prev, pos-prev);
            token = trim(token);
            if (!token.empty()) tokens.push_back(token);
            prev = pos + delimiter.length();
        }
        while (pos < str.length() && prev < str.length());
        return tokens;
    }

std::set<Edge> splitEdges(const std::string& str, std::set<Vertex>& Vertex_set){
    try {
        int brackets_counter=0, comma_counter=1;
        std::set<Edge> tokens;
        int opener=-1, comma=-1, ite_number=0;
        if( str[0] != '<'){                             //EdgeCase what if there are no edges
            throw IllegalName();
        }
        if( str[str.length()-1] != '>'){
            throw IllegalName();
        }
        for (auto &character : str) {

            if (character == '<') {
                if(comma_counter != 1){
                    throw IllegalName();
                }
                comma_counter=0;
                brackets_counter++;
                if (brackets_counter > 1) {
                    throw IllegalName();
                }
                opener = ite_number;
            }
            else if (character == '>') {
                if (brackets_counter == 0) {
                    throw IllegalName();
                }
                brackets_counter--;
                int closer = ite_number;

                if( (opener==-1) || (comma == -1) ){
                    throw IllegalName();
                }

                std::string src_vertex_name( str.substr( opener+1 , comma-opener-1 ) );
                std::string dst_vertex_name(str.substr(  comma+1  , closer-comma-1 ) );
                src_vertex_name = trim(src_vertex_name);
                dst_vertex_name = trim(dst_vertex_name);
                if( (src_vertex_name.empty()) || (dst_vertex_name.empty())){
                    throw IllegalName();
                }
                if( (src_vertex_name == dst_vertex_name)){
                    throw SelfEdge();
                }

                Edge edge;
                Vertex src_vertex;
                Vertex dst_vertex;

                src_vertex = Vertex(src_vertex_name);
                dst_vertex = Vertex(dst_vertex_name);
                if( Vertex_set.find(src_vertex) == Vertex_set.end() ){
                    throw UndefinedVariable(src_vertex_name);
                }
                if( Vertex_set.find(dst_vertex) == Vertex_set.end()){
                    throw UndefinedVariable(dst_vertex_name);
                }
                edge = Edge(src_vertex, dst_vertex);
                if(tokens.count(edge) != 0){
                    throw ParallelEdges();
                }
                tokens.insert(edge);

                comma_counter=0;
                opener = -1;
                comma = -1;
            }
            else if (character == ','){
                if( comma_counter != 0){
                    throw IllegalName();
                }
                comma_counter++;
                if(brackets_counter == 1){///This means this is an inner comma
                    comma = ite_number;
                }
                else assert(brackets_counter==0); ///This is an outer comma //PLZ remove
            }
            ite_number++;
        }
        return tokens;
    }catch(...){
        throw;
    }
}

    char checkAndReturnOperation(const std::string &s) {
        for (auto &character : s) {
            if ((character == '+') || (character == '^') || (character == '-') || (character == '*') ||
                (character == '!')) {
                return character;
            }
        }
        return NULLCHAR;
    }

    size_t findOperation(const std::string& s){
        size_t count=0;
        for(auto &character : s){
            if ((character == '+') || (character == '^') || (character == '-') || (character == '*') ||
                (character == '!')) {
                return count;
            }
            count++;
        }
        return std::string::npos;
    }


Graph defineGraph(std::string& lhs, std::string& rhs) {
    try {
        const std::string Comma=",";

        rhs                     = rhs.substr(1, rhs.length()-2); //EdgeCase check this
        size_t separator        = rhs.find_first_of('|');
        //EdgeCase '|' doesnt exist
        std::string vertices    = rhs.substr(0, separator);
        std::string edges       = rhs.substr(separator + 1, std::string::npos);

        vertices                = trim(vertices);
        edges                   = trim(edges);

        std::set<Vertex>          Vertex_set;
        std::vector<std::string>  Vertex_names_vector;
        Vertex_names_vector     = split(vertices, Comma);
        Vertex_set              = createSetFromVertexVector(Vertex_names_vector);

        std::set<Edge> Edge_set = splitEdges(edges, Vertex_set);

        return Graph(Vertex_set, Edge_set);
    }catch(...){
        throw;
    }
}

void printGraph(const Graph& graph, FILE* output){
    for(const auto& v : graph.getVertices()){
        fputs( v.getName().c_str() , output);
        fputs( "\n" , output );
    }

    fputs( "$\n" , output);

    for(const auto& e : graph.getEdges()){
        fputs( e.getSourceVertex().getName().c_str() , output);
        fputs( " " , output );
        fputs( e.getDestinationVertex().getName().c_str() , output);
        fputs( "\n" , output );
    }
}

class Gcalc {
    std::map<std::string, Graph> graphs_map;


public:
    std::string                 prompt;
    bool should_iterate;
    Gcalc():graphs_map(), prompt("Gcalc> "), should_iterate(true){}

    void executeCommand(const std::string &cmd_line, FILE* output) {
        try {
            std::string trimmed_cmd_line = trim(cmd_line);
            unsigned long long eq_sign_index = trimmed_cmd_line.find('=');
            std::string rhs, lhs;
            if (eq_sign_index != std::string::npos) { ///The operation is "LHS = RHS"
                //Todo: put this in a function

                lhs = trimmed_cmd_line.substr(0, eq_sign_index);
                lhs = trim(lhs);
                if (!isAlphanumeric(lhs)) {
                    throw IllegalName();
                }

                rhs = trimmed_cmd_line.substr(eq_sign_index + 1, std::string::npos);
                rhs = trim(rhs);

                //EdgeCase check if parentheses are allowed; example: G1 = (G2 + G3)

                
                char op = checkAndReturnOperation(rhs);
                if ((rhs.find_first_of('{') == 0) &&
                    (rhs.find_last_of('}') == rhs.length() - 1)) {
                    ///case "G1 = { ... | ... }"
                    graphs_map[lhs] = defineGraph(lhs, rhs);
                    return;
                } else if (op == NULLCHAR) {
                    ///RHS has no operations therefore should be " G1 = G2 " (Redefinition)
                    if (!isAlphanumeric(rhs)) {
                        throw IllegalName();
                    } else { ///Indeed "G1 = G2"
                        auto G2 = graphs_map.find(rhs);
                        if (G2 == graphs_map.end()) {     ///G2 is not defined -> Error
                            throw UndefinedVariable(rhs);
                        } else {
                            graphs_map[lhs] = G2->second;
                        }
                    }
                    return;
                }
                ///Here we have "G1 = G2 *op* G3"

                ///find the op
                size_t op_place = findOperation(rhs);

                ///Get "left *op* right"
                std::string left = rhs.substr(0, op_place);
                std::string right = rhs.substr(op_place + 1, std::string::npos);
                left = trim(left);
                right = trim(right);

                ///check if left and right are legal
                if (!isAlphanumeric(left) || !isAlphanumeric(right)) {
                    throw IllegalName();
                }
                ///find G2, G3 in the set
                auto G2 = graphs_map.find(left);
                auto G3 = graphs_map.find(right);
                graphs_map[lhs] = executeOperation(G2->second, G3->second, op);
                //Do the operation on G2 G3.
                return;
            }
            else if(trimmed_cmd_line == "who"){
                for(const auto& graph : graphs_map){
                    fputs( graph.first.c_str() , output);
                    fputs( "\n" , output );
                }
            }
            else if(trimmed_cmd_line == "reset"){
                graphs_map.clear();
            }
            else if(trimmed_cmd_line == "quit"){
                should_iterate = false;
            }
            else if(trimmed_cmd_line.substr(0, 6)  == "print("){
                size_t closer = trimmed_cmd_line.find_last_of(')');
                std::string G = trimmed_cmd_line.substr(6, trimmed_cmd_line.length() - 7); //todo I think 7 instead of 6 also change in delete
                G = trim(G);
                if(!isAlphanumeric(G)){
                    throw IllegalName();
                }
                if(graphs_map.count(G) == 0){
                    throw UndefinedVariable(G);
                }

                //you're okay to print
                printGraph((graphs_map.find(G))->second, output);
            }
            else if(trimmed_cmd_line.substr(0, 7) == "delete("){
                size_t closer = trimmed_cmd_line.find_last_of(')');
                std::string G = trimmed_cmd_line.substr(7, trimmed_cmd_line.length() - 8);
                G = trim(G);
                if(!isAlphanumeric(G)){
                    throw IllegalName();
                }
                if(graphs_map.count(G) == 0){
                    throw UndefinedVariable(G);
                }

                graphs_map.erase(G);
            }
            else if(trimmed_cmd_line.substr(0,5) == "gcalc"){
                std::string IO_names = trimmed_cmd_line.substr(5, std::string::npos);
                IO_names = trim(IO_names);
                size_t space = IO_names.find_first_of(' ');
                std::string input_name = IO_names.substr(0, space);
                std::string output_name = IO_names.substr(space+1, std::string::npos);
                input_name  = trim(input_name);
                output_name = trim(output_name);

                FILE* input_file  = fopen(input_name.c_str() , "r+");
                if(input_file == NULL){
                    std::cout << "NULLED" << std::endl; //todo
                }
                FILE* output_file = fopen(output_name.c_str(), "w");

                Gcalc g_calc_inner = Gcalc();
                while (g_calc_inner.should_iterate) {
                    char cmd_line_inner[255];
                    fgets(cmd_line_inner , 255 , input_file);
                    if(cmd_line_inner[0] == '\0'){
                        break;
                    }
                    g_calc_inner.executeCommand( cmd_line_inner , output_file );
                    cmd_line_inner[0] = '\0';
                }
                fclose(input_file);
                fclose(output_file);
            }
            else{
                throw UnrecognizedCommand(cmd_line);
            }


        }catch(const UndefinedVariable& e){
            fputs( e.what() , output);
            fputs( "\n" , output );
        }
    }

};





#endif //MATAM_GCALC_H
