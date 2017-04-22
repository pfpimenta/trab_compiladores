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
%token KW_TO
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

program : declist 
    ;
declist: dec declist 
	| /* nada */
	;
dec: funcdec | vardec
	;
vardec: TK_IDENTIFIER ':' vartypeandvalue ';'
	;
vartypeandvalue: KW_BYTE LIT_CHAR
	| KW_BYTE LIT_INTEGER
	| KW_SHORT LIT_INTEGER
	| KW_LONG LIT_INTEGER
	;
funcdec: vartype TK_IDENTIFIER '(' parameters ')' funcbody
	;
parameters: paramlist
	| /* nada */
	;
paramlist: param ',' paramlist | param
	;
param:	vartype TK_IDENTIFIER
	;
vartype: KW_BYTE | KW_SHORT | KW_LONG | KW_FLOAT | KW_DOUBLE
	;
funcbody: cmd
	;
cmdlist : cmdlisttail
	| /* nada */
    ;
cmdlisttail: cmd ';' cmdlisttail | cmd
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
