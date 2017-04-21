%{
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include "hash.h"
    void yyerror(char *s);
%}


%union{ linkedList_t* symbol; }

%token KW_BYTE
%token KW_SHORT
%token KW_LONG
%token KW_FLOAT
%token KW_DOUBLE
%token KW_WHEN
%token KW_THEN
%token KW_ELSE
%token KW_WHILE
%token KW_FOR
%token KW_READ
%token KW_RETURN
%token KW_PRINT

%token OPERATOR_LE
%token OPERATOR_GE
%token OPERATOR_EQ
%token OPERATOR_NE
%token OPERATOR_AND
%token OPERATOR_OR

%token <symbol> TK_IDENTIFIER

%token <symbol> LIT_INTEGER
%token <symbol> LIT_REAL
%token <symbol> LIT_CHAR
%token <symbol> LIT_STRING

%token TOKEN_ERROR


%%

program : cmdlist 
    ;

cmdlist : cmd ';' cmdlist | cmd 
    ;
cmd : LIT_INTEGER | TK_IDENTIFIER '=' expr
    ; 

expr: expr '*' expr | '(' expr ')' | LIT_INTEGER | TK_IDENTIFIER
    ; 
%%

void yyerror(char *s)
{
    int lineNum = getLineNumber();
    fprintf(stdout, "ERROR\n%s\nna linha: %i\n\n   ", s, lineNum);
    
    exit(3);
}
