
#include "tac.h"
#include "astree.h"

int temporaryCount = 0;
int labelCount = 0;


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

TAC* tacGetFirst(TAC* tac)
{
  // get first tac of a tac chain
  if(!tac->prev)
  { //eh o primeiro tac
    return tac;
  }
  else
  { //ainda nao eh o primeiro tac
    return tacGetFirst(tac->prev);
  }
}

TAC* tacGetLast(TAC* tac)
{
  // get last tac of a tac chain
  if(!tac->next)
  { //eh o ultimo tac
    return tac;
  }
  else
  { //ainda nao eh o ultimo tac
    return tacGetLast(tac->next);
  }
}

TAC* tacJoin(TAC* code1, TAC* code2)
{
  TAC* tac;
  if (!code1) return code2;
  if (!code2) return code1;
  for(tac = code2; tac->prev; tac= tac->prev)
    ; //soh vai ate o inicio da lista
  tac->prev = code1;
  code1->next = tac;
  return code2;
}
void tacPrintBack(TAC* last)
{
  TAC* tac;
  fprintf(stderr, "\n   tacPrintBack\n" );
  for (tac = last; tac; tac=tac->prev)
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
      case TAC_IFZ:
        fprintf(stderr, "TAC_IFZ" );
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
  fprintf(stderr, "\n   tacPrintForward\n" );
  for (tac = first; tac; tac=tac->next)
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
      case TAC_IFZ:
        fprintf(stderr, "TAC_IFZ" );
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
{// versao nova que cria uma copia das tacs na memoria
  TAC* newTac;
  newTac = tacCreate(last->type, last->res, last->op1, last->op2);
  if(!last->prev)//lista c 1 elemento
  {
    return newTac;
  }
  else
  {
    return tacJoin(newTac, tacReverse(last->prev));
  }
}

HASH_NODE* makeLabel()
{

}
HASH_NODE* makeTemporary()
{

}

TAC* tacMakeWhen(ASTREE* node, TAC* code0, TAC* code1)
{
  HASH_NODE* label = makeLabel();
  tacIfz = tacCreate(TAC_IFZ, label,code0->res, 0);
  tacLabel = tacCreate(TAC_LABEL, label,0, 0);
  return tacJoin(code0,tacJoin(tacIfz,tacJoin(code1,tacLabel)));
}

TAC* tacMakeWhenElse(ASTREE* node, TAC* code0, TAC* code1, TAC* code2)
{
  HASH_NODE* elseLabel = makeLabel();
  HASH_NODE* endLabel = makeLabel();
  tacIfz = tacCreate(TAC_IFZ, elseLabel,code0->res, 0);
  tacElseLabel = tacCreate(TAC_LABEL, elseLabel,0, 0);
  tacJmp = tacCreate(TAC_JMP, endLabel, 0, 0);
  tacEndLabel = tacCreate(TAC_LABEL, endLabel,0, 0);
  return tacJoin(code0, tacJoin(tacIfz, tacJoin(code1, tacJoin(tacJmp,
    tacJoin(tacElseLabel, tacJoin(code2, tacEndLabel))))));
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
    case ASTREE_KWWHENTHEN:
      result = tacMakeWhen(node, code[0], code[1]);
      break;
    case ASTREE_KWWHENTHENELSE:
      result = tacMakeWhenElse(node, code[0], code[1], code[2]);
      break;
    default:
      result = tacJoin( tacJoin( tacJoin(code[0], code[1]), code[2]), code[3]);
  }
  return result;
}
