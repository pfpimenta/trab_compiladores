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
declist: dec declist { $$ = astreeCreate(ASTREE_PROGRAM, NULL, $1, $2, 0, 0); }
    | /* nada */ { $$ = 0; }
    ;
dec: funcdec  { $$ = $1; }
    | vardec { $$ = $1; }
    ;
vardec: TK_IDENTIFIER ':' vartypeandvalue ';' { $$ = astreeCreate(ASTREE_VARDEC, $1, $3, 0, 0, 0); }
    ;
vartypeandvalue: KW_BYTE LIT_CHAR { $$ = astreeCreate(ASTREE_KWBYTECHAR, $2, 0, 0, 0, 0); }
    | KW_BYTE LIT_INTEGER  { $$ = astreeCreate(ASTREE_KWBYTEINT, $2, 0, 0, 0, 0); }
    | KW_SHORT LIT_INTEGER { $$ = astreeCreate(ASTREE_KWSHORTINT, $2, 0, 0, 0, 0); }
    | KW_LONG LIT_INTEGER { $$ = astreeCreate(ASTREE_KWLONGINT, $2, 0, 0, 0, 0); }
    | KW_FLOAT LIT_INTEGER { $$ = astreeCreate(ASTREE_KWFLOATINT, $2, 0, 0, 0, 0); }
    | KW_FLOAT LIT_REAL { $$ = astreeCreate(ASTREE_KWFLOATREAL, $2, 0, 0, 0, 0); }
    | KW_DOUBLE LIT_INTEGER { $$ = astreeCreate(ASTREE_KWDOUBLEINT, $2, 0, 0, 0, 0); }
    | KW_BYTE '[' LIT_INTEGER ']' intlist { $$ = astreeCreate(ASTREE_KWBYTEARRAYINT, $3, $5, 0, 0, 0); }
    | KW_BYTE '[' LIT_INTEGER ']' charlist { $$ = astreeCreate(ASTREE_KWBYTEARRAYCHAR, $3, $5, 0, 0, 0); }
    | KW_BYTE '[' LIT_INTEGER ']'   { $$ = astreeCreate(ASTREE_KWBYTEARRAY, $3, 0, 0, 0, 0); }
    | KW_SHORT '[' LIT_INTEGER ']' intlist { $$ = astreeCreate(ASTREE_KWSHORTARRAYINT, $3, $5, 0, 0, 0); }
    | KW_SHORT '[' LIT_INTEGER ']' { $$ = astreeCreate(ASTREE_KWSHORTARRAY, $3, 0, 0, 0, 0); }
    | KW_LONG '[' LIT_INTEGER ']' intlist  { $$ = astreeCreate(ASTREE_KWLONGARRAYINT, $3, $5, 0, 0, 0); }
    | KW_LONG '[' LIT_INTEGER ']'    { $$ = astreeCreate(ASTREE_KWLONGARRAY, $3, 0, 0, 0, 0); }
    | KW_FLOAT '[' LIT_INTEGER ']' floatlist { $$ = astreeCreate(ASTREE_KWFLOATARRAYFLOAT, $3, $5, 0, 0, 0); }
    | KW_FLOAT '[' LIT_INTEGER ']' intlist  { $$ = astreeCreate(ASTREE_KWFLOATARRAYINT, $3, $5, 0, 0, 0); }
    | KW_FLOAT '[' LIT_INTEGER ']' { $$ = astreeCreate(ASTREE_KWFLOATARRAY, $3, 0, 0, 0, 0); }
    | KW_DOUBLE '[' LIT_INTEGER ']' intlist { $$ = astreeCreate(ASTREE_KWDOUBLEARRAYINT, $3, $5, 0, 0, 0); }
    | KW_DOUBLE '[' LIT_INTEGER ']' { $$ = astreeCreate(ASTREE_KWDOUBLEARRAY, $3, 0, 0, 0, 0); }
    ;
