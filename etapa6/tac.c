
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
      fprintf(stderr, "TAC_SYMBOL" ); //ignora pra q?
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
    case TAC_PARAM:
      //fprintf(stderr, "TAC_PARAM" ); //ignora
      break;
    case TAC_VARDEC:
      fprintf(stderr, "TAC_VARDEC" );
      break;
    case TAC_VECDEC:
      fprintf(stderr, "TAC_VECDEC" );
      break;
    case TAC_OR:
      fprintf(stderr, "TAC_OR" );
      break;
    case TAC_AND:
      fprintf(stderr, "TAC_AND" );
      break;
    case TAC_EQUAL:
      fprintf(stderr, "TAC_EQUAL" );
      break;
    case TAC_NOTEQUAL:
      fprintf(stderr, "TAC_NOTEQUAL" );
      break;
    case TAC_LESSEQUAL:
      fprintf(stderr, "TAC_LESSEQUAL" );
      break;
    case TAC_GREATEREQUAL:
      fprintf(stderr, "TAC_GREATEREQUAL" );
      break;
    case TAC_LESS:
      fprintf(stderr, "TAC_LESS" );
      break;
    case TAC_GREATER:
      fprintf(stderr, "TAC_GREATER" );
      break;
    case TAC_JMPFALSE:
      fprintf(stderr, "TAC_JMPFALSE" );
      break;
    case TAC_PRINTELEMENT:
      fprintf(stderr, "TAC_PRINTELEMENT" );
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
    //if (!(tac->type == TAC_SYMBOL || tac->type == TAC_PARAM)){
    if (1){//debug
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
}
void tacPrintForward(TAC* first)
{
  TAC* tac;
  fprintf(stderr, "\n   tacPrintForward\n" );
  for (tac = first; tac; tac=tac->next)
  {
    if (tac->type == TAC_SYMBOL || tac->type == TAC_PARAM){
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
}

TAC* tacReverse(TAC* last)
{// versao nova que cria uma copia das tacs na memoria
  if(!last) return 0;
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
  //TAC* tacIfz = tacCreate(TAC_IFZ, label,code0?code0->res:0, 0);
  TAC* tacLabel = tacCreate(TAC_LABEL, label,0, 0);
  TAC* tacJmpFalse = tacCreate(TAC_JMPFALSE, label, code0?code0->res:0, 0);
  //join order: code0 TAC_JMPFALSE code1 tacLabel
  return tacJoin(code0,tacJoin(tacJmpFalse,tacJoin(code1,tacLabel)));
}

TAC* tacMakeWhenElse(ASTREE* node, TAC* code0, TAC* code1, TAC* code2)
{
  HASH_NODE* elseLabel = makeLabel();
  HASH_NODE* endLabel = makeLabel();
  //TAC* tacIfz = tacCreate(TAC_IFZ, elseLabel,code0?code0->res:0, 0);
  TAC* tacJmpFalse = tacCreate(TAC_JMPFALSE, elseLabel,code0?code0->res:0, 0);
  TAC* tacElseLabel = tacCreate(TAC_LABEL, elseLabel,0, 0);
  TAC* tacJmp = tacCreate(TAC_JMP, endLabel, 0, 0);
  TAC* tacEndLabel = tacCreate(TAC_LABEL, endLabel,0, 0);
  //join order: code0 tacJmpFalse code1 tacJmp tacElseLabel code2 tacEndLabel
  return tacJoin(code0, tacJoin(tacJmpFalse, tacJoin(code1, tacJoin(tacJmp,
    tacJoin(tacElseLabel, tacJoin(code2, tacEndLabel))))));
}

TAC* tacMakeFor(ASTREE* node, TAC* code0, TAC* code1, TAC* code2)
{
  //for (son0 to son1) son2
  HASH_NODE* tempvar = makeTemporary();
  HASH_NODE* begginingLabel = makeLabel();
  HASH_NODE* endLabel = makeLabel();
  TAC* tacMov = tacCreate(TAC_MOV, node->symbol, code0?code0->res:0, 0);
  TAC* tacBegginingLabel = tacCreate(TAC_LABEL, begginingLabel,0, 0);
  TAC* tacSub = tacCreate(TAC_SUB, tempvar, code1?code1->res:0, node->symbol);
  TAC* tacIfn = tacCreate(TAC_IFN,endLabel,tempvar,0);
  TAC* tacInc = tacCreate(TAC_INC,node->symbol, node->symbol, 0);
  TAC* tacJmp = tacCreate(TAC_JMP, begginingLabel, 0, 0);
  TAC* tacEndLabel = tacCreate(TAC_LABEL, endLabel,0, 0);
  // join order: code0 mov code1 begginingLabel sub ifn code2 inc jmp endLabel
  return tacJoin(code0, tacJoin(tacMov, tacJoin(code1, tacJoin(tacBegginingLabel,
            tacJoin(tacSub, tacJoin(tacIfn, tacJoin(code2,
            tacJoin(tacInc, tacJoin(tacJmp, tacEndLabel)))))))));
}

TAC* tacOp(ASTREE* node, TAC* code0, TAC* code1)
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
    case ASTREE_OR:
      type = TAC_OR;
      break;
    case ASTREE_AND:
      type = TAC_AND;
      break;
    case ASTREE_EQUAL:
      type = TAC_EQUAL;
      break;
    case ASTREE_NOTEQUAL:
      type = TAC_NOTEQUAL;
      break;
    case ASTREE_LESSEQUAL:
      type = TAC_LESSEQUAL;
      break;
    case ASTREE_GREATEREQUAL:
      type = TAC_GREATEREQUAL;
      break;
    case ASTREE_LESS:
      type = TAC_LESS;
      break;
    case ASTREE_GREATER:
      type = TAC_GREATER;
      break;
  }

  HASH_NODE* temp = makeTemporary();
  TAC* tac = tacCreate(type,temp,code0?code0->res:0,code1?code1->res:0);
  return tacJoin(tacJoin(code0,code1),tac);
}

