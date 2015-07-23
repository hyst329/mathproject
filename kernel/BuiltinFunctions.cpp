//
// Created by main on 18.07.2015.
//

#include <iostream>
#include "BuiltinFunctions.h"
#include "Matrix.h"
#include "UserFunction.h"
#include "Error.h"
#include "Array.h"


void ::Kernel::initialiseBuiltins() {
    AST::functions["$operator+"] = new BuiltinFunction(add);
    AST::functions["$operator-"] = new BuiltinFunction(subtract);
    AST::functions["$operator*"] = new BuiltinFunction(multiply);
    AST::functions["$operator/"] = new BuiltinFunction(divide);
    AST::functions["print"] = new BuiltinFunction(print);
    AST::functions["$operator="] = new BuiltinFunction(assign);
    AST::functions["pvar"] = new BuiltinFunction(pvar);
    AST::functions["pfun"] = new BuiltinFunction(pfun);
    AST::functions["exit"] = new BuiltinFunction(exit);
    AST::functions["all"] = new BuiltinFunction(all);
    AST::functions["any"] = new BuiltinFunction(any);

    AST::functions["$operator.*"]=new BuiltinFunction(elemMulti);
    AST::functions["$operator^"]=new BuiltinFunction(exponentation);
    AST::functions["$operator.^"]=new BuiltinFunction(elemExp);
    AST::functions["$operator>"]=new BuiltinFunction(more);
    AST::functions["$operator>="]=new BuiltinFunction(moreOrEqual);
    AST::functions["$operator<"]=new BuiltinFunction(less);
    AST::functions["$operator<="]=new BuiltinFunction(lessOrEqual);
    AST::functions["$operator=="]=new BuiltinFunction(equal);
    AST::functions["$operator!="]=new BuiltinFunction(notEqual);
    AST::functions["getRows"]=new BuiltinFunction(getRows);
    AST::functions["getColumns"]=new BuiltinFunction(getColumns);
    AST::functions["getCountOfElements"]=new BuiltinFunction(getCountOfElements);
    AST::functions["getSize"]=new BuiltinFunction(getSize);
    AST::functions["newIndentityMatrix"]=new BuiltinFunction(newIndentityMatrix);
    AST::functions["getElement"]=new BuiltinFunction(getElement);
}

Type *::Kernel::add(std::vector<Type *> v) {
    switch (v.size()) {
        case 1:
            return v[0];
        case 2:
            if (dynamic_cast<Matrix *>(v[0]) and dynamic_cast<Matrix *>(v[1])) {
                Matrix m = (*((Matrix *) v[0]) + *((Matrix *) v[1]));
                Matrix *r = new Matrix(m);
                return r;
            }
            else {
                Error::error(ET_INCOMPATIBLE_TYPES, {v[0]->getType(), v[1]->getType()});
            }
        default:
            // TODO(hyst329): error
            return 0;
    }

    return nullptr;
}

Type *::Kernel::subtract(std::vector<Type *> v) {
    switch (v.size()) {
        case 1:
            return v[0]; // TODO(hyst329) : Negate
        case 2:
            if (dynamic_cast<Matrix *>(v[0]) and dynamic_cast<Matrix *>(v[1])) {
                Matrix m = (*((Matrix *) v[0]) - *((Matrix *) v[1]));
                Matrix *r = new Matrix(m);
                return r;
            }
            else {
                Error::error(ET_INCOMPATIBLE_TYPES, {v[0]->getType(), v[1]->getType()});
            }
        default:
            // TODO(hyst329): error
            return 0;
    }
}

Type *::Kernel::multiply(std::vector<Type *> v) {
    switch (v.size()) {
        case 2:
            if (dynamic_cast<Matrix *>(v[0]) and dynamic_cast<Matrix *>(v[1])) {
                Matrix m = (*((Matrix *) v[0]) * *((Matrix *) v[1]));
                Matrix *r = new Matrix(m);
                return r;
            }
            else {
                Error::error(ET_INCOMPATIBLE_TYPES, {v[0]->getType(), v[1]->getType()});
            }
        default:
            // TODO(hyst329): error
            return 0;
    }
}

