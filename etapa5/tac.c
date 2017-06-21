
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

void tacPrintType(TAC* tac)
{
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
    case TAC_IFN:
      fprintf(stderr, "TAC_IFN" );
      break;
    case TAC_LABEL:
      fprintf(stderr, "TAC_LABEL" );
      break;
    case TAC_JMP:
      fprintf(stderr, "TAC_JMP" );
      break;
    case TAC_SUB:
      fprintf(stderr, "TAC_SUB" );
      break;
    case TAC_ADD:
      fprintf(stderr, "TAC_ADD" );
      break;
    case TAC_MUL:
      fprintf(stderr, "TAC_MUL" );
      break;
    case TAC_DIV:
      fprintf(stderr, "TAC_DIV" );
      break;
    case TAC_INC:
      fprintf(stderr, "TAC_INC" );
      break;
    default:
      fprintf(stderr, "TAC_UNKNOWN: %i", tac->type );
      break;
  }
}

void tacPrintBack(TAC* last)
{
  TAC* tac;
  fprintf(stderr, "\n   tacPrintBack\n" );
  for (tac = last; tac; tac=tac->prev)
  {
    fprintf(stderr, "TAC(" );
    tacPrintType(tac);
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
    tacPrintType(tac);
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
  static int count = 0;
  char* labelName = (char*) calloc(1,sizeof(char));

  sprintf(labelName, "___label%d", count);
  count++;

  LINKED_LIST* linkedList = addSymbol(labelName, SYMBOL_TK_IDENTIFIER,0,0);
  HASH_NODE* hashNode;
  hashNode = &(linkedList->symbol);
  return hashNode;
}

HASH_NODE* makeTemporary()
{
  static int count = 0;
  char* tempName = (char*) calloc(1,sizeof(char));

  sprintf(tempName, "___temp%d", count);
  count++;

  LINKED_LIST* linkedList = addSymbol(tempName, SYMBOL_TK_IDENTIFIER,0,0);
  HASH_NODE* hashNode;
  hashNode = &(linkedList->symbol);
  return hashNode;
}

TAC* tacMakeWhen(ASTREE* node, TAC* code0, TAC* code1)
{
  HASH_NODE* label = makeLabel();
  TAC* tacIfz = tacCreate(TAC_IFZ, label,code0->res, 0);
  TAC* tacLabel = tacCreate(TAC_LABEL, label,0, 0);
  //join order: code0 tacIfz code1 tacLabel
  return tacJoin(code0,tacJoin(tacIfz,tacJoin(code1,tacLabel)));
}

TAC* tacMakeWhenElse(ASTREE* node, TAC* code0, TAC* code1, TAC* code2)
{
  HASH_NODE* elseLabel = makeLabel();
  HASH_NODE* endLabel = makeLabel();
  TAC* tacIfz = tacCreate(TAC_IFZ, elseLabel,code0->res, 0);
  TAC* tacElseLabel = tacCreate(TAC_LABEL, elseLabel,0, 0);
  TAC* tacJmp = tacCreate(TAC_JMP, endLabel, 0, 0);
  TAC* tacEndLabel = tacCreate(TAC_LABEL, endLabel,0, 0);
  //join order: code0 tacIfz code1 tacJmp tacElseLabel code2 tacEndLabel
  return tacJoin(code0, tacJoin(tacIfz, tacJoin(code1, tacJoin(tacJmp,
    tacJoin(tacElseLabel, tacJoin(code2, tacEndLabel))))));
}

TAC* tacMakeFor(ASTREE* node, TAC* code0, TAC* code1, TAC* code2)
{
  //for (son0 to son1) son2
  HASH_NODE* tempvar = makeTemporary();
  HASH_NODE* begginingLabel = makeLabel();
  HASH_NODE* endLabel = makeLabel();
  TAC* tacMov = tacCreate(TAC_MOV, node->symbol, code0->res, 0);
  TAC* tacBegginingLabel = tacCreate(TAC_LABEL, begginingLabel,0, 0);
  TAC* tacSub = tacCreate(TAC_SUB, tempvar, code1->res, node->symbol);
  TAC* tacIfz = tacCreate(TAC_IFZ,endLabel,tempvar,0);
  TAC* tacInc = tacCreate(TAC_INC,node->symbol, node->symbol, 0);
  TAC* tacJmp = tacCreate(TAC_JMP, begginingLabel, 0, 0);
  TAC* tacEndLabel = tacCreate(TAC_LABEL, endLabel,0, 0);
  // join order: code0 code1 mov begginingLabel sub ifz code2 inc jmp endLabel
  return tacJoin(code0, tacJoin(code1, tacJoin(tacMov, tacJoin(tacBegginingLabel,
            tacJoin(tacSub, tacJoin(tacIfz, tacJoin(code2,
            tacJoin(tacInc, tacJoin(tacJmp, tacEndLabel)))))))));
}

TAC* tacAritExpr(ASTREE* node, TAC* code0, TAC* code1)
{
  int type;

  switch (node->type){
    case ASTREE_ADD:
      type = TAC_ADD;
      break;
    case ASTREE_SUB:
      type = TAC_SUB;
      break;
    case ASTREE_MULT:
      type = TAC_MUL;
      break;
    case ASTREE_DIV:
      type = TAC_DIV;
      break;
  }

  HASH_NODE* temp = makeTemporary();
  TAC* tac = tacCreate(type,temp,code0->res,code1->res);
  return tacJoin(tacJoin(code0,code1),tac);
}

TAC* tacMakeFuncDec(ASTREE* node, TAC* code0, TAC* code1, TAC* code2)
{
  // MISTERIO
  TAC* tacBeginFunc = tacCreate(TAC_BEGGINFUN, node->symbol, 0, 0); // MISTERIO
  TAC* tacEndFunc = tacCreate(TAC_ENDFUN, node->symbol, 0, 0); // MISTERIO
  // MISTERIO

  //code0: vartype
  //join order:  beginFunc code1 code2 endFunc
  return tacJoin(tacBeginFunc, tacJoin(code1, tacJoin(code2, tacEndFunc)));
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
    case ASTREE_LITREAL:
    case ASTREE_LITCHAR:
    case ASTREE_LITINT:
    case ASTREE_TKID:
      result = tacCreate(TAC_SYMBOL, node->symbol, 0, 0);
      break;
    case ASTREE_KWWHENTHEN:
      result = tacMakeWhen(node, code[0], code[1]);
      break;
    case ASTREE_KWWHENTHENELSE:
      result = tacMakeWhenElse(node, code[0], code[1], code[2]);
      break;
    case ASTREE_KWRETURN:
      result = tacJoin(code[0],tacCreate(TAC_RETURN, NULL, code[0]->res, NULL));
      break;
    case ASTREE_KWFOR:
      result = tacMakeFor(node, code[0], code[1], code[2]);
      break;
    case ASTREE_ADD:
    case ASTREE_SUB:
    case ASTREE_MULT:
    case ASTREE_DIV:
      result = tacAritExpr(node, code[0], code[1]);
      break;
    case ASTREE_FUNCDEC:
      result = tacMakeFuncDec(node, code[0], code[1], code[2]);
      break;
    default:
      result = tacJoin( tacJoin( tacJoin(code[0], code[1]), code[2]), code[3]);
  }
  return result;
}
