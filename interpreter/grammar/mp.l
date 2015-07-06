%{
#include <iostream>
using namespace std;

extern "C" int yywrap() {
    return 1;
}
%}
%%
[ \t] ;
[0-9]+\.[0-9]+ { cout << "Found a floating-point number: " << yytext << endl; }
[0-9]+  { cout << "Found an integer: " << yytext << endl; }
[a-zA-Z_][a-zA-Z0-9_]* { cout << "Found an identifier: " << yytext << endl; }
[\+\-\*\/\@\^\%\=]+ { cout << "Found an operator: " << yytext << endl; }
\; { cout << "Found a semicolon: " << yytext << endl; }
\, { cout << "Found a comma: " << yytext << endl; }
\( { cout << "Found left parenthese: " << yytext << endl; }
\) { cout << "Found right parenthese: " << yytext << endl; }
\{ { cout << "Found left brace: " << yytext << endl; }
\} { cout << "Found right brace: " << yytext << endl; }
%%