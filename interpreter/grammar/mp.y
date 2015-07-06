%{
#include <iostream>
#include "../Token.h"

using namespace std;

#define YYSTYPE Token
extern int yylex();
void yyerror(char* msg) {
    fprintf(stderr, "%s\n", msg);
}
%}
%token FLOAT ID OPERATOR
%token SEMICOLON COMMA
%token LEFTPAR RIGHTPAR LEFTBRACE RIGHTBRACE
%%
program: program instruction '\n' {
       }
       | program instruction SEMICOLON {
       }
       | instruction SEMICOLON {
       }
       | instruction {
       }
instruction: expression OPERATOR expression {
           }
           | OPERATOR expression {
           }
           | expression {
           }
expression: term OPERATOR term {
          }
          | OPERATOR term {
          }
          | term {
          }
term: FLOAT {
    }
    | ID {
    }
    | LEFTPAR expression RIGHTPAR {
    }
    | ID LEFTPAR expression RIGHTPAR {
        }
%%