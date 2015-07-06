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
        : Operation(operation), vast(vAst) {}
    };


}

#endif //MATHPROJECT_AST_H
