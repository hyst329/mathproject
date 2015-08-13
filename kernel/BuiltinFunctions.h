//
// Created by main on 18.07.2015.
//

#ifndef MATHPROJECT_BUILTINFUNCTIONS_H
#define MATHPROJECT_BUILTINFUNCTIONS_H

#include "Type.h"
#include <QList>

namespace Kernel {
    void initialiseBuiltins();

    Type *add(QList<Type *>);

    Type *subtract(QList<Type *>);

    Type *multiply(QList<Type *>);

    Type *divide(QList<Type *>);

    Type *print(QList<Type *>);

    Type *assign(QList<Type *>);

    Type *pvar(QList<Type *>);

    Type *pfun(QList<Type *>);

    Type *exit(QList<Type *>);

    Type *all(QList<Type *>);

    Type *any(QList<Type *>);

    Type *elemMulti(QList<Type *>);

    Type *elemExp(QList<Type *>);

    Type *exponentation(QList<Type *>);

    Type *more(QList<Type *>);

    Type *moreOrEqual(QList<Type *>);

    Type *less(QList<Type *>);

    Type *lessOrEqual(QList<Type *>);

    Type *equal(QList<Type *>);

    Type *notEqual(QList<Type *>);

    Type *index(QList<Type *>);

    Type *getRows(QList<Type *>);

    Type *getColumns(QList<Type *>);

    Type *getCountOfElements(QList<Type *>);

    Type *getSize(QList<Type *>);

    Type *newIdentityMatrix(QList<Type *>);

    Type *getElement(QList<Type *>);

    Type * isVector(QList<Type *>);

    Type * isScalar(QList<Type *>);

    Type * isInt(QList<Type *>);

    Type * sin(QList<Type *>);

    Type * cos(QList<Type *>);

    Type * tan(QList<Type *>);

    Type * cotan(QList<Type *>);

    Type * asin(QList<Type *>);

    Type * acos(QList<Type *>);

    Type * atan(QList<Type *>);

    Type * acotan(QList<Type *>);

    Type * sinh(QList<Type *>);

    Type * cosh(QList<Type *>);

    Type * tanh(QList<Type *>);

    Type * cotanh(QList<Type *>);
}

#endif //MATHPROJECT_BUILTINFUNCTIONS_H
