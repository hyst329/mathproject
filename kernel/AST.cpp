//
// Created by main on 05.07.2015.
//

#include <iostream>
#include "AST.h"
#include "Function.h"
#include "Error.h"
#include "ReferenceType.h"
#include <QtDebug>


namespace Kernel {
QMap<QString, Function *> AST::functions = QMap<QString, Function *>();
QMap<QString, Type *> AST::variables = QMap<QString, Type *>();
QStack<QString> AST::callstack = QStack<QString>();
QStack<QMap<QString, Type *>> AST::locals = QStack<QMap<QString, Type *>>();

QList<Type *> vAstToType(QList<AST *>, QList<int>);

ReferenceType *createReference(AST *arg)
{
    if(dynamic_cast<VarAST*>(arg)) {
        //TODO: Function references
        return new VariableReferenceType(((VarAST*)arg)->name);
    }
    if(dynamic_cast<FunctionAST*>(arg)) {
        FunctionAST *farg = (FunctionAST*)arg;
        if(farg->function == "$index") {
            VariableReferenceType *rfarg = (VariableReferenceType*)createReference(farg->arguments[0]);
            return new IndexReferenceType(rfarg->variable(),
                    vAstToType(farg->arguments.mid(1), {}));
        }
    }
    Error::warning(WT_INVALID_REFERENCE);
    return 0;
}

QList<Type *> vAstToType(QList<AST *> initial, QList<int> referenceVars) {
    QList<Type *> final;
    for (int i = 0; i < initial.size(); i++) {
        final << (referenceVars.contains(i + 1) ? createReference(initial[i]) : initial[i]->exec());
    }
    return final;
}

Type *BlockAST::exec() {
    for (AST *a: children) {
        auto r = a->exec();
        if (dynamic_cast<ReturnAST *>(a))
            return r;
    }
    return NullType::getInstance();
}

Type *FunctionAST::exec() {
    if (!functions.contains(function))
        Error::error(ET_UNKNOWN_FUNCTION, {function});
    bool toplevel = callstack.empty();
    callstack.push(function);
    // Push the locals
    QMap<QString, Type *> loc;
    for(QString var : variables.keys())
        if(var[0] != QLatin1Char('$')) loc.insert(var, variables[var]);
    locals.push(loc);
    Type *r = functions[function]->operator()(vAstToType(arguments, functions[function]->getReferenceVars()));
    // Pop the locals, restoring variables' values
    loc = locals.top();
    for(QString var : loc.keys())
        variables[var] = loc[var];
    callstack.pop();
    return r;
}

Type *FunctionBodyAST::exec() {
    return NullType::getInstance();
    //return function->operator()(QList<Type *>());
}
}
