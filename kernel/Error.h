//
// Created by R2 on 15.07.2015.
//


#ifndef MATHPROJECT_ERROR_H
#define MATHPROJECT_ERROR_H

#include <string>
#include <map>

enum ErrorType {
    ET_UNKNOWN,
    ET_DIMENSIONS_MISMATCH,
    ET_UNKNOWN_IDENTIFIER,
    ET_UNKNOWN_FUNCTION
};

static std::map<ErrorType, std::string> codes =
        {
                {ET_UNKNOWN,             "Unknown error"},
                {ET_DIMENSIONS_MISMATCH, "Matrix dimensions mismatch"},
                {ET_UNKNOWN_IDENTIFIER,  "Unknown identifier"},
                {ET_UNKNOWN_FUNCTION,    "Unknown function"}
        };

class Error {
    std::string text;

public:
    Error(ErrorType et) {
        //TODO: text processing of mistakes
        this->text = codes[et];
    }

    std::string getText() {
        return text;
    }

    static void error(ErrorType et) {
        throw Error(et);
    }
};


#endif //MATHPROJECT_ERROR_H
