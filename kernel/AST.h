//
// Created by main on 05.07.2015.
//

#ifndef MATHPROJECT_AST_H
#define MATHPROJECT_AST_H

#include <vector>
#include <map>
#include <stack>
#include "Type.h"
#include "NullType.h"


using namespace std;
class Function;
namespace Kernel {

    struct AST {
        virtual Type *exec() = 0;

        static map<string, Function *> functions;
        static map<string, Type*> variables;
        static stack<string> callstack;

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

    struct FunctionAST : public AST {
        std::string function;
        vector<AST *> arguments;

        FunctionAST(std::string function, vector<AST *> arguments = vector<AST *>())
                : function(function), arguments(arguments) { };

        Type *exec() ;
    };

    struct FunctionBodyAST : public AST {
        Function * function;

        FunctionBodyAST(Function *function)
                : function(function){ };
        Type *exec();
    };

    struct VarAST : public AST {
        string name;

        VarAST(string name)
                : name(name) { };

        Type *exec() {
            return AST::variables[name];
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
            return NullType::getInstance();
        }
    };

    struct ReturnAST : public AST {
        AST *returnValue;

        ReturnAST(AST *returnValue) : returnValue(returnValue) { }

        Type *exec() {
            //TODO(hyst329): switch the control to main "function"
            return returnValue->exec();
        }
    };
}

#endif //MATHPROJECT_AST_H
