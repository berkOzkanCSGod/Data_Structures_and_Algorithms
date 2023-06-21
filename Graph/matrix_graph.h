//
// Created by Berk Ozkan on 20.06.2023.
//

#ifndef DATA_STRUCTURES_AND_ALGORITHMS_MATRIX_GRAPH_H
#define DATA_STRUCTURES_AND_ALGORITHMS_MATRIX_GRAPH_H

#include <iostream>
#include "Matrix.h"
#include <queue>
#include <stack>
#include <limits>

typedef char graph_vertex_type;

struct Vertex{
    graph_vertex_type value;
    bool visited = false;
    Vertex(graph_vertex_type v): value(v), visited(false) {}
    Vertex() { value = '\0'; visited = false;}
    //can have more info here
};

class matrix_graph {
public:
    //constructors
        //default
    matrix_graph();
        //copy
    matrix_graph(const matrix_graph*& other);
        //destructor
    ~matrix_graph();

    //methods
        //add vertex
    void add_vertex(graph_vertex_type);
        //remove vertex
    void remove(graph_vertex_type);
        //find vertex
    Vertex* find_vertex_node(graph_vertex_type);
    int find_vertex_index(graph_vertex_type);
        //add edge w/ weight
    void add_edge(graph_vertex_type, graph_vertex_type, int weight = 1, bool directional = false);
        //remove edge
    void remove_edge(graph_vertex_type, graph_vertex_type);
        //print
    void print();
    //traversal
        //BFT
    void breath_first_travers(graph_vertex_type vertex);
    void depth_first_travers(graph_vertex_type vertex);
    void dijkstra(graph_vertex_type);
//    void prim(graph_vertex_type);

private:
    Matrix* matrix;
    Vertex* vertex_list;
    int size;

    int* dijkstra_execute(Vertex*);
//    int* prim_execute(Vertex*);
    void reset_visited_status();
    void directionalize_matrix();
    void un_directionalize_matrix();
    int find_min_edge_index(Vertex* v);


};


#endif //DATA_STRUCTURES_AND_ALGORITHMS_MATRIX_GRAPH_H
