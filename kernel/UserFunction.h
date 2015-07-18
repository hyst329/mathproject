//
// Created by R2 on 06.07.2015.
//

#ifndef MATHPROJECT_FUNCTION_H
#define MATHPROJECT_FUNCTION_H

#include <vector>
#include "Type.h"
#include "AST.h"
#include <map>
#include <functional>

class Function : public Type {
public:
    virtual Type* operator()(std::vector<Type*> arguments) = 0;

};

class BuiltinFunction : public Function {
    std::function<Type*(std::vector<Type*>)> f;

public:
    BuiltinFunction(const function<Type*(std::vector<Type*>)> &f) : f(f) { }

    virtual Type *operator()(std::vector<Type *> args);


    virtual bool equals(Type &type);

    virtual bool isNonzero();

    std::string getType() {
        return "BuiltinFunction";
    }
};

class UserFunction :  public Function {
    Kernel::AST *ast;


public:
    vector<string> arguments;

    virtual Type *operator()(std::vector<Type *> args);

    UserFunction(Kernel::AST *ast, vector<string> arguments = vector<string>()) : ast(ast), arguments(arguments) {
    }

    virtual bool equals(Type &type);

    virtual bool isNonzero();

    std::string getType() {
        return "UserFunction";
    }
};


#endif //MATHPROJECT_FUNCTION_H
