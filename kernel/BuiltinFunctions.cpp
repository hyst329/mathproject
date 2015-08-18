//
// Created by main on 18.07.2015.
//

#include <iostream>
#include "BuiltinFunctions.h"
#include "Matrix.h"
#include "Function.h"
#include "Error.h"
#include "Array.h"
#include "ReferenceType.h"


void ::Kernel::initialiseBuiltins() {
    AST::functions["$operator+"] = new BuiltinFunction(add);
    AST::functions["$operator-"] = new BuiltinFunction(subtract);
    AST::functions["$operator*"] = new BuiltinFunction(multiply);
    AST::functions["$operator/"] = new BuiltinFunction(divide);
    AST::functions["print"] = new BuiltinFunction(print);
    AST::functions["$operator="] = new BuiltinFunction(assign, {1});
    AST::functions["pvar"] = new BuiltinFunction(pvar);
    AST::functions["pfun"] = new BuiltinFunction(pfun);
    AST::functions["exit"] = new BuiltinFunction(exit);
    AST::functions["all"] = new BuiltinFunction(all);
    AST::functions["any"] = new BuiltinFunction(any);

    AST::functions["$operator.*"] = new BuiltinFunction(elemMulti);
    AST::functions["$operator^"] = new BuiltinFunction(exponentation);
    AST::functions["$operator.^"] = new BuiltinFunction(elemExp);
    AST::functions["$operator>"] = new BuiltinFunction(more);
    AST::functions["$operator>="] = new BuiltinFunction(moreOrEqual);
    AST::functions["$operator<"] = new BuiltinFunction(less);
    AST::functions["$operator<="] = new BuiltinFunction(lessOrEqual);
    AST::functions["$operator=="] = new BuiltinFunction(equal);
    AST::functions["$operator!="] = new BuiltinFunction(notEqual);
    AST::functions["$index"] = new BuiltinFunction(index);
    AST::functions["rows"] = new BuiltinFunction(getRows);
    AST::functions["columns"] = new BuiltinFunction(getColumns);
    AST::functions["elements"] = new BuiltinFunction(getCountOfElements);
    AST::functions["size"] = new BuiltinFunction(getSize);
    AST::functions["identity"] = new BuiltinFunction(newIdentityMatrix);

    AST::functions["sin"] = new BuiltinFunction(sin);
    AST::functions["cos"] = new BuiltinFunction(cos);
    AST::functions["tan"] = new BuiltinFunction(tan);
    AST::functions["cotan"] = new BuiltinFunction(cotan);
    AST::functions["tg"] = new BuiltinFunction(tan);
    AST::functions["ctg"] = new BuiltinFunction(cotan);

    AST::functions["arcsin"] = new BuiltinFunction(asin);
    AST::functions["arccos"] = new BuiltinFunction(acos);
    AST::functions["arctan"] = new BuiltinFunction(atan);
    AST::functions["arccotan"] = new BuiltinFunction(acotan);
    AST::functions["arctg"] = new BuiltinFunction(atan);
    AST::functions["arcctg"] = new BuiltinFunction(acotan);

    AST::functions["sinh"] = new BuiltinFunction(sinh);
    AST::functions["cosh"] = new BuiltinFunction(cosh);
    AST::functions["tanh"] = new BuiltinFunction(tanh);
    AST::functions["cotanh"] = new BuiltinFunction(cotanh);
    AST::functions["tgh"] = new BuiltinFunction(tanh);
    AST::functions["ctgh"] = new BuiltinFunction(cotanh);

    AST::functions["lg"] = new BuiltinFunction(lg);
    AST::functions["ln"] = new BuiltinFunction(ln);
    AST::functions["log"] = new BuiltinFunction(log);
    AST::functions["exp"] = new BuiltinFunction(exp);
}

