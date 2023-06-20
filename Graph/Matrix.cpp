//
// Created by Berk Ozkan on 20.06.2023.
//

#include "Matrix.h"

Matrix::Matrix() {
    matrix = new int*();
    size = 0;
}

Matrix::Matrix(int size) {
    matrix = new int*[size];
    for (int i = 0; i < size; ++i) {
        matrix[i] = new int[size];
    }
    this->size = size;
}

Matrix::~Matrix() {
    for (int i = 0; i < this->size; ++i) {
        delete [] matrix[i];
    }
    delete [] matrix;
    this->size = 0;
}

void Matrix::expand(){
    Matrix* new_matrix = new Matrix(this->size+1);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            new_matrix->matrix[i][j] = this->matrix[i][j];
        }
    }
    delete this->matrix;
    this->matrix = new_matrix->matrix;
    this->size = new_matrix->size;
}

void Matrix::remove_dimention(int index) {
    if (index > size-1)
        return;
    Matrix* new_matrix = new Matrix(this->size-1);
    int x = 0,y = 0;
    for (int i = 0; i < size; ++i) {
        y = 0;
        if (index == i)
            continue;
        for (int j = 0; j < size; ++j) {
            if (index == j)
                continue;
            new_matrix->matrix[x][y] = this->matrix[i][j];
            y++;
        }
        x++;
    }
    delete this->matrix;
    this->matrix = new_matrix->matrix;
    this->size = new_matrix->size;
}

void Matrix::print(){
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::printf("%d ", matrix[i][j]);
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void Matrix::add_weight(int index_row, int index_col, int weight, bool directional){
    if(directional) {
        this->matrix[index_row][index_col] = weight;
    } else {
        this->matrix[index_row][index_col] = weight;
        this->matrix[index_col][index_row] = weight;
    }
}

void Matrix::remove_weight(int index_row, int index_col){
    this->matrix[index_row][index_col] = 0;
    this->matrix[index_col][index_row] = 0;
}
