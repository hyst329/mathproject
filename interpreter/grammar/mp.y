%{
#include <QTextStream>
#include "kernel/AST.h"
#include "kernel/Function.h"
#include "kernel/Type.h"
#include "kernel/Error.h"
#include "kernel/Matrix.h"
#include <QString>
#include <QList>
#include <QMap>
#include <QSet>
#include <QtDebug>

using namespace Kernel;

extern int yylex();
extern int yylineno;
extern QString currentFilename;

void yyerror(Kernel::AST* a, char* msg) {
    QString location = QString("%1:%2").arg(currentFilename).arg(yylineno);
    Error::error(ET_SYNTAX, { QString("%1 at %2").arg(msg).arg(location) });
}

extern FILE* yyin;

static QString opMarker = "$operator";

extern volatile int inside;

inline bool isInteractive() {
    return yyin == stdin && !inside;
}

QMap<QString, double> prec = {
    {opMarker + "^",  9},
    {opMarker + "*",  8},
    {opMarker + "/",  8},
    {opMarker + "%",  8},
    {opMarker + "!",  8},
    {opMarker + "+",  7},
    {opMarker + "-",  7},
    {opMarker + "<",  6},
    {opMarker + "<=", 6},
    {opMarker + ">",  6},
    {opMarker + ">=", 6},
    {opMarker + "==", 5},
    {opMarker + "!=", 5},
    {opMarker + "&",  4},
    {opMarker + "@",  3},
    {opMarker + "|",  2},
    {opMarker + "=",  1}
};

QSet<QString> right_assoc = {opMarker + "^", opMarker + "="};

static bool last_term = 0;

%}
%error-verbose
%token <type> FLOAT STRING
%token <str> ID
%token <str> OPERATOR
%token SEMICOLON COMMA 
%token LEFTPAR RIGHTPAR LEFTBRACE RIGHTBRACE LEFTBRK RIGHTBRK
%token IF WHILE ELSE FUNCTION RETURN OPERATORKW PREC REF
%type <ast> program block bracedblock instruction expression term
%type <arglist> arglist
%type <exprlist> exprlist
%type <row> row
%type <rowlist> rowlist
%type <type> matrix
%type <str> arg
%right OPERATOR
%right IFX ELSE
%union
{
    Type *type;
    Kernel::AST *ast;
    char* str;
    QStringList *arglist;
    QList<Kernel::AST*> *exprlist;
    QList<double> *row;
    QList<QList<double>> *rowlist;
}
%start program
%parse-param {Kernel::AST *&result}
%%
program: block {
           $$ = result = $1;
           //cout << typeid(*result).name() << endl;
       }
block: block instruction {
            ((BlockAST*)$1)->children.append($2);
            $$ = $1;
       }
       | instruction {
            $$ = new BlockAST();
            ((BlockAST*)$$)->children.append($1);
       }
bracedblock : LEFTBRACE block RIGHTBRACE {
                /*inside = 1;*/
                $$ = $2;
                /*inside = 0;*/
}
instruction: IF expression instruction %prec IFX {
                $$ = new ConditionalAST($2, $3, 0);
                if(isInteractive()) {
                    result = $$;
                    return 0;
                }
           }
           | IF expression instruction ELSE instruction {
                $$ = new ConditionalAST($2, $3, $5);
                if(isInteractive()) {
                    result = $$;
                    return 0;
                }
           }
           | WHILE expression instruction {
                $$ = new WhileLoopAST($2, $3);
                if(isInteractive()) {
                    result = $$;
                    return 0;
                }
           }
           | FUNCTION ID LEFTPAR arglist RIGHTPAR instruction {
                UserFunction* f = new UserFunction($6, *$4);
                //cout << "Function BODY: " << $2 << endl;
                AST::functions[$2] = f;
                $$ = new FunctionBodyAST(f);
                if(isInteractive()) {
                    result = $$;
                    return 0;
                }
           }
           | OPERATORKW OPERATOR PREC FLOAT LEFTPAR arglist RIGHTPAR instruction {
                UserFunction* f = new UserFunction($8, *$6);
                AST::functions[opMarker + $2] = f;
                $$ = new FunctionBodyAST(f);
                prec[opMarker + $2] = ((Matrix*)$4)->element(1,1);
                if(isInteractive()) {
                    result = $$;
                    return 0;
                }
           }
           | RETURN expression SEMICOLON {
                $$ = new ReturnAST($2);
                if(isInteractive()) {
                    result = $$;
                    return 0;
                }
           }
           | expression SEMICOLON {
                $$ = $1;
                if(isInteractive()) {
                    result = $$;
                    return 0;
                }
           }
           | bracedblock {
                $$ = $1;
                if(isInteractive()) {
                    result = $$;
                    return 0;
                }
           }
