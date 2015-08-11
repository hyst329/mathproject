//
// Created by main on 19.07.2015.
//

#ifndef MATHPROJECT_NULLTYPE_H
#define MATHPROJECT_NULLTYPE_H


#include "Type.h"

class NullType : public Type {

    static NullType *instance;
public:
    static NullType *getInstance() {
        return instance;
    }

    virtual QString getType();

    virtual bool equals(Type &type);

    virtual bool isNonzero();


};


#endif //MATHPROJECT_NULLTYPE_H
