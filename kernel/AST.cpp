//
// Created by main on 05.07.2015.
//

#include "AST.h"
#include "Function.h"


namespace Kernel {
    map<string, Function *> AST::functions = std::map<std::string, Function *>();

    vector<Type *> vAstToType(vector<AST *> initial) {
        vector<Type *> final(initial.size());
        int i=0;
        for (auto x:initial) {
            final[i]=x->exec();
        }
        return final;
    }
    Type *FunctionAST::exec() {

        return functions[function]->operator()(vAstToType(arguments));
    }
    Type *FunctionBodyAST::exec() {
        return function->operator()(vector<Type *>());
    }
}