intlist: LIT_INTEGER intlist { $$ = astreeCreate(ASTREE_INTLIST, $1, $2, 0, 0, 0); }
    | LIT_INTEGER { $$ = astreeCreate(ASTREE_LITINT, $1, 0, 0, 0, 0); }
    ;

charlist: LIT_CHAR charlist { $$ = astreeCreate(ASTREE_CHARLIST, $1, $2, 0, 0, 0); }
    | LIT_CHAR { $$ = astreeCreate(ASTREE_LITCHAR, $1, 0, 0, 0, 0); }
    ;

floatlist: LIT_REAL floatlist { $$ = astreeCreate(ASTREE_FLOATLIST, $1, $2, 0, 0, 0); }
    | LIT_REAL { $$ = astreeCreate(ASTREE_LITREAL, $1, 0, 0, 0, 0); }
    ;

funcdec: vartype TK_IDENTIFIER '(' parameters ')' funcbody ';' { $$ = astreeCreate(ASTREE_FUNCDEC, $2, $1, $4, $6, 0); }
    ;

parameters: paramlist  { $$ = $1; }
    | /* nada */ { $$ = 0; }
    ;

paramlist: param ',' paramlist { $$ = astreeCreate(ASTREE_PARAMLIST, NULL, $1, $3, 0, 0); }
    | param { $$ = $1; }
    ;

param: vartype TK_IDENTIFIER { $$ = astreeCreate(ASTREE_PARAM, $2, $1, 0, 0, 0); }
    ;

vartype: KW_BYTE { $$ = astreeCreate(ASTREE_KWBYTE, NULL, 0, 0, 0, 0); }
    | KW_SHORT { $$ = astreeCreate(ASTREE_KWSHORT, NULL, 0, 0, 0, 0); }
    | KW_LONG { $$ = astreeCreate(ASTREE_KWLONG, NULL, 0, 0, 0, 0); }
    | KW_FLOAT { $$ = astreeCreate(ASTREE_KWFLOAT, NULL, 0, 0, 0, 0); }
    | KW_DOUBLE { $$ = astreeCreate(ASTREE_KWDOUBLE, NULL, 0, 0, 0, 0); }
    ;

funcbody: cmd { $$ = $1; }
    ;

cmdlist : cmdlist cmd ';' { $$ = astreeCreate(ASTREE_CMDLIST, NULL, $1, $2, 0, 0); }
    | /* nada */ { $$ = 0; }
    ;

cmd : atrib  { $$ = $1; }
    | '{' cmdlist '}'  { $$ = astreeCreate(ASTREE_CMDCOLCHETES, NULL, $1, 0, 0, 0); }
    | KW_READ TK_IDENTIFIER  { $$ = astreeCreate(ASTREE_KWREAD, $2, 0, 0, 0, 0); }
    | KW_PRINT printlist  { $$ = astreeCreate(ASTREE_KWPRINT, NULL, $2, 0, 0, 0); }
    | KW_RETURN expr { $$ = astreeCreate(ASTREE_KWRETURN, NULL, $2, 0, 0, 0); }
    | control { $$ = $1; }
    |/* nada*/ { $$ = 0; }
    ;

printlist: printelement printlist { $$ = astreeCreate(ASTREE_PRINTLIST, NULL, $1, $2, 0, 0); }
    | printelement { $$ = $1; }
    ;

printelement: LIT_STRING { $$ = astreeCreate(ASTREE_LITSTRING, $1, 0, 0, 0, 0); }
    | expr { $$ = $1; }
    ;

control: KW_WHEN '(' expr ')' KW_THEN cmd { $$ = astreeCreate(ASTREE_KWWHENTHEN, NULL, $3, $6, 0, 0); }
    | KW_WHEN '(' expr ')' KW_THEN cmd KW_ELSE cmd { $$ = astreeCreate(ASTREE_KWWHENTHENELSE, NULL, $3, $6, $8, 0); }
    | KW_WHILE '(' expr ')' cmd { $$ = astreeCreate(ASTREE_KWWHILE, NULL, $3, $5, 0, 0); }
    | KW_FOR '(' TK_IDENTIFIER '=' expr KW_TO expr ')' cmd { $$ = astreeCreate(ASTREE_KWFOR, $3, $5, $7, $9, 0); }
    ;

