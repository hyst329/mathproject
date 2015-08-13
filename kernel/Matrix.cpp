//
// Created by R2 on 06.07.2015.
//

#include "Matrix.h"
#include "Error.h"
#include <cmath>
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

QString Matrix::getType() {
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

Matrix::Matrix(QList<QList<double> > &v) {
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

Matrix &Matrix::operator=(const Matrix &other)
{
    for (int i = 0; i < sizeRow; i++) delete[] array[i];
    delete[] array;
    sizeRow = other.sizeRow;
    sizeColumn = other.sizeColumn;
    array = new double *[sizeRow];
    for (int i = 0; i < sizeRow; i++) array[i] = new double[sizeColumn];
    for (int i = 0; i < sizeRow; i++) {
        for (int j = 0; j < sizeColumn; j++) {
            array[i][j] = other.array[i][j];
        }
    }
}

QString Matrix::toString() {
    QString res;
    res += "{";
    for (int i = 0; i < sizeRow; i++)
        for (int j = 0; j < sizeColumn; j++) {
            res += QString::number(array[i][j]);
            res += (j != sizeColumn - 1 ? ", " : (i != sizeRow - 1 ? "; " : "}"));
        }
    return res;
}

Matrix::Matrix(const Matrix &other) : sizeRow(other.sizeRow), sizeColumn(other.sizeColumn) {
    array = new double *[other.sizeRow];
    for (int i = 0; i < other.sizeRow; i++) array[i] = new double[other.sizeColumn];
    for (int i = 0; i < sizeRow; i++)
        for (int j = 0; j < sizeColumn; j++)
            array[i][j] = other.array[i][j];
}

Matrix Matrix::elemMulti(Matrix &other) {
    if (sizeColumn != other.sizeColumn || sizeRow != other.sizeRow)
        Error::error(ET_DIMENSIONS_MISMATCH);
    Matrix res = Matrix(sizeRow,sizeColumn);
    for (int i = 0; i < sizeRow; i++)
        for (int j = 0; j < other.sizeColumn; j++) {
            res.array[i][j] = array[i][j] * other.array[i][j];
        }
    return res;

}

Matrix Matrix::operator^(Matrix &x) {
    if (x.sizeColumn!=1||x.sizeRow!=1||sizeRow!=sizeColumn)
        Error::error(ET_DIMENSIONS_MISMATCH);
    //if (x.array[0][0]-(double)((int)x.array[0][0])>=1.e-10)
        //TODO:error(matrix^double)
    int degree=(int)(x.array[0][0]);
    Matrix res = Matrix(sizeRow, sizeColumn);
    Matrix tmp = Matrix(sizeRow, sizeColumn);
    for (int i=0;i<sizeRow;i++)
        for (int j=0;j < sizeColumn;j++) {
            tmp.array[i][j] = array[i][j];
            res.array[i][j]=(i==j);
        }

    while (degree != 0)
    {
        if (degree % 2)
        {
            res = res*tmp;
        }
        tmp = tmp*tmp;
        degree=degree/2;
    }

    return res;
}

Matrix Matrix::elemExp(Matrix &x) {
    Matrix res = Matrix(sizeRow, sizeColumn);
    if (x.sizeColumn==1&&x.sizeRow==1) {
        double degree = x.array[0][0];
        for (int i = 0; i < sizeRow; i++)
            for (int j = 0; j < sizeColumn; j++)
                res.array[i][j] = pow(array[i][j], degree);
        return res;
    }
    if (x.sizeColumn==sizeColumn&&x.sizeRow==sizeRow) {
        for (int i = 0; i < sizeRow; i++)
            for (int j = 0; j < sizeColumn; j++)
                res.array[i][j] = pow(array[i][j], x.array[i][j]);
        return res;
    }
    if (x.sizeColumn!=sizeColumn||x.sizeRow!=sizeRow)
    {
        Error::error(ET_DIMENSIONS_MISMATCH);
    }
    return res;
}

Matrix Matrix::operator<(Matrix &other) {
    Matrix res = Matrix(1,1);
    for (int i=0;i<sizeRow;i++)
        for (int j=0;j < sizeColumn;j++)
            if (array[i][j]>=other.array[i][j]) {
                res.array[0][0]=0;
                return res;
            }
    res.array[0][0]=1;
    return res;
}

Matrix Matrix::operator>(Matrix &other) {
    Matrix res = Matrix(1,1);
    for (int i=0;i<sizeRow;i++)
        for (int j=0;j < sizeColumn;j++)
            if (array[i][j]<=other.array[i][j]) {
                res.array[0][0]=0;
                return res;
            }
    res.array[0][0]=1;
    return res;
}

Matrix Matrix::operator<=(Matrix &other) {
    Matrix res = Matrix(1,1);
    for (int i=0;i<sizeRow;i++)
        for (int j=0;j < sizeColumn;j++)
            if (array[i][j]>other.array[i][j]) {
                res.array[0][0]=0;
                return res;
            }
    res.array[0][0]=1;
    return res;
}

Matrix Matrix::operator>=(Matrix &other) {
    Matrix res = Matrix(1,1);
    for (int i=0;i<sizeRow;i++)
        for (int j=0;j < sizeColumn;j++)
            if (array[i][j]<other.array[i][j]) {
                res.array[0][0]=0;
                return res;
            }
    res.array[0][0]=1;
    return res;
}

Matrix Matrix::operator==(Matrix &other) {
    Matrix res = Matrix(1,1);
    for (int i=0;i<sizeRow;i++)
        for (int j=0;j < sizeColumn;j++)
            if (array[i][j]!=other.array[i][j]) {
                res.array[0][0]=0;
                return res;
            }
    res.array[0][0]=1;
    return res;
}

Matrix Matrix::operator!=(Matrix &other) {
    Matrix res = Matrix(1,1);
    for (int i=0;i<sizeRow;i++)
        for (int j=0;j < sizeColumn;j++)
            if (array[i][j]!=other.array[i][j]) {
                res.array[0][0]=1;
                return res;
            }
    res.array[0][0]=0;
    return res;
}

Matrix Matrix::newIdentityMatrix(int size) {
    Matrix res(size, size);
    for(int i=0;i<size;i++)
        res.array[i][i]=1;
    return res;
}


Matrix Matrix::sin() {
    Matrix res(sizeRow,sizeColumn);
    for(int i=0;i<res.getRows();i++)
        for (int j=0;j<res.getColumns();j++)
            res.array[i][j]=std::sin(array[i][j]);
    return res;
}


Matrix Matrix::cos() {
    Matrix res(sizeRow,sizeColumn);
    for(int i=0;i<res.getRows();i++)
        for (int j=0;j<res.getColumns();j++)
            res.array[i][j]=std::cos(array[i][j]);
    return res;
}


Matrix Matrix::tan() {
    Matrix res(sizeRow,sizeColumn);
    for(int i=0;i<res.getRows();i++)
        for (int j=0;j<res.getColumns();j++)
            res.array[i][j]=std::tan(array[i][j]);
    return res;
}

Matrix Matrix::cotan() {
    Matrix res(sizeRow,sizeColumn);
    for(int i=0;i<res.getRows();i++)
        for (int j=0;j<res.getColumns();j++)
            res.array[i][j]=1/std::tan(array[i][j]);

    return res;
}

Matrix Matrix::asin() {
    Matrix res(sizeRow,sizeColumn);
    for(int i=0;i<res.getRows();i++)
        for (int j=0;j<res.getColumns();j++)
            res.array[i][j]=std::asin(array[i][j]);
    return res;
}


Matrix Matrix::acos() {
    Matrix res(sizeRow,sizeColumn);
    for(int i=0;i<res.getRows();i++)
        for (int j=0;j<res.getColumns();j++)
            res.array[i][j]=std::acos(array[i][j]);
    return res;
}


Matrix Matrix::atan() {
    Matrix res(sizeRow,sizeColumn);
    for(int i=0;i<res.getRows();i++)
        for (int j=0;j<res.getColumns();j++)
            res.array[i][j]=std::atan(array[i][j]);
    return res;
}

Matrix Matrix::acotan() {
    Matrix res(sizeRow,sizeColumn);
    for(int i=0;i<res.getRows();i++)
        for (int j=0;j<res.getColumns();j++)
            res.array[i][j]=std::atan(1/array[i][j]);

    return res;
}

Matrix Matrix::sinh() {
    Matrix res(sizeRow,sizeColumn);
    for(int i=0;i<res.getRows();i++)
        for (int j=0;j<res.getColumns();j++)
            res.array[i][j]=std::sinh(array[i][j]);
    return res;
}


Matrix Matrix::cosh() {
    Matrix res(sizeRow,sizeColumn);
    for(int i=0;i<res.getRows();i++)
        for (int j=0;j<res.getColumns();j++)
            res.array[i][j]=std::cosh(array[i][j]);
    return res;
}


Matrix Matrix::tanh() {
    Matrix res(sizeRow,sizeColumn);
    for(int i=0;i<res.getRows();i++)
        for (int j=0;j<res.getColumns();j++)
            res.array[i][j]=std::tanh(array[i][j]);
    return res;
}

Matrix Matrix::cotanh() {
    Matrix res(sizeRow,sizeColumn);
    for(int i=0;i<res.getRows();i++)
        for (int j=0;j<res.getColumns();j++)
            res.array[i][j]=1/std::tanh(array[i][j]);

    return res;
}

Matrix Matrix::exp() {
    Matrix res(*this);
    for (int i=0;i<sizeRow;i++)
        for (int j=0;j<sizeColumn;j++)
            res.array[i][j]=std::exp(array[i][j]);
    return res;
}

Matrix Matrix::ln() {
    Matrix res(*this);
    for (int i=0;i<sizeRow;i++)
        for (int j=0;j<sizeColumn;j++)
            res.array[i][j]=std::log(array[i][j]);
    return res;
}

Matrix Matrix::lg() {
    Matrix res(*this);
    for (int i=0;i<sizeRow;i++)
        for (int j=0;j<sizeColumn;j++)
            res.array[i][j]=std::log10(array[i][j]);
    return res;
}

Matrix Matrix::log(Matrix &value) {
    Matrix res(*this);
    if (value.sizeColumn==1&&value.sizeRow==1)
    {
        double loge=std::log(value.array[0][0]);
        for (int i=0;i<sizeRow;i++)
            for (int j=0;j<sizeColumn;j++)
                res.array[i][j]=std::log(array[i][j])/loge;
    }
    if (value.sizeColumn==sizeColumn&&value.sizeRow==sizeRow)
    {
        for (int i=0;i<sizeRow;i++)
            for (int j=0;j<sizeColumn;j++)
                res.array[i][j]=std::log(array[i][j])/std::log(value.array[i][j]);
    }
    Error::error(ET_DIMENSIONS_MISMATCH);

    return res;
}
