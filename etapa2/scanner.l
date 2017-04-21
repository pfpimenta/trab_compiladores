%{
	#include <stdio.h>
	#include "hash.c"
	#include "y.tab.h"
	
	int token;
	int line_number = 1;
	int running = 1;
	int getLineNumber(void);
	int isRunning(void);
	int open_input(char* file_path);
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

"<="							{ return OPERATOR_LE;}
">="							{ return OPERATOR_GE; }
"=="							{ return OPERATOR_EQ;}
"!="							{ return OPERATOR_NE;}
"&&"							{ return OPERATOR_AND;}
"||"							{ return OPERATOR_OR;}


[0-9]+							{ addToken(yytext, LIT_INTEGER	); return LIT_INTEGER; }
[0-9]+\.[0-9]+					{ addToken(yytext, LIT_REAL); return LIT_REAL;  }
\'[^']\'						{ addToken(yytext, LIT_CHAR	); return LIT_CHAR; 	}
\"[^"]*\"						{ addToken(yytext, LIT_STRING	); return LIT_STRING; 	}

[a-zA-Z_][a-zA-Z0-9_]*			{ addToken(yytext, TK_IDENTIFIER); return TK_IDENTIFIER; 	}

"\n"							{ line_number++; }
" "|"	"						{ 		}

.								{ return TOKEN_ERROR;}

<COMMENT>
"*/"							{ BEGIN(INITIAL);}
<COMMENT>
"\n"							{ line_number++;}	
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

int isRunning()
{
	return running;
}
