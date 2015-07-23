//
// Created by R2 on 10.07.2015.
//

#ifndef MATHPROJECT_ARRAY_H
#define MATHPROJECT_ARRAY_H

#include "Type.h"
#include <vector>


class Array : Type {

    std::vector<Type *> array;

public:
    int size() {
        return array.size();
    }

    Type *&operator[](int i) {
        return array[i];
    }

    void add(Type *element) {
        array.push_back(element);
    }

    Array(int n) {
        array = std::vector<Type *>(n);
    }

    Array(std::vector<Type *> &newArray) {
        array = newArray;
    }
};


#endif //MATHPROJECT_ARRAY_H
