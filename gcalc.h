#ifndef MATAM_GCALC_H
#define MATAM_GCALC_H

#include <iostream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <cassert>
#include <fstream>
#include <stdio.h>

#include "ClassGraph.h"
#include "Exceptions.h"

#define NULLCHAR    '\0'


Graph executeOperation(const Graph &G2,const Graph &G3, char operation);

std::string ltrim(const std::string &s);

std::string rtrim(const std::string &s);

std::string trim(const std::string &s);

bool isAlphanumeric(const std::string &s);

void splitVertices(std::set<Vertex>& Vertex_set, const std::string &str);

std::set<Edge> splitEdges(const std::string &str, const std::set<Vertex>& Vertex_set);

char returnLastDominantOperation(const std::string &s);

size_t findLastDominantOperation(const std::string &s);

Graph defineGraph(std::string &rhs);

void printGraph(const Graph &graph, std::ostream& output);

std::set<Vertex> readVertices(std::ifstream& infile, unsigned int Vertex_num);

std::set<Edge> readEdges(std::ifstream& infile, unsigned int Edge_num, const std::set<Vertex>& Vertex_set);

Graph executeLoad (const std::string& to_interpret);

void removeParentheses(std::string& to_interpret);

Graph stringToGraph( std::map<std::string, Graph> &graphs_map , std::string to_interpret );

class Gcalc {
    std::map<std::string, Graph> graphs_map;


public:
    bool should_iterate;

    Gcalc();
    ~Gcalc() = default;
    void executeCommand(const std::string &cmd_line, std::ostream& output);

};


#endif //MATAM_GCALC_H
