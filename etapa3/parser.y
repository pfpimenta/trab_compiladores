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

%left OPERATOR_AND OPERATOR_OR
%left OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE
%left '<' '>' '!'
%left '-' '+'
%left '*' '/'


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
    | KW_FLOAT LIT_REAL
    | KW_DOUBLE LIT_INTEGER
    | KW_BYTE '[' LIT_INTEGER ']' intlist
    | KW_BYTE '[' LIT_INTEGER ']' charlist
    | KW_SHORT '[' LIT_INTEGER ']' intlist
    | KW_LONG '[' LIT_INTEGER ']' intlist
    | KW_FLOAT '[' LIT_INTEGER ']' floatlist
    | KW_DOUBLE '[' LIT_INTEGER ']' intlist
    ;
intlist: LIT_INTEGER intlist
    | /* nada */
    ;

charlist: LIT_CHAR charlist
    | /* nada */
    ;

floatlist: LIT_REAL floatlist
    | /* nada */
    ;

funcdec: vartype TK_IDENTIFIER '(' parameters ')' funcbody ';'
    ;

parameters: paramlist
    | /* nada */
    ;

paramlist: param ',' paramlist | param
    ;

param:    vartype TK_IDENTIFIER
    ;

vartype: KW_BYTE | KW_SHORT | KW_LONG | KW_FLOAT | KW_DOUBLE
    ;

funcbody: cmd
    ;

cmdlist : cmdlist cmd ';'
    | /* nada */
    ;

cmd : atrib
    | '{' cmdlist '}' 
    | KW_READ TK_IDENTIFIER
    | KW_PRINT printlist
    | KW_RETURN expr
    | control
    |/* nada*/ 
    ;
	
printlist: printelement printlist | printelement
    ;

printelement: LIT_STRING | expr
    ;

control: KW_WHEN '(' expr ')' KW_THEN cmd
    | KW_WHEN '(' expr ')' KW_THEN cmd KW_ELSE cmd
    | KW_WHILE '(' expr ')' cmd
    | KW_FOR '(' TK_IDENTIFIER '=' expr KW_TO expr ')' cmd
    ;

atrib: TK_IDENTIFIER '=' expr
    | TK_IDENTIFIER '#' expr '=' expr
    ;


expr:  '(' expr ')'
    | TK_IDENTIFIER
    | TK_IDENTIFIER '[' expr ']'
    | TK_IDENTIFIER '(' args ')'
    | LIT_INTEGER
    | LIT_CHAR
    | LIT_REAL
    | expr operator expr
    ;
	
args: expr argstail
    |  /* nada */
    ;
	
argstail: ',' expr argstail
	|  /* nada */
	;

operator: OPERATOR_LE
    | OPERATOR_GE
    | OPERATOR_EQ
    | OPERATOR_NE
    | OPERATOR_AND
    | OPERATOR_OR
    | '*'
    | '+'
    | '-'
    | '/'
    | '<'
    | '>'
    | '!' 
;

%%

void yyerror(char *s)
{
    int lineNum = getLineNumber();
    fprintf(stdout, "ERROR\n%s\nna linha: %i\n\n   ", s, lineNum);
    
    exit(3);
}
