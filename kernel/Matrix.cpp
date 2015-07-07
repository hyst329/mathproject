//
// Created by R2 on 06.07.2015.
//

#include "Matrix.h"

Matrix::Matrix(int rows, int columns) : sizeColumn(columns), sizeRow(rows) {
    array = new double *[rows];
    for (int i = 0; i < rows; i++) array[i] = new double[columns];
}

Matrix::~Matrix() {
    for (int i = 0; i < sizeRow; i++) delete[] array[i];
    delete[] array;
}

std::string Matrix::getType() {
    return "Matrix";
}

bool Matrix::equals(Type &type) {
    return false;
}

double & Matrix::element(int i, int j) {
    return array[i-1][j-1];
}
