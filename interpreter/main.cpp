#include <iostream>
#include "Token.h"

using namespace std;

extern int yyparse();
extern int  yylex();

int main() {
    yyparse();
    return 0;
}