atrib: TK_IDENTIFIER '=' expr { $$ = astreeCreate(ASTREE_ATRIB, $1, $3, 0, 0, 0); }
    | TK_IDENTIFIER '#' expr '=' expr { $$ = astreeCreate(ASTREE_ATRIBARRAY, $1, $3, $5, 0, 0); }
    ;


expr:  '(' expr ')' { $$ = astreeCreate(ASTREE_EXPRPARENTESIS, NULL, $2, 0, 0, 0); }
    | TK_IDENTIFIER { $$ = astreeCreate(ASTREE_TKID, $1, 0, 0, 0, 0); }
    | TK_IDENTIFIER '[' expr ']'  { $$ = astreeCreate(ASTREE_TKIDARRAY, $1, $3, 0, 0, 0); }
    | TK_IDENTIFIER '(' args ')' { $$ = astreeCreate(ASTREE_TKIDFUNC, $1, $3, 0, 0, 0); }
    | LIT_INTEGER { $$ = astreeCreate(ASTREE_LITINT, $1, 0, 0, 0, 0); }
    | LIT_CHAR { $$ = astreeCreate(ASTREE_LITCHAR, $1, 0, 0, 0, 0); }
    | LIT_REAL { $$ = astreeCreate(ASTREE_LITREAL, $1, 0, 0, 0, 0); }
    | expr  OPERATOR_LE expr { $$ = astreeCreate(ASTREE_LESSEQUAL, NULL, $1, $3, 0, 0); }
    | expr OPERATOR_GE expr { $$ = astreeCreate(ASTREE_GREATEREQUAL, NULL, $1, $3, 0, 0); }
    | expr OPERATOR_EQ expr { $$ = astreeCreate(ASTREE_EQUAL, NULL, $1, $3, 0, 0); }
    | expr OPERATOR_NE expr { $$ = astreeCreate(ASTREE_NOTEQUAL, NULL, $1, $3, 0, 0); }
    | expr OPERATOR_AND expr { $$ = astreeCreate(ASTREE_AND, NULL, $1, $3, 0, 0); }
    | expr OPERATOR_OR expr { $$ = astreeCreate(ASTREE_OR, NULL, $1, $3, 0, 0); }
    | expr '*' expr { $$ = astreeCreate(ASTREE_MULT, NULL, $1, $3, 0, 0); }
    | expr '+' expr { $$ = astreeCreate(ASTREE_ADD, NULL, $1, $3, 0, 0); }
    | expr '-' expr { $$ = astreeCreate(ASTREE_SUB, NULL, $1, $3, 0, 0); }
    | expr '/' expr { $$ = astreeCreate(ASTREE_DIV, NULL, $1, $3, 0, 0); }
    | expr '<' expr { $$ = astreeCreate(ASTREE_LESS, NULL, $1, $3, 0, 0); }
    | expr '>' expr { $$ = astreeCreate(ASTREE_GREATER, NULL, $1, $3, 0, 0); }
    ;

args: expr argstail  { $$ = astreeCreate(ASTREE_ARGS, NULL, $1, $2, 0, 0); }
    |  /* nada */ { $$ = 0; }
    ;

argstail: ',' expr argstail { $$ = astreeCreate(ASTREE_ARGSTAIL, NULL, $2, $3, 0, 0); }
	|  /* nada */ { $$ = 0; }
	;



%%

void yyerror(char *s)
{
    int lineNum = getLineNumber();
    fprintf(stdout, "ERROR\n%s\nna linha: %i\n\n   ", s, lineNum);

    exit(3);
}
