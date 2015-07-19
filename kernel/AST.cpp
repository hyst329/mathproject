//
// Created by main on 05.07.2015.
//

#include <iostream>
#include "AST.h"
#include "UserFunction.h"
#include "Error.h"


namespace Kernel {
    map<string, Function *> AST::functions = map<string, Function *>();
    map<string, Type *> AST::variables = map<string, Type *>();
    stack<string> AST::callstack = stack<string>();

    vector<Type *> vAstToType(vector<AST *> initial) {
        vector<Type *> final(initial.size());
        for (int i = 0; i < initial.size(); i++) {
            final[i] = initial[i]->exec();
        }
        return final;
    }

    Type *FunctionAST::exec() {
        if (!functions.count(function))
            Error::error(ET_UNKNOWN_FUNCTION, {function});
        callstack.push(function);
        // TODO: temporary for assign
        Type *r = 0;
        if (function == "$operator=") {
            if(dynamic_cast<VarAST*>(arguments[0]))
                variables[((VarAST*)arguments[0])->name] = arguments[1]->exec();
            else
                Error::error(ET_ASSIGNMENT_ERROR);
        }
        else {
            r = functions[function]->operator()(vAstToType(arguments));
        }
        callstack.pop();
        return r;
    }

    Type *FunctionBodyAST::exec() {
        return NullType::getInstance();
        //return function->operator()(vector<Type *>());
    }
}