//
// Created by main on 05.07.2015.
//

#include "AST.h"
#include "Function.h"


namespace Kernel {
    map<string, Function *> AST::functions = std::map<std::string, Function *>();
}