TAC* tacMakeFuncDec(ASTREE* node, TAC* code0, TAC* code1, TAC* code2)
{
  TAC* tacBeginFunc = tacCreate(TAC_BEGGINFUN, node->symbol, 0, 0);
  TAC* tacEndFunc = tacCreate(TAC_ENDFUN, node->symbol, 0, 0);

  //code0: vartype
  //join order:  beginFunc code1 code2 endFunc
  return tacJoin(tacBeginFunc, tacJoin(code1, tacJoin(code2, tacEndFunc)));
}

TAC* tacMakeParam(ASTREE* node)
{
  TAC* tacParam = tacCreate(TAC_PARAM, node->symbol, 0, 0);
  return tacParam;
}

TAC* tacMakeFuncCall(ASTREE* node, TAC* code0)
{
  //code0: expr
  HASH_NODE* tempvar = makeTemporary();
  TAC* tacCall = tacCreate(TAC_CALL, tempvar, node->symbol, 0);
  //tacArgsComplete(code0, node->symbol, 1);
  //join order: args call
  return tacJoin(code0, tacCall);
}

void tacArgsComplete(TAC* tac, HASH_NODE* func, int argIndex)
{
  if(!tac) return;
  if(tac->type == TAC_ARG  && tac->res==0 && tac->op2==0)
  {
    tac->res = (HASH_NODE*)argIndex;
    argIndex = argIndex + 1;
    tac->op2 = func;
  }
  tacArgsComplete(tac->prev, func, argIndex);
  return;
}

TAC* tacMakeArgs(ASTREE* node, TAC* son0)
{
  //o index e o HASH_NODE func sao completados dps
  TAC* tacArg = tacCreate(TAC_ARG, 0, son0?son0->res:0, 0);
  //join order: expr tacArg
  return tacJoin(son0, tacArg);
}

TAC* tacMakeWhile(ASTREE* node, TAC* code0, TAC* code1)
{
  HASH_NODE *beginLabel = makeLabel();
  HASH_NODE *endLabel = makeLabel();
  TAC* tacBeginLabel = tacCreate(TAC_LABEL, beginLabel,0, 0);
  TAC* tacEndLabel = tacCreate(TAC_LABEL, endLabel,0, 0);
  TAC* tacJmpFalse = tacCreate(TAC_JMPFALSE, endLabel, code0?code0->res:0, NULL);
  TAC* tacJmp = tacCreate(TAC_JMP, beginLabel,0,0);
  return tacJoin(tacBeginLabel,tacJoin(code0,tacJoin(tacJmpFalse,tacJoin(code1,tacJoin(tacJmp,tacEndLabel)))));
}

