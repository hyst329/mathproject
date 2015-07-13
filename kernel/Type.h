//
// Created by R2 on 06.07.2015.
//

#ifndef MATHPROJECT_TYPE_H
#define MATHPROJECT_TYPE_H

#include <string>

class Type {
public:
    virtual std::string getType() = 0;

    virtual bool equals(Type &type) = 0;

    virtual bool isNonzero() = 0;
};


#endif //MATHPROJECT_TYPE_H
