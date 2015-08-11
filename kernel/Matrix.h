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

    Matrix(const Matrix &other);

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

    Matrix newIdentityMatrix(Matrix &size);

    Matrix getElement(Matrix &i, Matrix &j);

    Matrix getElement(Matrix &i);

    Matrix isVector();

    Matrix isScalar();

    Matrix isInt(Matrix eps=Matrix(0e-10));

    bool isVectorBool();

    bool isScalarBool();

    bool isIntBool(double eps=0e-10);

    double toDouble(int i=0,int j=0);

    Matrix setElement(Matrix &i, Matrix &j,Matrix &Value) ;

    virtual void print(std::ostream &os) override;
};


#endif //MATHPROJECT_MATRIX_H
