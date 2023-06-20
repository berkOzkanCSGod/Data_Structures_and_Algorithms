
#include "matrix_graph.h"

matrix_graph::matrix_graph(){
    matrix = new Matrix();
    vertex_list = new Vertex[0];
    size = 0;
}

matrix_graph::matrix_graph(const matrix_graph*& other){
    this->matrix = new Matrix(other->size);
    this->vertex_list = new Vertex[other->size];
    for (int i = 0; i < other->size; ++i) {
        vertex_list[i] = other->vertex_list[i];
        for (int j = 0; j < other->size; ++j) {
            this->matrix->matrix[i][j] =  other->matrix->matrix[i][j];
        }
    }
    this->size = other->size;
}

matrix_graph::~matrix_graph(){
    delete matrix;
    delete vertex_list;
    size = 0;
}

void matrix_graph::add_vertex(graph_vertex_type vertex){
    if (find_vertex_index(vertex) == -1){
        matrix->expand();
        Vertex* new_list = new Vertex[this->size];
        for (int i = 0; i < this->size; ++i) {
            new_list[i] = vertex_list[i];
        }
        new_list[size] = Vertex(vertex);
        delete vertex_list;
        this->size++;

        vertex_list = new_list;
    } else {
        std::cout << "Vertex " << vertex << " already in graph, cannot add again.\n";
    }

}

int matrix_graph::find_vertex_index(graph_vertex_type vertex){
    for (int i = 0; i < size; ++i) {
        if (vertex_list[i].value == vertex)
            return i;
    }
    return -1;
}

void matrix_graph::print(){
    std::cout << "";
    for (int i = 0; i < size; ++i) {
        std::cout << vertex_list[i].value << " ";
    }
    std::cout << "\n";
    matrix->print();

}

void matrix_graph::remove(graph_vertex_type vertex){
    int index = find_vertex_index(vertex);
    if (index != -1){
        matrix->remove_dimention(index);

        Vertex* new_list = new Vertex[this->size-1];
        int x = 0;
        for (int i = 0; i < this->size; ++i) {
            if (index == i)
                continue;
            new_list[x] = vertex_list[i];
            x++;
        }

        delete vertex_list;
        this->size--;

        vertex_list = new_list;

    }
}

void matrix_graph::add_edge(graph_vertex_type v1, graph_vertex_type v2, int weight, bool directional){
    int index1 = find_vertex_index(v1);
    int index2 = find_vertex_index(v2);
    if (index1 >= 0 || index1 < size || index2 >= 0 && index2 < size)
        matrix->add_weight(index1,index2,weight, directional);
}

void matrix_graph::remove_edge(graph_vertex_type v1, graph_vertex_type v2){
    int index1 = find_vertex_index(v1);
    int index2 = find_vertex_index(v2);
    if (index1 >= 0 || index1 < size || index2 >= 0 && index2 < size)
        matrix->remove_weight(index1,index2);
}

Vertex* matrix_graph::find_vertex_node(graph_vertex_type vertex){
    return &vertex_list[find_vertex_index(vertex)];
}