TAC* tacMakeBool(ASTREE* node, TAC* code0, TAC* code1)
{
  TAC* exprBool;

  switch (node->type){
    case ASTREE_OR:
    {
      HASH_NODE *temp = makeTemporary();
      TAC *result = tacCreate(TAC_OR, temp, code0?code0->res:0, code1?code1->res:0);
      exprBool = tacJoin(tacJoin(code0,code1),result);
    }
      break;

    case ASTREE_AND:
    {
      HASH_NODE *temp = makeTemporary();
      TAC *result = tacCreate(TAC_AND, temp, code0?code0->res:0, code1?code1->res:0);
      exprBool = tacJoin(tacJoin(code0,code1),result);
    }
      break;

    case ASTREE_EQUAL:
    {
      HASH_NODE *temp = makeTemporary();
      TAC *result = tacCreate(TAC_EQUAL, temp, code0?code0->res:0, code1?code1->res:0);
      exprBool = tacJoin(tacJoin(code0,code1),result);
    }
      break;

    case ASTREE_NOTEQUAL:
    {
      HASH_NODE *temp = makeTemporary();
      TAC *result = tacCreate(TAC_NOTEQUAL, temp, code0?code0->res:0, code1?code1->res:0);
      exprBool = tacJoin(tacJoin(code0,code1),result);
    }
      break;


    case ASTREE_LESSEQUAL:
    {
      HASH_NODE *temp = makeTemporary();
      TAC *result = tacCreate(TAC_LESSEQUAL, temp, code0?code0->res:0, code1?code1->res:0);
      exprBool = tacJoin(tacJoin(code0,code1),result);
    }
      break;

    case ASTREE_GREATEREQUAL:
    {
      HASH_NODE *temp = makeTemporary();
      TAC *result = tacCreate(TAC_GREATEREQUAL, temp, code0?code0->res:0, code1?code1->res:0);
      exprBool = tacJoin(tacJoin(code0,code1),result);
    }
      break;
    case ASTREE_LESS:
    {
      HASH_NODE *temp = makeTemporary();
      TAC *result = tacCreate(TAC_LESS, temp, code0?code0->res:0, code1?code1->res:0);
      exprBool = tacJoin(tacJoin(code0,code1),result);
    }
      break;

    case ASTREE_GREATER:
    {
      HASH_NODE *temp = makeTemporary();
      TAC *result = tacCreate(TAC_GREATER, temp, code0?code0->res:0, code1?code1->res:0);
      exprBool = tacJoin(tacJoin(code0,code1),result);
    }
      break;

  }

  return exprBool;
}

TAC* tacMakeVecWrite(ASTREE* node, TAC* code0, TAC* code1)
{
  TAC* tacVecwrite = tacCreate(TAC_VECWRITE, node->symbol, code0?code0->res:0, code1?code1->res:0);
  //join order: code0 code1 vecwrite
  return tacJoin(code0, tacJoin(code1, tacVecwrite));
}

TAC* tacMakeVecRead(ASTREE* node, TAC* code0)
{
  HASH_NODE* temp = makeTemporary();
  TAC* tacVecread = tacCreate(TAC_VECREAD, temp, node->symbol, code0?code0->res:0);
  //join order: code0 vecread
  return tacJoin(code0, tacVecread);
}

TAC* tacMakeVarDec(ASTREE* node, TAC* code0)
{
  if(node->symbol->nature == NATURE_VAR)
  {
    return tacJoin(code0, tacCreate(TAC_VARDEC, node->symbol, code0?code0->res:0, 0));
  }
  if(node->symbol->nature == NATURE_ARRAY)
  {
    return tacJoin(code0, tacCreate(TAC_VECDEC, node->symbol, code0?code0->res:0, node->son[0]->symbol));
  }
}

TAC* tacMakePrint(ASTREE* node, TAC* code0)
{
  //TAC* tacPrint = tacCreate(TAC_PRINT, code0?code0->res:0, 0, 0);
  TAC* tacPrint = tacCreate(TAC_PRINT, 0, 0, 0); //PRINT_ELEMENTs antes
  return tacJoin(code0, tacPrint);
}

TAC* tacMakeRead(ASTREE* node)
{
  TAC* tacRead = tacCreate(TAC_READ, node->symbol, 0, 0);
  return tacRead;
}

