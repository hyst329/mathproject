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
%token IF WHILE ELSE FUNCTION RETURN
%%
program: block {
           $$ = $1;
       }
block: block instruction '\n' {
       }
       | block instruction SEMICOLON {
       }
       | instruction SEMICOLON {
       }
       | instruction {
       }
instruction: IF expression '\n' LEFTBRACE '\n' block '\n' RIGHTBRACE {
           }
           | WHILE expression '\n' LEFTBRACE '\n' block '\n' RIGHTBRACE {
           }
           | FUNCTION ID LEFTPAR arglist RIGHTPAR '\n' LEFTBRACE '\n' block '\n' RIGHTBRACE {
           }
           |  expression OPERATOR expression {
           }
           | OPERATOR expression {
           }
           | expression {
           }
arglist: arglist COMMA ID {
       }
       | ID {
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