Type *::Kernel::divide(std::vector<Type *> v) {
    // TODO: Multiply to inverse?
    switch (v.size()) {
        case 2:
            if (dynamic_cast<Matrix *>(v[0]) and dynamic_cast<Matrix *>(v[1])) {
                if (((Matrix *) v[1])->getRows() == 1 and ((Matrix *) v[1])->getColumns() == 1) {
                    Matrix g = *((Matrix *) v[1]);
                    g.element(1, 1) = 1.0 / g.element(1, 1);
                    Matrix m = *((Matrix *) v[0]) * g;
                    Matrix *r = new Matrix(m);
                    return r;
                }
            }
            else {
                Error::error(ET_INCOMPATIBLE_TYPES, {v[0]->getType(), v[1]->getType()});
            }
        default:
            // TODO(hyst329): error
            return 0;
    }
    return nullptr;
}

Type *::Kernel::print(std::vector<Type *> v) {
    for (Type *t: v) t->print(std::cout);
    return 0;
}

Type *::Kernel::assign(std::vector<Type *> v) {
    switch (v.size()) {
        case 2:
            v[0] = v[1];
            return v[1];
        default:
            // TODO(hyst329): error
            return NullType::getInstance();
    }
}

Type *::Kernel::pvar(std::vector<Type *> v) {
    for (auto p: AST::variables) {
        cout << (p.second ? (boost::format("%1%\t:\t[%3$20s at addr. %2$9d] %4%") % p.first % (int) p.second
                             % p.second->getType() % (*p.second))
                          : (boost::format("%1%\t:\t[******************** at addr. %2$9d] ZERO POINTER")
                             % p.first % p.second))
        << endl;
    }
    return NullType::getInstance();
}


Type *::Kernel::pfun(std::vector<Type *> v) {
    for (auto p: AST::functions) {
        cout <<
        boost::format("%1% (%2%)\t at addr. %3$9d") % p.first % (dynamic_cast<UserFunction *>(p.second) ? "user" :
                                                                 "built-in") % (int) p.second << endl;
    }
    return NullType::getInstance();
}

Type *::Kernel::exit(std::vector<Type *> v) {
    ::exit(1);
    return 0;
}

Type *::Kernel::all(std::vector<Type *> v) {
    bool r = 1;
    for (Type *x: v) r = r && x->isNonzero();
    return new Matrix(double(r));
}

Type *::Kernel::any(std::vector<Type *> v) {
    bool r = 0;
    for (Type *x: v) r = r || x->isNonzero();
    return new Matrix(double(r));
}

Type *::Kernel::elemMulti(std::vector<Type *> v) {
    switch (v.size()) {
        case 2:
            if (dynamic_cast<Matrix *>(v[0]) and dynamic_cast<Matrix *>(v[1])) {
                Matrix m = ((Matrix *) v[0])->elemMulti(*((Matrix *) v[1]));
                Matrix *r = new Matrix(m);
                return r;
            }
            else {
                Error::error(ET_INCOMPATIBLE_TYPES, {v[0]->getType(), v[1]->getType()});
            }
        default:
            // TODO(hyst329): error
            return 0;
    }
}

Type *::Kernel::elemExp(std::vector<Type *> v) {
    switch (v.size()) {
        case 2:
            if (dynamic_cast<Matrix *>(v[0]) and dynamic_cast<Matrix *>(v[1])) {
                Matrix m = ((Matrix *) v[0])->elemExp(*((Matrix *) v[1]));
                Matrix *r = new Matrix(m);
                return r;
            }
            else {
                Error::error(ET_INCOMPATIBLE_TYPES, {v[0]->getType(), v[1]->getType()});
            }
        default:
            // TODO(hyst329): error
            return 0;
    }
}

