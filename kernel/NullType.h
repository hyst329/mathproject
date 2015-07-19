//
// Created by main on 19.07.2015.
//

#ifndef MATHPROJECT_NULLTYPE_H
#define MATHPROJECT_NULLTYPE_H


#include "Type.h"

class NullType : public Type {

public:
    virtual std::string getType();

    virtual bool equals(Type &type);

    virtual bool isNonzero();
};


#endif //MATHPROJECT_NULLTYPE_H
