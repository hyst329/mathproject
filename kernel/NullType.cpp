//
// Created by main on 19.07.2015.
//

#include "NullType.h"

std::string NullType::getType() {
    return "NullType";
}

bool NullType::equals(Type &type) {
    return 0;
}

bool NullType::isNonzero() {
    return 0;
}
