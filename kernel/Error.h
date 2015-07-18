//
// Created by R2 on 15.07.2015.
//


#ifndef MATHPROJECT_ERROR_H
#define MATHPROJECT_ERROR_H

#include <string>
#include <map>
#include <boost/format.hpp>

enum ErrorType {
    ET_UNKNOWN,
    ET_DIMENSIONS_MISMATCH,
    ET_UNKNOWN_IDENTIFIER,
    ET_UNKNOWN_FUNCTION,
    ET_ASSIGNMENT_ERROR
};

static std::map<ErrorType, std::string> codes =
        {
                {ET_UNKNOWN, "Unknown error"},
                {ET_DIMENSIONS_MISMATCH, "Matrix dimensions mismatch"},
                {ET_UNKNOWN_IDENTIFIER, "Unknown identifier"},
                {ET_UNKNOWN_FUNCTION, "Unknown function"},
                {ET_ASSIGNMENT_ERROR, "Error in assignment"}
        };

class Error {
    std::string text;

public:
    Error(ErrorType et) {
        //TODO: text processing of mistakes
        this->text = (boost::format("[%1%] %2%") % et % codes[et]).str();
    }

    std::string getText() {
        return text;
    }

    static void error(ErrorType et) {
        throw Error(et);
    }
};

#endif //MATHPROJECT_ERROR_H
