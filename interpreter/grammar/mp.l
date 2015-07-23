%option case-insensitive
%option yylineno
%{
#include <iostream>
#include "../../kernel/AST.h"
#include "../../kernel/Type.h"
#include "../../kernel/Matrix.h"
#include "mpparser.hpp"
#include "../Token.h"
using namespace std;
using namespace Kernel;

extern "C" int yywrap() {
    return 1;
}

extern void yyerror(Kernel::AST*, char*);


volatile int inside = 0;
%}
%%
[ \t\n] ;
[0-9]+\.[0-9]+ {
    //cout << "Found a floating-point number: " << yytext << endl;
    yylval.type = new Matrix(atof(yytext));
    return FLOAT;
}
[0-9]+ {
    //cout << "Found an integer: " << yytext << endl;
    yylval.type = new Matrix(atof(yytext));
    return FLOAT;
}
if {
    //cout << "Found IF keyword: " << yytext << endl;
    return IF;
}
else {
    //cout << "Found ELSE keyword: " << yytext << endl;
    return ELSE;
}
while {
    //cout << "Found WHILE keyword: " << yytext << endl;
    return WHILE;
}
function {
    //cout << "Found FUNCTION keyword: " << yytext << endl;
    return FUNCTION;
}
return {
    //cout << "Found RETURN keyword: " << yytext << endl;
    return RETURN;
}
[\$]?[a-zA-Z_][a-zA-Z0-9_]* {
    //cout << "Found an identifier: " << yytext << endl;
    yylval.str = strdup(yytext);
    return ID;
}
[\+\-\*\/\@\^\%\=\<\>\!\.]+ {
    //cout << "Found an operator: " << yytext << endl;
    yylval.str = strdup(yytext);
    return OPERATOR;
}
\; {
    //cout << "Found a semicolon: " << yytext << endl;
    return SEMICOLON;
}
\, {
    //cout << "Found a comma: " << yytext << endl;
    return COMMA;
}
\( {
    //cout << "Found left parenthese: " << yytext << endl;
    return LEFTPAR;
}
\) {
    //cout << "Found right parenthese: " << yytext << endl;
    return RIGHTPAR;
}
\{ {
    //cout << "Found left brace: " << yytext << endl;
    inside++;
    return LEFTBRACE;
}
\} {
    //cout << "Found right brace: " << yytext << endl;
    inside--;
    return RIGHTBRACE;
}
\[ {
    //cout << "Found left bracket: " << yytext << endl;
    return LEFTBRK;
}
\] {
    //cout << "Found right bracket: " << yytext << endl;
    return RIGHTBRK;
}
. {
    yyerror(0, yytext);
}
%%