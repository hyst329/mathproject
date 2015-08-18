%option case-insensitive
%option yylineno
%{
#include <iostream>
#include "kernel/AST.h"
#include "kernel/Type.h"
#include "kernel/Matrix.h"
#include "kernel/StringType.h"
#include "kernel/Error.h"
#include "mpparser.hpp"
#include <QStack>
#include <QSet>
using namespace std;
using namespace Kernel;

extern "C" int yywrap() {
    return 1;
}

QStack<YY_BUFFER_STATE> include_stack;

extern void yyerror(Kernel::AST*, char*);
extern void yy_switch_to_buffer(YY_BUFFER_STATE);

extern QString checkFilename(QString filename);
QSet<QString> includedFiles;

volatile int inside = 0;
QString currentFilename;
QStack<QString> filenameStack;
%}
%x incl
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
\"[^\"\n]*\"  {
    QString withoutquotes = QString(yytext).mid(1, strlen(yytext) - 2);
    yylval.type = new StringType(withoutquotes);
    return STRING;
}
\"[^\"\n]*\n {
    QString msg = QString("%1 at %2:%3").arg(QString(yytext)).arg(currentFilename).arg(yylineno);
    Error::warning(WT_UNTERMINATED_STRING, {msg});
    yylval.type = new StringType(yytext);
    return STRING;
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
operator {
    //cout << "Found OPERATOR keyword: " << yytext << endl;
    return OPERATORKW;
}
prec {
    //cout << "Found PREC keyword: " << yytext << endl;
    return PREC;
}
ref {
    //cout << "Found REF keyword: " << yytext << endl;
    return REF;
}
include {
    BEGIN(incl);
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
<incl>[ \t]* ; /* eat the whitespace */
<incl>[^ \t\n]+ {
    QString path = checkFilename(yytext);
    QString error;
    if(includedFiles.contains(path)) goto begin;
    includedFiles << path;
    currentFilename = path;
    filenameStack.push(path);
    include_stack.push(YY_CURRENT_BUFFER);
    yyin = fopen(path.toLatin1().constData(), "r");
    error = QString("%1 : %2").arg(QString(yytext)).arg(path);
    if (!yyin)
        Error::error(ET_FILE, {error});
    yy_switch_to_buffer(yy_create_buffer(yyin, YY_BUF_SIZE));
    begin:
    BEGIN(INITIAL);
}
<<EOF>> {
    if (include_stack.empty())
    {
        yyterminate();
    }
    else
    {
        yy_delete_buffer( YY_CURRENT_BUFFER );
        yy_switch_to_buffer(include_stack.top());
        include_stack.pop();
        currentFilename = filenameStack.top();
        filenameStack.pop();
    }
}
%%
