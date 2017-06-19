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