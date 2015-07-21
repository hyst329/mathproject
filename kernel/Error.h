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
    ET_SYNTAX,
    ET_DIMENSIONS_MISMATCH,
    ET_UNKNOWN_IDENTIFIER,
    ET_UNKNOWN_FUNCTION,
    ET_ASSIGNMENT_ERROR,
    ET_LOCAL_TOPLEVEL,
    ET_INCOMPATIBLE_TYPES
};

static std::map<ErrorType, std::string> codes =
        {
                {ET_UNKNOWN,             "Unknown error"},
                {ET_SYNTAX,              "Syntax error: %1%"},
                {ET_DIMENSIONS_MISMATCH, "Matrix dimensions mismatch"},
                {ET_UNKNOWN_IDENTIFIER,  "Unknown identifier: %1%"},
                {ET_UNKNOWN_FUNCTION,    "Unknown function: %1%"},
                {ET_ASSIGNMENT_ERROR,    "Error in assignment"},
                {ET_LOCAL_TOPLEVEL,      "Creating local variable in top-level statement"},
                {ET_INCOMPATIBLE_TYPES,  "Incompatible types: %1% and %2%"}
        };

class Error {
    std::string text;

public:
    Error(ErrorType et, std::vector<std::string> &args) {
        //TODO: text processing of mistakes
        text = (boost::format("[%1$3d] %2%") % et % codes[et]).str();
        boost::format f(text);
        for(int i = 0; i < args.size(); i++) f = f % args[i];
        text = f.str();
    }

    std::string getText() {
        return text;
    }

    static void error(ErrorType et, std::vector<std::string> args = std::vector<std::string>()) {
        throw Error(et, args);
    }
};

#endif //MATHPROJECT_ERROR_H
