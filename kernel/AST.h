//
// Created by main on 05.07.2015.
//

#ifndef MATHPROJECT_AST_H
#define MATHPROJECT_AST_H

#include <QList>
#include <QMap>
#include <QStack>
#include <iostream>
#include "Type.h"
#include "NullType.h"


using namespace std;

class Function;
namespace Kernel {

    struct AST {
        virtual Type *exec() = 0;

        static QMap<QString, Function *> functions;
        static QMap<QString, Type *> variables;
        static QStack<QString> callstack;

    };

    struct BlockAST : public AST {
        QList<AST *> children;

        Type *exec();
    };

    struct TypeAST : public AST {
        Type *value;

        Type *exec() {
            return value;
        }

        TypeAST(Type *v) : value(v) { }
    };

    struct FunctionAST : public AST {
        QString function;
        QList<AST *> arguments;

        FunctionAST(QString function, QList<AST *> arguments)
                : function(function), arguments(arguments) { }

        Type *exec();
    };

    struct FunctionBodyAST : public AST {
        Function *function;

        FunctionBodyAST(Function *function)
                : function(function) { }

        Type *exec();
    };

    struct VarAST : public AST {
        QString name;

        VarAST(QString name)
                : name(name) { }

        Type *exec() {
            return AST::variables[name];
        }
    };

    struct ConditionalAST : public AST {
        AST *branchIf, *branchThen, *branchElse;

        ConditionalAST(AST *ifAST, AST *thenAST, AST *elseAST)
                : branchIf(ifAST), branchThen(thenAST), branchElse(elseAST) { }

        Type *exec() {
            auto bif = branchIf->exec();
            if (bif->isNonzero())
                branchThen->exec();
            else if (branchElse) branchElse->exec();
            return NullType::getInstance();
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
            return returnValue->exec();
        }
    };
}

#endif //MATHPROJECT_AST_H