TAC* tacPrintList(ASTREE* node, TAC* code0, TAC* code1)
{
  TAC* result;
  if( !node->son[0] ){
    fprintf(stderr, "ERRO tacPrintList: n existe node->son[0]\n" );
  }
  if(node->son[0]->type == ASTREE_LITSTRING)
  {
    result = tacCreate(TAC_PRINTELEMENT, node->son[0]->symbol, 0, 0);
  }else{ // expr
    result = tacJoin( code0, tacCreate(TAC_PRINTELEMENT, code0?code0->res:0, 0, 0) );
  }
  if(code1->type == TAC_SYMBOL)
  {
    code1 = tacCreate(TAC_PRINTELEMENT, code1->res, 0, 0);
  }
  return tacJoin(code1, result);
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
  //fprintf(stderr, "\nDEBUG SEGMENTATION 1\n" );

  switch (node->type) {
    case ASTREE_INTLIST:
    case ASTREE_CHARLIST:
    case ASTREE_FLOATLIST:
      result = tacJoin(tacCreate(TAC_SYMBOL, node->symbol, 0, 0), code[0]);
      break;
    case ASTREE_KWCHAR:
    case ASTREE_KWINT:
    case ASTREE_KWREAL:
    case ASTREE_LITREAL:
    case ASTREE_LITCHAR:
    case ASTREE_LITINT:
    case ASTREE_TKID:
      result = tacCreate(TAC_SYMBOL, node->symbol, 0, 0);
      break;
    case ASTREE_LITSTRING: //so aparece no print
      result = tacCreate(TAC_PRINTELEMENT, node->symbol, 0, 0);
      break;
    case ASTREE_KWWHENTHEN:
      result = tacMakeWhen(node, code[0], code[1]);
      break;
    case ASTREE_KWWHENTHENELSE:
      result = tacMakeWhenElse(node, code[0], code[1], code[2]);
      break;
    case ASTREE_KWRETURN:
      result = tacJoin(code[0],tacCreate(TAC_RETURN, NULL, code[0]?code[0]->res:0, NULL));
      break;
    case ASTREE_KWFOR:
      result = tacMakeFor(node, code[0], code[1], code[2]);
      break;
    case ASTREE_KWWHILE:
      result =  tacMakeWhile(node, code[0], code[1]);
      break;
    case ASTREE_ADD:
    case ASTREE_SUB:
    case ASTREE_MULT:
    case ASTREE_DIV:
    case ASTREE_LESSEQUAL:
    case ASTREE_EQUAL:
    case ASTREE_GREATEREQUAL:
    case ASTREE_OR:
    case ASTREE_AND:
    case ASTREE_NOTEQUAL:
    case ASTREE_GREATER:
    case ASTREE_LESS:
      result = tacOp(node, code[0], code[1]);
      break;
    case ASTREE_FUNCDEC:
      result = tacMakeFuncDec(node, code[0], code[1], code[2]);
      break;
    case ASTREE_PARAM:
      result = tacMakeParam(node);
      break;
    case ASTREE_TKIDFUNC:
      result = tacMakeFuncCall(node, code[0]);
      break;
    case ASTREE_ARGS:
    case ASTREE_ARGSTAIL:
      //fprintf(stderr, "\nDEBUG\n" );
      result = tacJoin(tacMakeArgs(node, code[0]), code[1]);
      break;
    case ASTREE_ATRIB:
      result = tacJoin(code[0], tacCreate(TAC_MOV, node->symbol, code[0]?code[0]->res:0, 0));
      break;
    case ASTREE_ATRIBARRAY:
      result = tacMakeVecWrite(node, code[0], code[1]);
      break;
    case ASTREE_TKIDARRAY:
      result = tacMakeVecRead(node, code[0]);
      break;
    case ASTREE_VARDEC:
      result = tacMakeVarDec(node, code[0]);
      break;
    case ASTREE_KWPRINT:
      result = tacMakePrint(node, code[0]);
      break;
    case ASTREE_KWREAD:
      result = tacMakeRead(node);
      break;
    case ASTREE_PRINTLIST:
      fprintf(stderr, " DEBUG 11111\n");
      result = tacPrintList(node, code[0], code[1]);
      break;
    default:
      result = tacJoin( tacJoin( tacJoin(code[0], code[1]), code[2]), code[3]);
  }
  return result;
}
