//
// Created by main on 06.07.2015.
//

#ifndef MATHPROJECT_TOKEN_H
#define MATHPROJECT_TOKEN_H
#include <string>

struct Token {
    int type;
    std::string value;
    Token(int t = 0, std::string v = "") : type(t), value(v) { }
    operator int() { return type; }
};

#endif //MATHPROJECT_TOKEN_H
