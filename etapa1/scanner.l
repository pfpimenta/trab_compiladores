// Pedro Henrique Augustin e Pedro Foletto Pimenta
// XXXXXX e 229778
%{
	#include <stdio.h>
	#include "tokens.h"
	#include "hash.c"
	
	int open_input(char* file_path);
	int token;
	int line_number = 1;
	int getLineNumber(void);
	int running = 1;
	int open_input(char* file_path);
	
	#include "main.c"
%}

%x COMMENT

%%

"byte"							{ return KW_BYTE; 											}
"short"							{ return KW_SHORT; 											}
"long"							{ return KW_LONG; 											}
"float"							{ return KW_FLOAT; 											}	
"double"						{ return KW_DOUBLE; 										}
"when"							{ return KW_WHEN; 											}
"then"							{ return KW_THEN; 											}
"else"							{ return KW_ELSE; 											}
"while"						 	{ return KW_WHILE; 											}
"for"							{ return KW_FOR; 											}
"read"							{ return KW_READ; 											}
"return"						{ return KW_RETURN; 										}
"print"							{ return KW_PRINT; 											}

"/*"							{ BEGIN(COMMENT);}
"//"[^"\n"]*							{ 							}

[-,;:(){}*+/<>=!&$\]\[]			{ return (int)yytext[0]; 									}

"<="							{ return OPERATOR_LE; 										}
">="							{ return OPERATOR_GE; 										}
"=="							{ return OPERATOR_EQ; 										}
"!="							{ return OPERATOR_NE; 										}
"&&"							{ return OPERATOR_AND; 										}
"||"							{ return OPERATOR_OR; 										}


[0-9]+							{ addSymbol(yytext, LIT_INTEGER	); return LIT_INTEGER; 		}
[0-9]*\.[0-9]+					{ addSymbol(yytext, LIT_REAL); return LIT_REAL;  			}
\'[^']\'						{ addSymbol(yytext, LIT_CHAR	); return LIT_CHAR; 		}
\"[^"]*\"						{ addSymbol(yytext, LIT_STRING	); return LIT_STRING; 		}

[a-zA-Z_][a-zA-Z0-9_]*			{ addSymbol(yytext, TK_IDENTIFIER); return TK_IDENTIFIER; 	}

"\n"							{ line_number++; 						}
" "|"	"						{ 								}

.								{ return TOKEN_ERROR; 					}

<COMMENT>
"*/"							{ BEGIN(INITIAL);						}
<COMMENT>
"\n"							{ line_number++;						}	
<COMMENT>
. 								{ 							}

%%

int yywrap()
{
	running = 0;

	return 1;
}

int open_input(char* file_path)
{
	FILE* file = fopen(file_path,"r");
	int could_open = (file != NULL);

	if(!could_open)
	{
		return 0;
	}
	else
	{
		yyin = file;

		return 1;
	}
}

int getLineNumber()
{
	return line_number;
}
