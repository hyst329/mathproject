%option case-insensitive
%option yylineno
%{
#include <iostream>
#include "mpparser.hpp"
#include "../Token.h"
using namespace std;

extern "C" int yywrap() {
    return 1;
}

%}
%%
[ \t] ;
[0-9]+\.[0-9]+ { cout << "Found a floating-point number: " << yytext << endl; return FLOAT; }
[0-9]+  { cout << "Found an integer: " << yytext << endl; return FLOAT; }
if { cout << "Found IF keyword: " << yytext << endl; return IF; }
else { cout << "Found ELSE keyword: " << yytext << endl; return ELSE; }
while { cout << "Found WHILE keyword: " << yytext << endl; return WHILE; }
function { cout << "Found FUNCTION keyword: " << yytext << endl; return FUNCTION; }
return { cout << "Found RETURN keyword: " << yytext << endl; return RETURN; }
[a-zA-Z_][a-zA-Z0-9_]* { cout << "Found an identifier: " << yytext << endl; return ID; }
[\+\-\*\/\@\^\%\=\<\>]+ { cout << "Found an operator: " << yytext << endl; return OPERATOR; }
\; { cout << "Found a semicolon: " << yytext << endl; return SEMICOLON; }
\, { cout << "Found a comma: " << yytext << endl; return COMMA; }
\( { cout << "Found left parenthese: " << yytext << endl; return LEFTPAR; }
\) { cout << "Found right parenthese: " << yytext << endl; return RIGHTPAR; }
\{ { cout << "Found left brace: " << yytext << endl; return LEFTBRACE; }
\} { cout << "Found right brace: " << yytext << endl; return RIGHTBRACE; }
%%