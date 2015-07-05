#include <iostream>

using namespace std;

extern int yylex();

int main() {
    yylex();
    return 0;
}