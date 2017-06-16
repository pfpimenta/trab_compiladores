#ifndef TAC_H
#define TAC_H

#include "hash.h"
#include "astree.h"

#define TAC_RETURN
#define TAC_BEGGINFUN
#define TAC_ENDFUN
#define TAC_VECREAD
#define TAC_VECWRITE
#define TAC_MOV
#define TAC_SMP //???
#define TAC_READ
#define TAC_PRINT
#define TAC_ARG
#define TAC_CALL
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

TAC* tacCreate(int type, HASH_NODE* res, HASH_NODE* op1, HASH_NODE* op2);
TAC* tacJoin(TAC* code1, TAC* code2);
void tacPrintBack(TAC* last);
void tacPrintForward(TAC* first);
TAC* tacReverse(TAC* last);
TAC* tacGenerate(ASTREE* node);

#endif
