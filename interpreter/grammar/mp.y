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
void yyerror(Kernel::AST* a, char* msg) {
    fprintf(stderr, "%s in line %d\n", msg, yylineno);
}

static std::string opMarker = "$operator";
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
%type <row> row
%type <rowlist> rowlist
%type <type> matrix
%union
{
    Type *type;
    Kernel::AST *ast;
    char* str;
    std::vector<std::string> *arglist;
    std::vector<Kernel::AST*> *exprlist;
    std::vector<double> *row;
    std::vector<std::vector<double>> *rowlist;
}
%start program
%parse-param {Kernel::AST *&result}
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
                //f->arguments = $4;
                AST::functions[$2] = f;
                $$ = new FunctionBodyAST(f, *$4);
           }
           | expression OPERATOR expression {
                std::vector<AST*> v = { $1, $3 };
                $$ = new FunctionAST(opMarker + $2, v);
           }
           | OPERATOR expression {
                std::vector<AST*> v = { $2 };
                $$ = new FunctionAST(opMarker + $1, v);
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
            $1->push_back($3);
            $$ = $1;
        }
        | expression {
            $$ = new std::vector<Kernel::AST*>;
            $$->push_back($1);
        }
expression: term OPERATOR term {
              std::vector<AST*> v = { $1, $3 };
              $$ = new FunctionAST(opMarker + $2, v);
          }
          | OPERATOR term {
              std::vector<AST*> v = { $2 };
              $$ = new FunctionAST(opMarker + $1, v);
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
          $$ = new Matrix(*$2);
          delete $2;
      }
rowlist: rowlist SEMICOLON row {
           $1->push_back(*$3);
           $$ = $1;
       }
       | row {
           $$ = new std::vector<std::vector<double>>;
           $$->push_back(*$1);
       }
row: row COMMA FLOAT {
         $1->push_back(((Matrix*)$3)->element(0, 0));
         $$ = $1;
   }
   | FLOAT {
         $$ = new std::vector<double>;
         $$->push_back(((Matrix*)$1)->element(0, 0));
   }
%%