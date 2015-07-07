//
// Created by R2 on 06.07.2015.
//

#include "Matrix.h"


char *Matrix::getType() {
    char *text = "Matrix";
    return text;
}

bool Matrix::equals(Type type) {
    return false;
}

double & Matrix::element(int i, int j) {
    return array[i-1][j-1];
}

