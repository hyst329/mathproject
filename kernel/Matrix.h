//
// Created by R2 on 06.07.2015.
//

#ifndef MATHPROJECT_MATRIX_H
#define MATHPROJECT_MATRIX_H


#include "Type.h"

class Matrix: Type
{
    double **array;
    int sizeColumn;
    int sizeRow;

public:
    Matrix(int columns, int rows);

    ~Matrix();

    std::string getType();

    bool equals(Type &type);
    double & element(int i, int j);

};


#endif //MATHPROJECT_MATRIX_H
