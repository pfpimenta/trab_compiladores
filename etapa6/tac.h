#ifndef TAC_H
#define TAC_H

#include "hash.h"
#include "astree.h"

#define TAC_SYMBOL 1
#define TAC_RETURN 2 // op1: var a ser retornada
#define TAC_BEGGINFUN 3
#define TAC_ENDFUN 4
#define TAC_VECREAD 5
#define TAC_VECWRITE 6
#define TAC_MOV 7 // res := op1
#define TAC_READ 8 // res: var de input
#define TAC_PRINT 9 // res:expr
#define TAC_ARG 10 // res:var, op1:index, op2:func
#define TAC_CALL 11 // op1=f, res=res
#define TAC_IFZ 12 //jmp if zero
#define TAC_IFN 13 //jmp if negative
#define TAC_LABEL 14
#define TAC_JMP 15
#define TAC_SUB 16 // res = op1 - op2
#define TAC_ADD 17
#define TAC_MUL 18
#define TAC_DIV 19
#define TAC_INC 20 // res = op1 + 1
#define TAC_PARAM 21 // res eh a variavel do parametro
#define TAC_VARDEC 22 // res:var op1:valor
#define TAC_VECDEC 23 // res:var op1:expr op2:valor
#define TAC_OR 24
#define TAC_EQUAL 25
#define TAC_NOTEQUAL 26
#define TAC_LESSEQUAL 27
#define TAC_GREATEREQUAL 28
#define TAC_LESS 29
#define TAC_GREATER 30
#define TAC_AND 31

//codigo aqui

typedef struct tac_struct
{
	int type;
  HASH_NODE* res;
  HASH_NODE* op1;
  HASH_NODE* op2;
  struct tac_struct* prev;
  struct tac_struct* next;
} TAC;

TAC* tacGetFirst(TAC* tac);
TAC* tacGetLast(TAC* tac);
TAC* tacCreate(int type, HASH_NODE* res, HASH_NODE* op1, HASH_NODE* op2);
TAC* tacJoin(TAC* code1, TAC* code2);
void tacPrintType(TAC* tac);
void tacPrintBack(TAC* last);
void tacPrintForward(TAC* first);
TAC* tacReverse(TAC* last);
HASH_NODE* makeLabel();
HASH_NODE* makeTemporary();
TAC* tacMakeWhen(ASTREE* node, TAC* code0, TAC* code1);
TAC* tacMakeWhenElse(ASTREE* node, TAC* code0, TAC* code1, TAC* code2);
TAC* tacDeclaration(TAC* id, TAC* literal);
TAC* tacMakeFor(ASTREE* node, TAC* code0, TAC* code1, TAC* code2);
TAC* tacOp(ASTREE* node, TAC* code0, TAC* code1);
TAC* tacMakeFuncDec(ASTREE* node, TAC* code0, TAC* code1, TAC* code2);
TAC* tacMakeParam(ASTREE* node);
TAC* tacMakeFuncCall(ASTREE* node, TAC* son0);
void tacArgsComplete(TAC* tac, HASH_NODE* func, int argIndex);
TAC* tacMakeArgs(ASTREE* node, TAC* son0);
TAC* tacMakeWhile(ASTREE* node, TAC* code0, TAC* code1);
TAC* tacMakeVecWrite(ASTREE* node, TAC* code0, TAC* code1);
TAC* tacMakeVecRead(ASTREE* node, TAC* code0);
TAC* tacMakeVarDec(ASTREE* node, TAC* code0);
TAC* tacMakePrint(ASTREE* node, TAC* code0);
TAC* tacGenerate(ASTREE* node);
#endif
