//
// Created by R2 on 06.07.2015.
//

#ifndef MATHPROJECT_MATRIX_H
#define MATHPROJECT_MATRIX_H


#include "Type.h"
#include "AST.h"

class Matrix : public Type {
    double **array;
    int sizeColumn;
    int sizeRow;

public:
    Matrix(int columns, int rows);

    Matrix(double number);

    Matrix(std::vector<std::vector<double>> &v);

    Matrix(const Matrix& other);

    ~Matrix();

    std::string getType();

    bool equals(Type &type);

    bool isNonzero();

    double &element(int i, int j);

    Matrix operator+(Matrix &other);

    Matrix operator-(Matrix &other);

    Matrix operator*(Matrix &other);

    int getRows() { return sizeRow; }

    int getColumns() { return sizeColumn; }

    Matrix elemMulti(Matrix &other);

    Matrix elemExp(Matrix &degree);

    Matrix operator^(Matrix &degree);

    Matrix operator<(Matrix &other);

    Matrix operator>(Matrix &other);

    Matrix operator<=(Matrix &other);

    Matrix operator>=(Matrix &other);

    Matrix operator==(Matrix &other);

    Matrix operator!=(Matrix &other);

    Matrix newIndentityMatrix(Matrix &size);

    virtual void print(std::ostream &os) override;
};


#endif //MATHPROJECT_MATRIX_H
