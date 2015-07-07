%{
#include <iostream>
#include "../Token.h"

using namespace std;

#define YYSTYPE Token
extern int yylex();
extern int yylineno;
void yyerror(char* msg) {
    fprintf(stderr, "%s in line %d\n", msg, yylineno);
}
%}
%token FLOAT ID OPERATOR
%token SEMICOLON COMMA
%token LEFTPAR RIGHTPAR LEFTBRACE RIGHTBRACE
%token IF ELSE FUNCTION RETURN
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
    | matrix {
    }
    | LEFTPAR expression RIGHTPAR {
    }
    | ID LEFTPAR expression RIGHTPAR {
        }
matrix: LEFTBRACE rowlist RIGHTBRACE {
      }
rowlist: rowlist SEMICOLON row {
       }
       | row {
       }
row: row COMMA term {
   }
   | term {
   }
%%