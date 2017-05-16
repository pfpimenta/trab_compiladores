%{
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include "hash.h"
    #include "astree.h"
    void yyerror(char *s);
    
    ASTREE* root;
%}

%start program

%union{ LINKED_LIST* symbol; ASTREE* astree;}

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

%type <astree> declist
%type <astree> dec
%type <astree> vardec
%type <astree> funcdec
%type <astree> vartypeandvalue
%type <astree> intlist
%type <astree> floatlist
%type <astree> charlist

%left OPERATOR_AND OPERATOR_OR
%left OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE
%left '<' '>' '!'
%left '-' '+'
%left '*' '/'


%%

program : declist { root = $1; }
    ;
declist: dec declist { $$ = astreeCreate(PROGRAM, NULL, $1, $2, 0, 0); }
    | /* nada */ { $$ = astreeCreate(PROGRAM, NULL, 0, 0, 0, 0); }
    ;
dec: funcdec  { $$ = $1; }
    | vardec { $$ = $1; }
    ;
vardec: TK_IDENTIFIER ':' vartypeandvalue ';' { $$ = astreeCreate(PROGRAM, NULL, $1, $3, 0, 0); }
    ;
vartypeandvalue: KW_BYTE LIT_CHAR { $$ = astreeCreate(KWBYTE, NULL,
                                    astreeCreate(LITCHAR, $2, 0, 0, 0, 0), 0, 0, 0); }
    | KW_BYTE LIT_INTEGER 
    | KW_SHORT LIT_INTEGER 
    | KW_LONG LIT_INTEGER 
    | KW_FLOAT LIT_INTEGER 
    | KW_FLOAT LIT_REAL 
    | KW_DOUBLE LIT_INTEGER 
    | KW_BYTE '[' LIT_INTEGER ']' intlist 
    | KW_BYTE '[' LIT_INTEGER ']' charlist
    | KW_BYTE '[' LIT_INTEGER ']'  
    | KW_SHORT '[' LIT_INTEGER ']' intlist
    | KW_SHORT '[' LIT_INTEGER ']'
    | KW_LONG '[' LIT_INTEGER ']' intlist 
    | KW_LONG '[' LIT_INTEGER ']'  
    | KW_FLOAT '[' LIT_INTEGER ']' floatlist 
    | KW_FLOAT '[' LIT_INTEGER ']' intlist  
    | KW_FLOAT '[' LIT_INTEGER ']' 
    | KW_DOUBLE '[' LIT_INTEGER ']' intlist
    | KW_DOUBLE '[' LIT_INTEGER ']' 
    ;
intlist: LIT_INTEGER intlist { $$ = astreeCreate(INTLIST, NULL, $1, $2, 0, 0); }
    | LIT_INTEGER
    ;

charlist: LIT_CHAR charlist
    | LIT_CHAR
    ;

floatlist: LIT_REAL floatlist
    | LIT_REAL
    ;

funcdec: vartype TK_IDENTIFIER '(' parameters ')' funcbody ';'
    ;

parameters: paramlist
    | /* nada */
    ;

paramlist: param ',' paramlist
    | param
    ;

param:    vartype TK_IDENTIFIER
    ;

vartype: KW_BYTE
    | KW_SHORT
    | KW_LONG
    | KW_FLOAT
    | KW_DOUBLE
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


expr:  '(' expr ')' { $$ = $2; }
    | TK_IDENTIFIER { $$ = $1; }
    | TK_IDENTIFIER '[' expr ']'  { $$ = astreeCreate(ARRAY, NULL, astreeCreate(ARRAY, $1, 0, 0, 0, 0), $3, 0, 0);}
    | TK_IDENTIFIER '(' args ')' { $$ = astreeCreate(ARRAY, NULL, astreeCreate(FUNCTION, $1, 0, 0, 0, 0), $3, 0, 0);}
    | LIT_INTEGER 
    | LIT_CHAR
    | LIT_REAL
    | expr  OPERATOR_LE expr
    | expr OPERATOR_GE expr
    | expr OPERATOR_EQ expr
    | expr OPERATOR_NE expr
    | expr OPERATOR_AND expr
    | expr OPERATOR_OR expr
    | expr '*' expr
    | expr '+' expr
    | expr '-' expr
    | expr '/' expr
    | expr '<' expr
    | expr '>' expr
    | expr '!' expr
    ;
	
args: expr argstail
    |  /* nada */
    ;
	
argstail: ',' expr argstail
	|  /* nada */
	;



%%

void yyerror(char *s)
{
    int lineNum = getLineNumber();
    fprintf(stdout, "ERROR\n%s\nna linha: %i\n\n   ", s, lineNum);
    
    exit(3);
}
