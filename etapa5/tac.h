#ifndef TAC_H
#define TAC_H

#include "hash.h"
#include "astree.h"

#define TAC_SYMBOL 1
#define TAC_RETURN 2
#define TAC_BEGGINFUN 3
#define TAC_ENDFUN 4
#define TAC_VECREAD 5
#define TAC_VECWRITE 6
#define TAC_MOV 7
#define TAC_READ 8
#define TAC_PRINT 9
#define TAC_ARG 10
#define TAC_CALL 11
#define TAC_IFZ 12 //jmp if zero
#define TAC_IFN 13 //jmp if negative
#define TAC_LABEL 14
#define TAC_JMP 15
#define TAC_SUB 16
#define TAC_ADD 17
#define TAC_MUL 18
#define TAC_DIV 19
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
void tacPrintBack(TAC* last);
void tacPrintForward(TAC* first);
TAC* tacReverse(TAC* last);
HASH_NODE* makeLabel();
HASH_NODE* makeTemporary();
TAC* tacMakeWhen(ASTREE* node, TAC* code0, TAC* code1);
TAC* tacMakeWhenElse(ASTREE* node, TAC* code0, TAC* code1, TAC* code2);
TAC* tacDeclaration(TAC* id, TAC* literal);
TAC* tacGenerate(ASTREE* node);
TAC* tacMakeFor(ASTREE* node, TAC* code0, TAC* code1, TAC* code2);
TAC* tacAritExpr(ASTREE* node, TAC* code0, TAC* code1);
#endif