Type *::Kernel::exponentation(std::vector<Type *> v) {
    switch (v.size()) {
        case 2:
            if (dynamic_cast<Matrix *>(v[0]) and dynamic_cast<Matrix *>(v[1])) {
                Matrix m = *((Matrix *) v[0])^(*((Matrix *) v[1]));
                Matrix *r = new Matrix(m);
                return r;
            }
            else {
                Error::error(ET_INCOMPATIBLE_TYPES, {v[0]->getType(), v[1]->getType()});
            }
        default:
            // TODO(hyst329): error
            return 0;
    }
}
Type *::Kernel::more(std::vector<Type *> v) {
    switch (v.size()) {
        case 2:
            if (dynamic_cast<Matrix *>(v[0]) and dynamic_cast<Matrix *>(v[1])) {
                Matrix m = *((Matrix *) v[0])>(*((Matrix *) v[1]));
                Matrix *r = new Matrix(m);
                return r;
            }
            else {
                Error::error(ET_INCOMPATIBLE_TYPES, {v[0]->getType(), v[1]->getType()});
            }
        default:
            // TODO(hyst329): error
            return 0;
    }
}

Type *::Kernel::moreOrEqual(std::vector<Type *> v) {
    switch (v.size()) {
        case 2:
            if (dynamic_cast<Matrix *>(v[0]) and dynamic_cast<Matrix *>(v[1])) {
                Matrix m = *((Matrix *) v[0])>=(*((Matrix *) v[1]));
                Matrix *r = new Matrix(m);
                return r;
            }
            else {
                Error::error(ET_INCOMPATIBLE_TYPES, {v[0]->getType(), v[1]->getType()});
            }
        default:
            // TODO(hyst329): error
            return 0;
    }
}

Type *::Kernel::less(std::vector<Type *> v) {
    switch (v.size()) {
        case 2:
            if (dynamic_cast<Matrix *>(v[0]) and dynamic_cast<Matrix *>(v[1])) {
                Matrix m = *((Matrix *) v[0])<(*((Matrix *) v[1]));
                Matrix *r = new Matrix(m);
                return r;
            }
            else {
                Error::error(ET_INCOMPATIBLE_TYPES, {v[0]->getType(), v[1]->getType()});
            }
        default:
            // TODO(hyst329): error
            return 0;
    }
}

Type *::Kernel::lessOrEqual(std::vector<Type *> v) {
    switch (v.size()) {
        case 2:
            if (dynamic_cast<Matrix *>(v[0]) and dynamic_cast<Matrix *>(v[1])) {
                Matrix m = *((Matrix *) v[0])<=(*((Matrix *) v[1]));
                Matrix *r = new Matrix(m);
                return r;
            }
            else {
                Error::error(ET_INCOMPATIBLE_TYPES, {v[0]->getType(), v[1]->getType()});
            }
        default:
            // TODO(hyst329): error
            return 0;
    }
}

Type *::Kernel::equal(std::vector<Type *> v) {
    switch (v.size()) {
        case 2:
            if (dynamic_cast<Matrix *>(v[0]) and dynamic_cast<Matrix *>(v[1])) {
                Matrix m = *((Matrix *) v[0])==(*((Matrix *) v[1]));
                Matrix *r = new Matrix(m);
                return r;
            }
            else {
                Error::error(ET_INCOMPATIBLE_TYPES, {v[0]->getType(), v[1]->getType()});
            }
        default:
            // TODO(hyst329): error
            return 0;
    }
}

Type *::Kernel::notEqual(std::vector<Type *> v) {
    switch (v.size()) {
        case 2:
            if (dynamic_cast<Matrix *>(v[0]) and dynamic_cast<Matrix *>(v[1])) {
                Matrix m = *((Matrix *) v[0])!=(*((Matrix *) v[1]));
                Matrix *r = new Matrix(m);
                return r;
            }
            else {
                Error::error(ET_INCOMPATIBLE_TYPES, {v[0]->getType(), v[1]->getType()});
            }
        default:
            // TODO(hyst329): error
            return 0;
    }
}

