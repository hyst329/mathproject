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
    virtual Type *operator()(QList<Type *> args) = 0;
    QList<int> getReferenceVars() const;

protected:
    QList<int> referenceVars;
};

class BuiltinFunction : public Function {
    std::function<Type *(QList<Type *>)> f;

public:
    BuiltinFunction(const function<Type *(QList<Type *>)> &f, QList<int> referenceVars = QList<int>())
        : f(f) {
        this->referenceVars = referenceVars;
    }

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

    UserFunction(Kernel::AST *ast, QStringList arguments = QStringList())
        : ast(ast), arguments(arguments) {
            for(int i = 0; i < arguments.size(); i++)
                if(arguments[i].startsWith("ref ")) {
                    arguments[i] = arguments[i].mid(4);
                    referenceVars << (i + 1);
                }
    }

    virtual bool equals(Type &type);

    virtual bool isNonzero();

    QString getType() {
        return "UserFunction";
    }
};


#endif //MATHPROJECT_FUNCTION_H
