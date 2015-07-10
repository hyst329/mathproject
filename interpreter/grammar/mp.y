%{
#include <iostream>
#include "../../kernel/AST.h"
#include "../../kernel/Function.h"
#include "../../kernel/Type.h"
#include "../../kernel/Matrix.h"
#include <string>
#include <vector>

using namespace std;
using namespace Kernel;

extern int yylex();
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
%type <ast> program block instruction expression term
%type <arglist> arglist
%type <exprlist> exprlist
%union
{
    Type *type;
    Kernel::AST *ast;
    char* str;
    std::vector<std::string> *arglist;
    std::vector<Kernel::AST*> *exprlist;
}
%%
program: block {
           $$ = $1;
       }
block: block instruction '\n' {
            ((BlockAST*)$1)->children.push_back($2);
            $$ = $1;
       }
       | block instruction SEMICOLON {
            ((BlockAST*)$1)->children.push_back($2);
            $$ = $1;
       }
       | instruction SEMICOLON {
            $$ = new BlockAST();
            ((BlockAST*)$$)->children.push_back($1);
       }
       | instruction {
            $$ = new BlockAST();
            ((BlockAST*)$$)->children.push_back($1);
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
                Function* f = new Function($9);
                AST::functions[$2] = f;
                $$ = new FunctionBodyAST(f, *$4);
           }
           | expression OPERATOR expression {
                std::vector<AST*> v = { $1, $3 };
                $$ = new FunctionAST($2, v);
           }
           | OPERATOR expression {
                std::vector<AST*> v = { $2 };
                $$ = new FunctionAST($1, v);
           }
           | expression {
                $$ = $1;
           }
arglist: arglist COMMA ID {
           $1->push_back($3);
           $$ = $1;
       }
       | ID {
           $$ = new std::vector<std::string>;
           $$->push_back($1);
       }
exprlist: exprlist COMMA expression {
        }
        | expression {
        }
expression: term OPERATOR term {
              std::vector<AST*> v = { $1, $3 };
              $$ = new FunctionAST($2, v);
          }
          | OPERATOR term {
              std::vector<AST*> v = { $2 };
              $$ = new FunctionAST($1, v);
          }
          | term {
              $$ = $1;
          }
term: FLOAT {
        $$ = new TypeAST($1);
    }
    | ID {
        $$ = new VarAST($1);
    }
    | matrix {
        //$$ = new TypeAST($1);
    }
    | LEFTPAR expression RIGHTPAR {
        $$ = $2;
    }
    | ID LEFTPAR exprlist RIGHTPAR {
        $$ = new FunctionAST($1, *$3);
    }
matrix: LEFTBRACE rowlist RIGHTBRACE {
      }
rowlist: rowlist SEMICOLON row {
       }
       | row {
       }
row: row COMMA expression {
   }
   | expression {
   }
%%