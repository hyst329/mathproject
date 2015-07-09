//
// Created by main on 05.07.2015.
//

#ifndef MATHPROJECT_AST_H
#define MATHPROJECT_AST_H
#include <vector>
#include <map>
#include "Type.h"
#include <map>
using namespace std;
namespace Interpreter {
    class Type;
    struct AST {
        virtual Type* exec() = 0;
        map<string,Type*> *variables;
    };
    struct TypeAST:public AST {
        Type *value;
        Type *exec() {
            return value;
        }
        TypeAST(Type *Value):value(Value){};
    };
    struct RealAST : public AST {
        double value;
        RealAST(double Value):value(Value){};
    };
    struct GlobalAST: public AST {
        AST *Operation;
        vector <AST> *vast;
        GlobalAST(AST *operation, vector <AST> *vAst)
            :Operation(operation), vast(vAst) {};
        //Type* exec() {
        //    return Operation(vast)->exec();
        //}
    };
    struct BinaryAST: public AST {
        AST *Operation;
        AST *left,*right;
        BinaryAST(AST *operation,AST *Left,AST *Right)
                :Operation(operation),left(Left),right(Right) {};
       // Type* exec() {
      //      return Operation(left,right)->exec();
        //}
    };
    struct UnaryAST: public AST {
        AST *Operation;
        AST *ast;
        UnaryAST(AST *operation,AST *Ast)
                :Operation(operation),ast(Ast){};
        //Type* exec() {
          //  return ;
        //}
    };
    struct VarAST : public AST {
        string Name;
        VarAST(string name)
                : Name(name) {};
        Type *exec(){
            return (*variables)[Name];
        }
    };
    struct ConditionalAST:public AST {
        AST *IfAST,*ThenAST,*ElseAST;
        ConditionalAST(AST *ifAST,AST *thenAST,AST *elseAST)
                :IfAST(ifAST),ThenAST(thenAST),ElseAST(elseAST) {};
        Type *exec() {
            if(IfAST->exec())
                return ThenAST->exec();
            else
                return ElseAST->exec();
        }
    };

    Type* getVariables(){
        return 0;
    }
}

#endif //MATHPROJECT_AST_H
