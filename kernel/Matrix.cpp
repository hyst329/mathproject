//
// Created by R2 on 06.07.2015.
//

#include "Matrix.h"
#include "Error.h"

Matrix::Matrix(int rows, int columns) : sizeColumn(columns), sizeRow(rows) {
    array = new double *[rows];
    for (int i = 0; i < rows; i++) array[i] = new double[columns];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            array[i][j] = 0;
        }
    }
}

Matrix::Matrix(double number) : Matrix(1, 1) {
    **array = number;
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

double &Matrix::element(int i, int j) {
    return array[i - 1][j - 1];
}

bool Matrix::isNonzero() {
    for (int i = 0; i < sizeRow; i++)
        for (int j = 0; j < sizeColumn; j++)
            if (array[i][j]) return true;
    return false;
}

Matrix::Matrix(vector<vector<double>> &v) {
    sizeRow = v.size();
    sizeColumn = 0;
    for (int i = 0; i < sizeRow; i++) {
        if (v[i].size() > sizeColumn) sizeColumn = v[i].size();
    }
    array = new double *[sizeRow];
    for (int i = 0; i < sizeRow; i++) array[i] = new double[sizeColumn];
    for (int i = 0; i < sizeRow; i++) {
        for (int j = 0; j < sizeColumn; j++) {
            array[i][j] = v[i].size() > j ? v[i][j] : 0;
        }
    }
}

Matrix Matrix::operator+(Matrix &other) {
    if (other.sizeRow != sizeRow or other.sizeColumn != sizeColumn) Error::error(ET_DIMENSIONS_MISMATCH);
    Matrix res = Matrix(sizeRow, sizeColumn);
    for (int i = 0; i < sizeRow; i++)
        for (int j = 0; j < sizeColumn; j++)
            res.array[i][j] = array[i][j] + other.array[i][j];
    return res;
}

Matrix Matrix::operator-(Matrix &other) {
    if (other.sizeRow != sizeRow or other.sizeColumn != sizeColumn) Error::error(ET_DIMENSIONS_MISMATCH);
    Matrix res = Matrix(sizeRow, sizeColumn);
    for (int i = 0; i < sizeRow; i++)
        for (int j = 0; j < sizeColumn; j++)
            res.array[i][j] = array[i][j] - other.array[i][j];
    return res;
}

Matrix Matrix::operator*(Matrix &other) {
    if (sizeColumn == 1 and sizeRow == 1) {
        Matrix res = Matrix(other.sizeRow, other.sizeColumn);
        for (int i = 0; i < other.sizeRow; i++)
            for (int j = 0; j < other.sizeColumn; j++)
                res.array[i][j] = other.array[i][j] * array[0][0];
        return res;
    }
    if (other.sizeColumn == 1 and other.sizeRow == 1) {
        Matrix res = Matrix(sizeRow, sizeColumn);
        for (int i = 0; i < sizeRow; i++)
            for (int j = 0; j < sizeColumn; j++)
                res.array[i][j] = array[i][j] * other.array[0][0];
        return res;
    }
    if (sizeColumn != other.sizeRow) Error::error(ET_DIMENSIONS_MISMATCH);
    Matrix res = Matrix(sizeRow, other.sizeColumn);
    for (int i = 0; i < sizeRow; i++)
        for (int j = 0; j < other.sizeColumn; j++) {
            for (int k = 0; k < sizeColumn; k++)
                res.array[i][j] += array[i][k] * other.array[k][j];

        }
    return res;
}

void Matrix::print(std::ostream &os) {
    os << "{";
    for (int i = 0; i < sizeRow; i++)
        for (int j = 0; j < sizeColumn; j++)
            os << array[i][j] << (j != sizeColumn - 1 ? ", " : (i != sizeRow - 1 ? "; " : "}"));
}

Matrix::Matrix(const Matrix &other) : Matrix(other.sizeRow, other.sizeColumn) {
    for (int i = 0; i < sizeRow; i++)
        for (int j = 0; j < sizeColumn; j++)
            array[i][j] = other.array[i][j];
}

Matrix Matrix::elemMulti(Matrix &other) {
    if (sizeColumn != other.sizeColumn || sizeRow != other.sizeRow)
        Error::error(ET_DIMENSIONS_MISMATCH);
    Matrix res = Matrix(sizeRow, other.sizeColumn);
    for (int i = 0; i < sizeRow; i++)
        for (int j = 0; j < other.sizeColumn; j++) {
            res.array[i][j] = array[i][j] * other.array[i][j];
        }
    return res;

}

Matrix Matrix::elemExp(int degree) {
    Matrix res = Matrix(sizeRow, sizeColumn);
    if (degree==0) {
        for (int i=0;i<sizeRow;i++)
            for (int j=0;j < sizeColumn;j++)
                if (array[i][j]!=0)
                    res.array[i][j]=1;
                //else TODO:exeption(0^0)
    }
    else {
        Matrix tmp = Matrix(sizeRow, sizeColumn);
        for (int i=0;i<sizeRow;i++)
            for (int j=0;j < sizeColumn;j++) {
                res.array[i][j] = 1;
                tmp.array[i][j] = array[i][j];
            }
        while (degree !=0) {
            if (degree%2!=0) {
                for (int i=0;i<sizeRow;i++)
                    for (int j=0;j < sizeColumn;j++)
                        res.array[i][j]*=tmp.array[i][j];
                degree--;
            }
            for (int i=0;i<sizeRow;i++)
                for (int j=0;j < sizeColumn;j++)
                    tmp.array[i][j]*=tmp.array[i][j];
            degree/=2;
        }
    }
    return res;
}

Matrix Matrix::operator^(int degree) {
    Matrix res = Matrix(sizeRow, sizeColumn);
    Matrix tmp = Matrix(sizeRow, sizeColumn);
    for (int i=0;i<sizeRow;i++)
        for (int j=0;j < sizeColumn;j++) {
            res.array[i][j] = 1;
            tmp.array[i][j] = array[i][j];
        }
    while (degree != 0)
    {
        if (degree % 2 != 0)
        {
            res = res*tmp;
            degree -= 1;
        }
        tmp = tmp*tmp;
        degree /= 2;
    }
    return res;
}
Matrix Matrix::elemExp(double degree) {
    Matrix res = Matrix(sizeRow, sizeColumn);
    for (int i=0;i<sizeRow;i++)
        for (int j=0;j < sizeColumn;j++)
            res.array[i][j]=pow(array[i][j],degree);
}