%{
#include <iostream>
#include "../../kernel/AST.h"
#include "../../kernel/Matrix.h"

using namespace std;
using namespace Kernel;

extern int yylex();
#define YYSTYPE Type*
extern int yylineno;
void yyerror(char* msg) {
    fprintf(stderr, "%s in line %d\n", msg, yylineno);
}
%}
%token <type> FLOAT
%token <str> ID
%token <str> OPERATOR
%token SEMICOLON COMMA
%token LEFTPAR RIGHTPAR LEFTBRACE RIGHTBRACE
%token IF WHILE ELSE FUNCTION RETURN
%union
{
    Type* type;
    AST* ast;
    std::string str;
}
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
instruction: IF expression '\n' LEFTBRACE '\n' block '\n' RIGHTBRACE '\n' ELSE LEFTBRACE '\n' block '\n' RIGHTBRACE {
                $$ = new ConditionalAST($2, $6, $13);
           }
           | IF expression '\n' LEFTBRACE '\n' block '\n' RIGHTBRACE {
                $$ = new ConditionalAST($2, $6, 0);
           }
           | WHILE expression '\n' LEFTBRACE '\n' block '\n' RIGHTBRACE {
                $$ = new WhileLoopAST($2, $6);
           }
           | FUNCTION ID LEFTPAR arglist RIGHTPAR '\n' LEFTBRACE '\n' block '\n' RIGHTBRACE {
                $$ = new FunctionAST($2, $4, $9);
           }
           | expression OPERATOR expression {
                $$ = new FunctionAST($2);
                // TODO : add operators
           }
           | OPERATOR expression {
                $$ = new FunctionAST($2);
                // TODO : add operators
           }
           | expression {
                $$ = $1;
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
        $$ = new TypeAST($1);
    }
    | ID {
        $$ = new TypeAST($1);
    }
    | matrix {
        $$ = new TypeAST($1);
    }
    | LEFTPAR expression RIGHTPAR {
        $$ = $2;
    }
    | ID LEFTPAR row RIGHTPAR {
        $$ = new FunctionAST($1, $3);
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