//
// Created by main on 05.07.2015.
//

#include "AST.h"
#include "UserFunction.h"
#include "Error.h"


namespace Kernel {
    map<string, Function *> AST::functions = map<string, Function *>();
    map<string, Type *> AST::variables = map<string, Type *>();
    stack<string> AST::callstack = stack<string>();

    vector<Type *> vAstToType(vector<AST *> initial) {
        vector<Type *> final(initial.size());
        int i = 0;
        for (auto x:initial) {
            final[i] = x->exec();
        }
        return final;
    }

    Type *FunctionAST::exec() {
        if(!functions.count(function))
            Error::error(ET_UNKNOWN_FUNCTION);
        callstack.push(function);
        Type *r = functions[function]->operator()(vAstToType(arguments));
        callstack.pop();
        return r;
    }

    Type *FunctionBodyAST::exec() {
        return 0;
        //return function->operator()(vector<Type *>());
    }
}