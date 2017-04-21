%{
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include "hash.h"
%}



%token 			KW_WORD
%token 			KW_BOOL
%token 			KW_BYTE
%token 			KW_IF
%token 			KW_THEN
%token 			KW_ELSE
%token 			KW_LOOP
%token 			KW_INPUT
%token 			KW_RETURN
%token 			KW_OUTPUT
%token 			OPERATOR_LE
%token 			OPERATOR_GE
%token 			OPERATOR_EQ
%token 			OPERATOR_NE
%token 			OPERATOR_AND
%token 			OPERATOR_OR
%token 			TK_IDENTIFIER
%token <symbol>	LIT_INTEGER
%token <symbol>	LIT_FALSE
%token <symbol>	LIT_TRUE
%token <symbol>	LIT_CHAR
%token <symbol>	LIT_STRING
%token 			TOKEN_ERROR