Type *::Kernel::add(QList<Type *> v) {
    switch (v.size()) {
    case 1:
        return v[0];
    case 2:
        if (dynamic_cast<Matrix *>(v[0])and dynamic_cast<Matrix *>(v[1])) {
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

Type *::Kernel::subtract(QList<Type *> v) {
    switch (v.size()) {
    case 1:
        return v[0]; // TODO(hyst329) : Negate
    case 2:
        if (dynamic_cast<Matrix *>(v[0])and dynamic_cast<Matrix *>(v[1])) {
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

Type *::Kernel::multiply(QList<Type *> v) {
    switch (v.size()) {
    case 2:
        if (dynamic_cast<Matrix *>(v[0])and dynamic_cast<Matrix *>(v[1])) {
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

Type *::Kernel::divide(QList<Type *> v) {
    // TODO: Multiply to inverse?
    switch (v.size()) {
    case 2:
        if (dynamic_cast<Matrix *>(v[0])and dynamic_cast<Matrix *>(v[1])) {
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

Type *::Kernel::print(QList<Type *> v) {
    static QTextStream str(stdout);
    for (Type *t: v) {
        t->print(str);
        str << endl;
    }
    return NullType::getInstance();
}

Type *::Kernel::assign(QList<Type *> v) {
    ReferenceType *ref;
    switch (v.size()) {
    case 2:
        if(!dynamic_cast<ReferenceType *>(v[0])) {
            return NullType::getInstance();
        }
        ref = (ReferenceType *)v[0];
        if(dynamic_cast<VariableReferenceType *>(ref) /*&& !ref->reference()*/) {
            AST::variables[((VariableReferenceType *)ref)->variable()] = v[1];
        }
        //qDebug("Reference: %d(ref=%d) %d", v[0], ref, v[1]);
        *(ref->reference()) = *v[1];
        return v[1];
    default:
        // TODO(hyst329): error
        return NullType::getInstance();
    }
}

Type *::Kernel::pvar(QList<Type *> v) {
    static QTextStream s(stdout);
    for (auto p = AST::variables.begin(); p != AST::variables.end(); ++p) {

        s << (p.value() ? (QString("%1\t:\t[%3 at addr. %2] %4").arg(p.key())
                           .arg((int) p.value())
                           .arg(p.value()->getType()).arg(p.value()->toString()))
              : (QString("%1\t:\t[******************** at addr. %2] ZERO POINTER")
                 .arg(p.key()).arg((int) p.value())));
        endl(s);
    }
    return NullType::getInstance();
}


Type *::Kernel::pfun(QList<Type *> v) {
    static QTextStream s(stdout);
    for (auto p = AST::functions.begin(); p != AST::functions.end(); ++p) {
        s <<
                QString("%1 (%2)\t at addr. %3").arg(p.key()).arg(dynamic_cast<UserFunction *>(p.value()) ? "user" :
                                                                  "built-in").arg((int) p.value());
        endl(s);

    }
    return NullType::getInstance();
}

Type *::Kernel::exit(QList<Type *> v) {
    int code = 1;
    if(!v.empty())
        if(dynamic_cast<Matrix*>(v[0]))
            code = ((Matrix*)v[0])->element(1, 1);
    ::exit(code);
    return 0;
}

Type *::Kernel::all(QList<Type *> v) {
    bool r = 1;
    for (Type *x: v) r = r && x->isNonzero();
    return new Matrix(double(r));
}

Type *::Kernel::any(QList<Type *> v) {
    bool r = 0;
    for (Type *x: v) r = r || x->isNonzero();
    return new Matrix(double(r));
}

Type *::Kernel::elemMulti(QList<Type *> v) {
    switch (v.size()) {
    case 2:
        if (dynamic_cast<Matrix *>(v[0])and dynamic_cast<Matrix *>(v[1])) {
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

Type *::Kernel::elemExp(QList<Type *> v) {
    switch (v.size()) {
    case 2:
        if (dynamic_cast<Matrix *>(v[0])and dynamic_cast<Matrix *>(v[1])) {
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

Type *::Kernel::exponentation(QList<Type *> v) {
    switch (v.size()) {
    case 2:
        if (dynamic_cast<Matrix *>(v[0])and dynamic_cast<Matrix *>(v[1])) {
            Matrix m = *((Matrix *) v[0]) ^(*((Matrix *) v[1]));
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

Type *::Kernel::more(QList<Type *> v) {
    switch (v.size()) {
    case 2:
        if (dynamic_cast<Matrix *>(v[0])and dynamic_cast<Matrix *>(v[1])) {
            Matrix m = *((Matrix *) v[0]) > (*((Matrix *) v[1]));
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

Type *::Kernel::moreOrEqual(QList<Type *> v) {
    switch (v.size()) {
    case 2:
        if (dynamic_cast<Matrix *>(v[0])and dynamic_cast<Matrix *>(v[1])) {
            Matrix m = *((Matrix *) v[0]) >= (*((Matrix *) v[1]));
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

Type *::Kernel::less(QList<Type *> v) {
    switch (v.size()) {
    case 2:
        if (dynamic_cast<Matrix *>(v[0])and dynamic_cast<Matrix *>(v[1])) {
            Matrix m = *((Matrix *) v[0]) < (*((Matrix *) v[1]));
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

Type *::Kernel::lessOrEqual(QList<Type *> v) {
    switch (v.size()) {
    case 2:
        if (dynamic_cast<Matrix *>(v[0])and dynamic_cast<Matrix *>(v[1])) {
            Matrix m = *((Matrix *) v[0]) <= (*((Matrix *) v[1]));
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

Type *::Kernel::equal(QList<Type *> v) {
    switch (v.size()) {
    case 2:
        if (dynamic_cast<Matrix *>(v[0])and dynamic_cast<Matrix *>(v[1])) {
            Matrix m = *((Matrix *) v[0]) == (*((Matrix *) v[1]));
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

Type *::Kernel::notEqual(QList<Type *> v) {
    switch (v.size()) {
    case 2:
        if (dynamic_cast<Matrix *>(v[0])and dynamic_cast<Matrix *>(v[1])) {
            Matrix m = *((Matrix *) v[0]) != (*((Matrix *) v[1]));
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


Type *::Kernel::index(QList<Type *> v) {
    switch (v.size()) {
    case 1:
    // TODO: Error
    case 2:
    // TODO: Index of an array
    case 3:
        if (dynamic_cast<Matrix *>(v[0])and dynamic_cast<Matrix *>(v[1])and dynamic_cast<Matrix *>(v[2]))
            return new Matrix(
                    ((Matrix *) v[0])->element((int) ((Matrix *) v[1])->element(1, 1),
                                               (int) ((Matrix *) v[2])->element(1, 1)));
    default:
        break;
    }
}

Type *::Kernel::getRows(QList<Type *> v) {
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

Type *::Kernel::getColumns(QList<Type *> v) {
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

Type *::Kernel::getCountOfElements(QList<Type *> v) {
    switch (v.size()) {
    case 1:
        if (dynamic_cast<Matrix *>(v[0])) {
            Matrix m = *((Matrix *) v[0]);
            Matrix *r = new Matrix(m.getColumns() * m.getRows());
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

Type *::Kernel::getSize(QList<Type *> v) {
    switch (v.size()) {
    case 1:
        if (dynamic_cast<Matrix *>(v[0])) {
            Matrix m = *((Matrix *) v[0]);
            Matrix *r = new Matrix(*(new QList<QList<double> >({{(double) m.getRows()},
                                                                {(double) m.getColumns()}})));
            return r;
        }
        if (dynamic_cast<Array *>(v[0])) {
            return new Matrix(((Array *) v[0])->size());
        }
        else {
            Error::error(ET_INCOMPATIBLE_TYPES, {v[0]->getType(), v[1]->getType()});
        }
    default:
        // TODO(hyst329): error
        return 0;
    }
}

Type *::Kernel::newIdentityMatrix(QList<Type *> v) {
    switch (v.size()) {
    case 1:
        if (dynamic_cast<Matrix *>(v[0])) {
            Matrix *r = new Matrix(Matrix::newIdentityMatrix((int) ((Matrix *) v[0])->element(1, 1)));
            return r;
        }
        else {
            //Error::error(ET_INCOMPATIBLE_TYPES, {v[0]->getType(), v[1]->getType()});
        }
    default:
        // TODO(hyst329): error
        return 0;
    }
}

Type *::Kernel::sin(QList<Type *> v) {
    switch (v.size()) {
    case 1:
        if (dynamic_cast<Matrix *>(v[0])) {
            Matrix m = *((Matrix *) v[0]);
            Matrix *r = new Matrix(m.sin());
            return r;
        }
        else {
            //Error::error(ET_INCOMPATIBLE_TYPES, {v[0]->getType(), v[1]->getType()});
        }
    default:
        // TODO(hyst329): error
        return 0;
    }
}

Type *::Kernel::cos(QList<Type *> v) {
    switch (v.size()) {
    case 1:
        if (dynamic_cast<Matrix *>(v[0])) {
            Matrix m = *((Matrix *) v[0]);
            Matrix *r = new Matrix(m.cos());
            return r;
        }
        else {
            //Error::error(ET_INCOMPATIBLE_TYPES, {v[0]->getType(), v[1]->getType()});
        }
    default:
        // TODO(hyst329): error
        return 0;
    }
}

Type *::Kernel::tan(QList<Type *> v) {
    switch (v.size()) {
    case 1:
        if (dynamic_cast<Matrix *>(v[0])) {
            Matrix m = *((Matrix *) v[0]);
            Matrix *r = new Matrix(m.tan());
            return r;
        }
        else {
            //Error::error(ET_INCOMPATIBLE_TYPES, {v[0]->getType(), v[1]->getType()});
        }
    default:
        // TODO(hyst329): error
        return 0;
    }
}

Type *::Kernel::cotan(QList<Type *> v) {
    switch (v.size()) {
    case 1:
        if (dynamic_cast<Matrix *>(v[0])) {
            Matrix m = *((Matrix *) v[0]);
            Matrix *r = new Matrix(m.cotan());
            return r;
        }
        else {
            //Error::error(ET_INCOMPATIBLE_TYPES, {v[0]->getType(), v[1]->getType()});
        }
    default:
        // TODO(hyst329): error
        return 0;
    }
}

Type *::Kernel::asin(QList<Type *> v) {
    switch (v.size()) {
    case 1:
        if (dynamic_cast<Matrix *>(v[0])) {
            Matrix m = *((Matrix *) v[0]);
            Matrix *r = new Matrix(m.asin());
            return r;
        }
        else {
            //Error::error(ET_INCOMPATIBLE_TYPES, {v[0]->getType(), v[1]->getType()});
        }
    default:
        // TODO(hyst329): error
        return 0;
    }
}

Type *::Kernel::acos(QList<Type *> v) {
    switch (v.size()) {
    case 1:
        if (dynamic_cast<Matrix *>(v[0])) {
            Matrix m = *((Matrix *) v[0]);
            Matrix *r = new Matrix(m.acos());
            return r;
        }
        else {
            //Error::error(ET_INCOMPATIBLE_TYPES, {v[0]->getType(), v[1]->getType()});
        }
    default:
        // TODO(hyst329): error
        return 0;
    }
}

Type *::Kernel::atan(QList<Type *> v) {
    switch (v.size()) {
    case 1:
        if (dynamic_cast<Matrix *>(v[0])) {
            Matrix m = *((Matrix *) v[0]);
            Matrix *r = new Matrix(m.atan());
            return r;
        }
        else {
            //Error::error(ET_INCOMPATIBLE_TYPES, {v[0]->getType(), v[1]->getType()});
        }
    default:
        // TODO(hyst329): error
        return 0;
    }
}

Type *::Kernel::acotan(QList<Type *> v) {
    switch (v.size()) {
    case 1:
        if (dynamic_cast<Matrix *>(v[0])) {
            Matrix m = *((Matrix *) v[0]);
            Matrix *r = new Matrix(m.acotan());
            return r;
        }
        else {
            //Error::error(ET_INCOMPATIBLE_TYPES, {v[0]->getType(), v[1]->getType()});
        }
    default:
        // TODO(hyst329): error
        return 0;
    }
}

Type *::Kernel::sinh(QList<Type *> v) {
    switch (v.size()) {
    case 1:
        if (dynamic_cast<Matrix *>(v[0])) {
            Matrix m = *((Matrix *) v[0]);
            Matrix *r = new Matrix(m.sinh());
            return r;
        }
        else {
            //Error::error(ET_INCOMPATIBLE_TYPES, {v[0]->getType(), v[1]->getType()});
        }
    default:
        // TODO(hyst329): error
        return 0;
    }
}

Type *::Kernel::cosh(QList<Type *> v) {
    switch (v.size()) {
    case 1:
        if (dynamic_cast<Matrix *>(v[0])) {
            Matrix m = *((Matrix *) v[0]);
            Matrix *r = new Matrix(m.cosh());
            return r;
        }
        else {
            //Error::error(ET_INCOMPATIBLE_TYPES, {v[0]->getType(), v[1]->getType()});
        }
    default:
        // TODO(hyst329): error
        return 0;
    }
}

Type *::Kernel::tanh(QList<Type *> v) {
    switch (v.size()) {
    case 1:
        if (dynamic_cast<Matrix *>(v[0])) {
            Matrix m = *((Matrix *) v[0]);
            Matrix *r = new Matrix(m.tanh());
            return r;
        }
        else {
            //Error::error(ET_INCOMPATIBLE_TYPES, {v[0]->getType(), v[1]->getType()});
        }
    default:
        // TODO(hyst329): error
        return 0;
    }
}

Type *::Kernel::cotanh(QList<Type *> v) {
    switch (v.size()) {
    case 1:
        if (dynamic_cast<Matrix *>(v[0])) {
            Matrix m = *((Matrix *) v[0]);
            Matrix *r = new Matrix(m.cotanh());
            return r;
        }
        else {
            //Error::error(ET_INCOMPATIBLE_TYPES, {v[0]->getType(), v[1]->getType()});
        }
    default:
        // TODO(hyst329): error
        return 0;
    }
}

Type *::Kernel::lg(QList<Type *> v) {
    switch (v.size()) {
    case 1:
        if (dynamic_cast<Matrix *>(v[0])) {
            Matrix m = *((Matrix *) v[0]);
            Matrix *r = new Matrix(m.lg());
            return r;
        }
        else {
            //Error::error(ET_INCOMPATIBLE_TYPES, {v[0]->getType(), v[1]->getType()});
        }
    default:
        // TODO(hyst329): error
        return 0;
    }
}

Type *::Kernel::ln(QList<Type *> v) {
    switch (v.size()) {
    case 1:
        if (dynamic_cast<Matrix *>(v[0])) {
            Matrix m = *((Matrix *) v[0]);
            Matrix *r = new Matrix(m.ln());
            return r;
        }
        else {
            //Error::error(ET_INCOMPATIBLE_TYPES, {v[0]->getType(), v[1]->getType()});
        }
    default:
        // TODO(hyst329): error
        return 0;
    }
}

Type *::Kernel::exp(QList<Type *> v) {
    switch (v.size()) {
    case 1:
        if (dynamic_cast<Matrix *>(v[0])) {
            Matrix m = *((Matrix *) v[0]);
            Matrix *r = new Matrix(m.exp());
            return r;
        }
        else {
            //Error::error(ET_INCOMPATIBLE_TYPES, {v[0]->getType(), v[1]->getType()});
        }
    default:
        // TODO(hyst329): error
        return 0;
    }
}

Type *::Kernel::log(QList<Type *> v) {
    switch (v.size()) {
    case 1:
        return ln(v);
    case 2:
        if (dynamic_cast<Matrix *>(v[0])and dynamic_cast<Matrix *>(v[1])) {
            Matrix m = (*((Matrix *) v[0])).log((*((Matrix *) v[1])));
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
