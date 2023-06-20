//
// Created by Berk Ozkan on 20.06.2023.
//

#ifndef DATA_STRUCTURES_AND_ALGORITHMS_MATRIX_H
#define DATA_STRUCTURES_AND_ALGORITHMS_MATRIX_H

#include <iostream>

class Matrix {
public:
    //default const;
    Matrix();
    //constructor with size
    Matrix(int size);
    //destructor
    ~Matrix();

    void print();

private:
    int** matrix;
    int size;

    void expand();
    void remove_dimention(int index);
    void remove_weight(int index1, int index2);
    void add_weight(int index_row, int index_col, int weight, bool directional);

    friend class matrix_graph;
};


#endif //DATA_STRUCTURES_AND_ALGORITHMS_MATRIX_H
