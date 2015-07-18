//
// Created by main on 18.07.2015.
//

#include <iostream>
#include "BuiltinFunctions.h"
#include "Matrix.h"
#include "UserFunction.h"

void ::Kernel::initialiseBuiltins() {
    AST::functions["$operator+"] = new BuiltinFunction(add);
    AST::functions["$operator-"] = new BuiltinFunction(subtract);
    AST::functions["$operator*"] = new BuiltinFunction(multiply);
    AST::functions["$operator/"] = new BuiltinFunction(divide);
}

Type *::Kernel::add(std::vector<Type *> v) {
    switch(v.size()) {
        case 1:
            return v[0];
        case 2:
            if(typeid(v[0]) == typeid(Matrix*) and typeid(v[1]) == typeid(Matrix*)) {
                Matrix m = (*((Matrix *) v[0]) + *((Matrix *) v[1]));
                Matrix *r = new Matrix(m);
                return r;
            }
            else {
                // TODO(hyst329): error
            }
        default:
            // TODO(hyst329): error
            return 0;
    }

    return nullptr;
}

Type *::Kernel::subtract(std::vector<Type *> v) {
    switch(v.size()) {
        case 1:
            return v[0]; // TODO(hyst329) : Negate
        case 2:
            if(typeid(v[0]) == typeid(Matrix*) and typeid(v[1]) == typeid(Matrix*)) {
                Matrix m = (*((Matrix *) v[0]) - *((Matrix *) v[1]));
                Matrix *r = new Matrix(m);
                return r;
            }
            else {
                // TODO(hyst329): error
            }
        default:
            // TODO(hyst329): error
            return 0;
    }
}

Type *::Kernel::multiply(std::vector<Type *> v) {
    switch(v.size()) {
        case 2:
            if(typeid(v[0]) == typeid(Matrix*) and typeid(v[1]) == typeid(Matrix*)) {
                Matrix m = (*((Matrix *) v[0]) * *((Matrix *) v[1]));
                Matrix *r = new Matrix(m);
                return r;
            }
            else {
                // TODO(hyst329): error
            }
        default:
            // TODO(hyst329): error
            return 0;
    }
}

Type *::Kernel::divide(std::vector<Type *> v) {
    return nullptr;
}

Type *::Kernel::print(std::vector<Type *> v) {
    for (Type *t: v) std::cout << *t;
    return 0;
}
