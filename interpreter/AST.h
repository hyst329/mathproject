//
// Created by main on 05.07.2015.
//

#ifndef MATHPROJECT_AST_H
#define MATHPROJECT_AST_H
#include <string>
#include <vector>
using namespace std;
namespace Interpreter {

    struct AST {
        virtual void exec() = 0;
    };

    struct RealAST : public AST {
        double value;
        RealAST(double Value):value(Value){};
    };
    struct GlobalAST: public AST {
    private:
        string Operation;
        vector <AST> *vast;
    public:
        GlobalAST(string operation, vector <AST> *vAst)
            :Operation(operation), vast(vAst) {}
    };
    class BinaryAST: public AST {
        string Operation;
        AST *left,*right;
    public:
        BinaryAST(string operation,AST *Left,AST *Right)
                :Operation(operation),left(Left),right(Right){};
    };
    class UnaryAST: public AST {
        string Operation;
        AST *ast;
    public:
        UnaryAST(string operation,AST *Ast)
                :Operation(operation),ast(Ast){};
    };
    class VariableAST : public AST {
        string Name;

    public:
        VariableAST(string name)
                : Name(name) {}
    };
    class ConditionalAST:public AST {
        string Operation;
        AST *IfAST,*ThenAST,*ElseAST;
    public:
        ConditionalAST(string operation,AST *ifAST,AST *thenAST,AST *elseAST)
                :Operation(operation),IfAST(ifAST),ThenAST(thenAST),ElseAST(elseAST){};
    };

}

#endif //MATHPROJECT_AST_H
