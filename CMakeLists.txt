cmake_minimum_required(VERSION 3.13)
project(Matam)

set(CMAKE_CXX_STANDARD 11)

add_executable(Matam Edge.cpp Vertex.cpp ClassGraph.cpp gcalc.h gcalc.cpp Exceptions.h Exceptions.cpp graph.cpp graph.h)