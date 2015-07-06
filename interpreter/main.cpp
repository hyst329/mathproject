#include <iostream>
#include "Token.h"

using namespace std;

extern int yyparse();

int main() {
    yyparse();
    return 0;
}