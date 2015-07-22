//
// Created by main on 18.07.2015.
//

#ifndef MATHPROJECT_BUILTINFUNCTIONS_H
#define MATHPROJECT_BUILTINFUNCTIONS_H

#include "Type.h"
#include <vector>

namespace Kernel {
    void initialiseBuiltins();
    Type *add(std::vector<Type *>);
    Type *subtract(std::vector<Type *>);
    Type *multiply(std::vector<Type *>);
    Type *divide(std::vector<Type *>);
    Type *print(std::vector<Type *>);
    Type *assign(std::vector<Type *>);
    Type *pvar(std::vector<Type *>);
    Type *pfun(std::vector<Type *>);
    Type *exit(std::vector<Type *>);
    Type *all(std::vector<Type *>);
    Type *any(std::vector<Type *>);

    Type *elemMulti(std::vector<Type *>);
    Type *elemExp(std::vector<Type *>);
    Type *exponentation(std::vector<Type *>);
    Type *more(std::vector<Type *>);
    Type *moreOrEqual(std::vector<Type *>);
    Type *less(std::vector<Type *>);
    Type *lessOrEqual(std::vector<Type *>);
    Type *equal(std::vector<Type *>);
    Type *notEqual(std::vector<Type *>);
    Type *getRows(std::vector<Type *>);
    Type *getColumns(std::vector<Type *>);
    Type *getCountOfElements(std::vector<Type *>);
    Type *getSize(std::vector<Type *>);
    Type *newIndentityMatrix(std::vector<Type *>);
}

#endif //MATHPROJECT_BUILTINFUNCTIONS_H
