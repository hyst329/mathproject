//
// Created by R2 on 06.07.2015.
//

#ifndef MATHPROJECT_FUNCTION_H
#define MATHPROJECT_FUNCTION_H

#include "Type.h"
#include "AST.h"
#include <functional>

class Function : public Type {
public:
    virtual Type *operator()(QList<Type *> arguments) = 0;

};

class BuiltinFunction : public Function {
    std::function<Type *(QList<Type *>)> f;

public:
    BuiltinFunction(const function<Type *(QList<Type *>)> &f) : f(f) { }

    virtual Type *operator()(QList<Type *> args);


    virtual bool equals(Type &type);

    virtual bool isNonzero();

    QString getType() {
        return "BuiltinFunction";
    }
};

class UserFunction : public Function {
    Kernel::AST *ast;


public:
    QStringList arguments;

    virtual Type *operator()(QList<Type *> args);

    UserFunction(Kernel::AST *ast, QStringList arguments = QStringList()) : ast(ast), arguments(arguments) {
    }

    virtual bool equals(Type &type);

    virtual bool isNonzero();

    QString getType() {
        return "UserFunction";
    }
};


#endif //MATHPROJECT_FUNCTION_H