arglist: arglist COMMA arg {
           $1->append($3);
           $$ = $1;
       }
       | arg {
           $$ = new QStringList;
           $$->append($1);
       }
arg: ID {
       $$ = $1;
   }
   | REF ID {
       $$ = strdup((QByteArray("ref ") + $2).constData());
   }
exprlist: exprlist COMMA expression {
            $1->append($3);
            $$ = $1;
        }
        | expression {
            $$ = new QList<Kernel::AST*>;
            $$->append($1);
        }
expression: expression OPERATOR expression {
              double last = INT_MAX;
              if(dynamic_cast<FunctionAST*>($3) and !last_term)
                  last = prec.find(((FunctionAST*)($3))->function) == prec.end() ?
                         INT_MAX : prec[((FunctionAST*)($3))->function];
              double added = prec.find(opMarker + $2) == prec.end() ? INT_MIN : prec[opMarker + $2];
              //cout << "Added: " << added << " Last: " << last << endl;
              if(right_assoc.contains(opMarker + $2) ? added <= last : added < last) {
                  QList<AST*> v = { $1, $3 };
                  $$ = new FunctionAST(opMarker + $2, v);
              }
              else {
                  AST* tmp = ((FunctionAST*)($3))->arguments[0];
                  ((FunctionAST*)($3))->arguments[0] = new FunctionAST(opMarker + $2, {$1, tmp});
                  $$ = $3;
              }
              last_term = 0;
          }
          | OPERATOR expression {
              QList<AST*> v = { $2 };
              $$ = new FunctionAST(opMarker + $1, v);
          }
          | term {
              $$ = $1;
              last_term = 1;
          }
term: FLOAT {
        $$ = new TypeAST($1);
    }
    | STRING {
        $$ = new TypeAST($1);
    }
    | ID {
        $$ = new VarAST($1);
    }
    | matrix {
        $$ = new TypeAST($1);
    }
    | LEFTPAR expression RIGHTPAR {
        $$ = $2;
    }
    | ID LEFTPAR exprlist RIGHTPAR {
        $$ = new FunctionAST($1, *$3);
    }
    | ID LEFTBRK exprlist RIGHTBRK {
        $3->prepend(new VarAST($1));
        $$ = new FunctionAST("$index", *$3);
    }
matrix: LEFTBRACE rowlist RIGHTBRACE {
          $$ = new Matrix(*$2);
      }
rowlist: rowlist SEMICOLON row {
           $1->append(*$3);
           $$ = $1;
       }
       | row {
           $$ = new QList<QList<double>>;
           $$->append(*$1);
       }
row: row COMMA FLOAT {
         $1->append(((Matrix*)$3)->element(1, 1));
         $$ = $1;
   }
   | FLOAT {
         $$ = new QList<double>;
         $$->append(((Matrix*)$1)->element(1, 1));
   }
   | row COMMA error {
         Error::error(ET_ROW_NONCONSTANT);
   }
   | error {
         Error::error(ET_ROW_NONCONSTANT);
   }
%%
