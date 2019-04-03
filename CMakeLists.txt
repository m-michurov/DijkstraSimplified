cmake_minimum_required(VERSION 3.12)
project(DijkstraSimplified C)

set(CMAKE_C_STANDARD 11)

add_executable(Dijkstra main.c graph.c graph.h dijkstra.c errcodes.h ensure.h)