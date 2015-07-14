//
// Created by R2 on 06.07.2015.
//

#ifndef MATHPROJECT_MATRIX_H
#define MATHPROJECT_MATRIX_H


#include "Type.h"
#include "AST.h"

class Matrix : public Type
{
    double **array;
    int sizeColumn;
    int sizeRow;

public:
    Matrix(int columns, int rows);

    Matrix(double number);

    Matrix(std::vector<std::vector<double>> &v);

    ~Matrix();

    std::string getType();

    bool equals(Type &type);

    bool isNonzero();
    double & element(int i, int j);

};


#endif //MATHPROJECT_MATRIX_H
