
#include "tac.h"
#include "astree.h"


TAC* tacCreate(int type, HASH_NODE* res, HASH_NODE* op1, HASH_NODE* op2)
{
  TAC* newtac;
  newtac = (TAC*) calloc(1,sizeof(TAC));
  newtac->type = type;
  newtac->res = res;
  newtac->op1 = op1;
  newtac->op2 = op2;
  newtac->prev = 0;
  newtac->next = 0;
  return newtac;
}

TAC* tacJoin(TAC* code1, TAC* code2)
{
  TAC* tac;
  if (!code1) return code2;
  if (!code2) return code1;
  for(tac = code2; tac->prev; tac= tac->prev)
    ; //soh vai ate o inicio da lista
  tac->prev = code1;
  return code2;
}
void tacPrintBack(TAC* last)
{
  TAC* tac;
  for (tac = last; tac; tac->prev)
  {
    fprintf(stderr, "TAC(" );
    switch (tac->type) {
      case TAC_SYMBOL:
        fprintf(stderr, "TAC_SYMBOL" );
        break;
      case TAC_RETURN:
        fprintf(stderr, "TAC_RETURN" );
        break;
      case TAC_BEGGINFUN:
        fprintf(stderr, "TAC_BEGGINFUN" );
        break;
      case TAC_ENDFUN:
        fprintf(stderr, "TAC_ENDFUN" );
        break;
      case TAC_VECREAD:
        fprintf(stderr, "TAC_VECREAD" );
        break;
      case TAC_VECWRITE:
        fprintf(stderr, "TAC_VECWRITE" );
        break;
      case TAC_MOV:
        fprintf(stderr, "TAC_MOV" );
        break;
      case TAC_READ:
        fprintf(stderr, "TAC_READ" );
        break;
      case TAC_PRINT:
        fprintf(stderr, "TAC_PRINT" );
        break;
      case TAC_ARG:
        fprintf(stderr, "TAC_ARG" );
        break;
      case TAC_CALL:
        fprintf(stderr, "TAC_CALL" );
        break;
      default:
        fprintf(stderr, "TAC_UNKNOWN" );
        break;
    }
    if(tac->res)
    {
      fprintf(stderr,",%s", tac->res->text);
    }else{
      fprintf(stderr, ", ");
    }
    if(tac->op1)
    {
      fprintf(stderr,",%s", tac->op1->text);
    }else{
      fprintf(stderr, ", ");
    }
    if(tac->op2)
    {
      fprintf(stderr,",%s", tac->op2->text);
    }else{
      fprintf(stderr, ", ");
    }
    fprintf(stderr, ")\n" );
  }
}
void tacPrintForward(TAC* first)
{
  TAC* tac;
  for (tac = first; tac; tac->next)
  {
    fprintf(stderr, "TAC(" );
    switch (tac->type) {
      case TAC_SYMBOL:
        fprintf(stderr, "TAC_SYMBOL" );
        break;
      case TAC_RETURN:
        fprintf(stderr, "TAC_RETURN" );
        break;
      case TAC_BEGGINFUN:
        fprintf(stderr, "TAC_BEGGINFUN" );
        break;
      case TAC_ENDFUN:
        fprintf(stderr, "TAC_ENDFUN" );
        break;
      case TAC_VECREAD:
        fprintf(stderr, "TAC_VECREAD" );
        break;
      case TAC_VECWRITE:
        fprintf(stderr, "TAC_VECWRITE" );
        break;
      case TAC_MOV:
        fprintf(stderr, "TAC_MOV" );
        break;
      case TAC_READ:
        fprintf(stderr, "TAC_READ" );
        break;
      case TAC_PRINT:
        fprintf(stderr, "TAC_PRINT" );
        break;
      case TAC_ARG:
        fprintf(stderr, "TAC_ARG" );
        break;
      case TAC_CALL:
        fprintf(stderr, "TAC_CALL" );
        break;
      default:
        fprintf(stderr, "TAC_UNKNOWN" );
        break;
    }
    if(tac->res)
    {
      fprintf(stderr,",%s", tac->res->text);
    }else{
      fprintf(stderr, ", ");
    }
    if(tac->op1)
    {
      fprintf(stderr,",%s", tac->op1->text);
    }else{
      fprintf(stderr, ", ");
    }
    if(tac->op2)
    {
      fprintf(stderr,",%s", tac->op2->text);
    }else{
      fprintf(stderr, ", ");
    }
    fprintf(stderr, ")\n" );
  }
}

TAC* tacReverse(TAC* last)
{
  TAC* temp;
  if(!last->prev) return last; //lista c 1 elemento

  temp = last->prev;
  last->prev->next = 0;
  last->prev = 0;

  return tacJoin(last, tacReverse(temp));
}

TAC* tacGenerate(ASTREE* node){
  int i = 0;
  TAC* code[MAX_SONS];
  TAC* result = 0;

  if (!node) return 0;

  //process children first
  for(i=0; i<MAX_SONS; ++i)
  {
    code[i] = tacGenerate(node->son[i]);
  }
  switch (node->type) {
    case ASTREE_TKID:
      result = tacCreate(TAC_SYMBOL, node->symbol, 0, 0);
      break;
    default:
      result = tacJoin( tacJoin( tacJoin(code[0], code[1]), code[2]), code[3]);
  }
  return result;
}