Type *::Kernel::getRows(std::vector<Type *> v) {
    switch (v.size()) {
        case 1:
            if (dynamic_cast<Matrix *>(v[0])) {
                Matrix m = *((Matrix *) v[0]);
                Matrix *r = new Matrix(m.getRows());
                return r;
            }
            else {
                Error::error(ET_INCOMPATIBLE_TYPES, {v[0]->getType(), v[1]->getType()});
            }
        default:
            // TODO(hyst329): error
            return 0;
    }
}

Type *::Kernel::getColumns(std::vector<Type *> v) {
    switch (v.size()) {
        case 1:
            if (dynamic_cast<Matrix *>(v[0])) {
                Matrix m = *((Matrix *) v[0]);
                Matrix *r = new Matrix(m.getColumns());
                return r;
            }
            else {
                Error::error(ET_INCOMPATIBLE_TYPES, {v[0]->getType(), v[1]->getType()});
            }
        default:
            // TODO(hyst329): error
            return 0;
    }
}

Type *::Kernel::getCountOfElements(std::vector<Type *> v) {
    switch (v.size()) {
        case 1:
            if (dynamic_cast<Matrix *>(v[0])) {
                Matrix m = *((Matrix *) v[0]);
                Matrix *r = new Matrix(m.getColumns()*m.getRows());
                return r;
            }
            else {
                Error::error(ET_INCOMPATIBLE_TYPES, {v[0]->getType(), v[1]->getType()});
            }
        default:
            // TODO(hyst329): error
            return 0;
    }
}

Type *::Kernel::getSize(std::vector<Type *> v) {
    switch (v.size()) {
        case 1:
            if (dynamic_cast<Matrix *>(v[0])) {
                Matrix m = *((Matrix *) v[0]);
                Matrix *r = new Matrix(*(new vector<vector<double>>({{(double)m.getRows()},{(double)m.getColumns()}})));
                return r;
            }
            if (dynamic_cast<Array *>(v[0])) {
                return new Matrix(((Array *)v[0])->size());
            }
            else {
                Error::error(ET_INCOMPATIBLE_TYPES, {v[0]->getType(), v[1]->getType()});
            }
        default:
            // TODO(hyst329): error
            return 0;
    }
}

Type *::Kernel::newIndentityMatrix(std::vector<Type *> v) {
    switch (v.size()) {
        case 1:
            if (dynamic_cast<Matrix *>(v[0])) {
                Matrix *r = new Matrix(Matrix(0).newIndentityMatrix(*(Matrix *)v[0]));
                return r;
            }
            else {
                Error::error(ET_INCOMPATIBLE_TYPES, {v[0]->getType(), v[1]->getType()});
            }
        default:
            // TODO(hyst329): error
            return 0;
    }
}
Type *::Kernel::getElement(std::vector<Type *> v) {
    switch(v.size()) {
        case 3:
            if (dynamic_cast<Matrix *>(v[0])&& dynamic_cast<Matrix *>(v[1])&&dynamic_cast<Matrix *>(v[2])) {
                Matrix m = *((Matrix *) v[0]);
                Matrix i = *((Matrix *) v[1]);
                Matrix j= *((Matrix *) v[2]);
                Matrix *r =new Matrix(m.getElement(i,j));
                return r;
            }
            else {
                Error::error(ET_INCOMPATIBLE_TYPES, {v[0]->getType(), v[1]->getType(), v[2]->getType()});
            }
        case 2:
            if (dynamic_cast<Matrix *>(v[0])&& dynamic_cast<Matrix *>(v[1])) {
                Matrix m = *((Matrix *) v[0]);
                Matrix i = *((Matrix *) v[1]);
                Matrix *r =new Matrix(m.getElement(i));
                return r;
            }
            else {
                Error::error(ET_INCOMPATIBLE_TYPES, {v[0]->getType(), v[1]->getType()});
            }
        default:
            // TODO(hyst329): error
            return 0;
    }
}