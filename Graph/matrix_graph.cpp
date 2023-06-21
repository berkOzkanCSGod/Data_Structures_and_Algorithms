
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
        if (index1 != index2)
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

void matrix_graph::breath_first_travers(graph_vertex_type vertex){
    std::queue<Vertex*> Q;
    int vertex_index;

    Q.push(find_vertex_node(vertex));
    vertex_list[find_vertex_index(vertex)].visited = true;

    while (!Q.empty()){

        for (int i = 0; i < size; ++i) {
            vertex_index = find_vertex_index(Q.front()->value);
            if (matrix->matrix[vertex_index][i] > 0){
                if (!vertex_list[i].visited) {
                    Q.push(&vertex_list[i]);
                    vertex_list[i].visited = true;
                }
            }
        }

        std::cout << Q.front()->value << " ";
        Q.pop();
    }

    reset_visited_status();

    std::cout << "\n";
    std::cout << "\n";
}

void matrix_graph::depth_first_travers(graph_vertex_type vertex){
    std::stack<Vertex*> S;
    int vertex_index;

    S.push(find_vertex_node(vertex));
    vertex_list[find_vertex_index(vertex)].visited = true;

    while (!S.empty()){
        for (int i = 0; i < size; ++i) {
            vertex_index = find_vertex_index(S.top()->value);
            if (matrix->matrix[vertex_index][i] > 0){
                if (!vertex_list[i].visited) {
                    S.push(&vertex_list[i]);
                    vertex_list[i].visited = true;

                }
            }
        }

        std::cout << S.top()->value << " ";
        S.pop();
    }

    reset_visited_status();

    std::cout << "\n";
    std::cout << "\n";
}

void matrix_graph::reset_visited_status() {
    for (int i = 0; i < size; ++i) {
        vertex_list[i].visited = false;
    }
}

void matrix_graph::dijkstra(graph_vertex_type v){

    reset_visited_status();

    //turn matrix into inf
    directionalize_matrix();

    int* weight = dijkstra_execute(find_vertex_node(v));
    for (int i = 0; i < size; ++i) {
        std::cout << vertex_list[i].value << " ";
    }
    std::cout << "\n";

    for (int i = 0; i < size; ++i) {
        if (weight[i] == std::numeric_limits<int>::max()){
            std::cout << "INF ";
        } else {
            std::cout << weight[i] << " ";
        }
    }
    std::cout << "\n";

    //turn matrix back to normal
    un_directionalize_matrix();
    reset_visited_status();
    delete [] weight;
}
//void matrix_graph::prim(graph_vertex_type v){
//    reset_visited_status();
//    int* tree;
//
//
//
//
//    reset_visited_status();
//    delete [] tree;
//}

void matrix_graph::directionalize_matrix(){
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (matrix->matrix[i][j] == 0){
                matrix->add_weight(i,j,std::numeric_limits<int>::max(), true);
            }
        }
    }
}
void matrix_graph::un_directionalize_matrix(){
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (matrix->matrix[i][j] == std::numeric_limits<int>::max()){
                matrix->add_weight(i,j,0, true);
            }
        }
    }
}

int* matrix_graph::dijkstra_execute(Vertex* v) {
    int* weight = new int[size];
    int vertex_index = find_vertex_index(v->value);

    //copy row of starting vertex
    for (int i = 0; i < size; ++i) {
        weight[i] = matrix->matrix[vertex_index][i];
    }

    //cycle through each node
    for (int count = 0; count < size; ++count) {
        v->visited = true;
        vertex_index = find_vertex_index(v->value);
        //cycle through each edge
        for (int i = 0; i < size; ++i) {
            if (!vertex_list[i].visited){
                if ( weight[vertex_index] < std::numeric_limits<int>::max() && matrix->matrix[vertex_index][i] < std::numeric_limits<int>::max() && weight[i] > weight[vertex_index]+matrix->matrix[vertex_index][i]){
                    weight[i] = weight[vertex_index]+matrix->matrix[vertex_index][i];
                }
            }
        }
        int min_index = 0;
        for (int i = 0; i < size; ++i) {
            if (!vertex_list[i].visited && weight[i] < weight[min_index]){
                min_index = i;
            }
        }
        v = &vertex_list[min_index];
    }



    return weight;
}
//int* matrix_graph::prim_execute(Vertex* v) {
//    int* tree = new int[size];
//    int vertex_index = find_vertex_index(v->value);
//
//    tree[0];
//
//
//    return tree;
//}

int matrix_graph::find_min_edge_index(Vertex* v){
    int v_index = find_vertex_index(v->value);

    int min_index = 0;
    for (int i = 0; i < size; ++i) {
        if (!vertex_list[i].visited && matrix->matrix[v_index][i] < matrix->matrix[v_index][min_index]){
            min_index = i;
        }
    }

}
