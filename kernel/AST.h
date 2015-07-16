//
// Created by main on 05.07.2015.
//

#ifndef MATHPROJECT_AST_H
#define MATHPROJECT_AST_H

#include <vector>
#include <map>
#include "Type.h"
#include "Function.h"
#include <map>


using namespace std;
class Function;

namespace Kernel {

    struct AST {
        virtual Type *exec() = 0;

        map<string, Type *> *variables;
        static map<string, Function*> functions;

    };

    struct BlockAST : public AST {
        vector<AST *> children;

        Type *exec() {
            for (AST *a: children) a->exec();
        }
    };

    struct TypeAST : public AST {
        Type *value;

        Type *exec() {
            return value;
        }

        TypeAST(Type *v) : value(v) { };
    };
    vector<Type *> vAstToType(vector<AST *> initial) {
        vector<Type *> final(initial.size());
        int i=0;
        for (auto x:initial) {
            final[i]=x->exec();
        }
        return final;
    }
    struct FunctionAST : public AST {
        std::string function;
        vector<AST *> arguments;

        FunctionAST(std::string function, vector<AST *> arguments = vector<AST *>())
                : function(function), arguments(arguments) { };

        Type *exec() {
            return AST().functions[function]->operator()(vAstToType(arguments));
            // TODO: Add Function call
           // return 0;//function(arguments)->exec();
        }
    };

    struct FunctionBodyAST : public AST {
        Function* function;

        FunctionBodyAST(Function *function)
                : function(function){ };

        Type *exec() {
            return function->operator()();
            // TODO: Add Function call
            //return 0;//function(arguments)->exec();
        }
    };

    struct VarAST : public AST {
        string name;

        VarAST(string name)
                : name(name) { };

        Type *exec() {
            return (*variables)[name];
        }
    };

    struct ConditionalAST : public AST {
        AST *branchIf, *branchThen, *branchElse;

        ConditionalAST(AST *ifAST, AST *thenAST, AST *elseAST)
                : branchIf(ifAST), branchThen(thenAST), branchElse(elseAST) { };

        Type *exec() {
            if (branchIf->exec()->isNonzero())
                return branchThen->exec();
            else
                return branchElse->exec();
        }
    };

    struct WhileLoopAST : public AST {
        AST *condition, *iteration;

        WhileLoopAST(AST *condition, AST *iteration) : condition(condition), iteration(iteration) { }

        Type *exec() {
            while (condition->exec()->isNonzero())
                iteration->exec();
            return 0;
        }
    };
}

#endif //MATHPROJECT_AST_H
