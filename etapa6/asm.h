#ifndef ASM_H
#define ASM_H
#include "tac.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ASM_STRING_SIZE 2000

void asmVecdec(TAC* tac, char* asmString0, char* asmString1, char* tempString);
void asmVardec(TAC* tac, char* asmString0, char* asmString1, char* tempString);
void asmBeginFun(TAC* tac, char* asmString0, char* asmString1, char* tempString);
void asmReturn(TAC* tac, char* asmString0, char* asmString1, char* tempString);
void asmPrint(TAC* tac, char* asmString0, char* asmString1, char* tempString);
void asmAdd(TAC* tac, char* asmString0, char* asmString1, char* tempString);
void asmSub(TAC* tac, char* asmString0, char* asmString1, char* tempString);
void asmJump(TAC* tac, char* asmString0, char* asmString1, char* tempString);
void asmJmpFalse(TAC* tac, char* asmString0, char* asmString1, char* tempString);
char* generateAsm (TAC* last);

#endif
