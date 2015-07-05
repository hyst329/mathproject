//
// Created by main on 05.07.2015.
//

#ifndef MATHPROJECT_AST_H
#define MATHPROJECT_AST_H

namespace Interpreter {
    struct AST {
        virtual void exec() = 0;
    };

    struct RealAST : public AST {
        double value;
    };
}

#endif //MATHPROJECT_AST_H
