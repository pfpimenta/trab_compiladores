#include "asm.h"

int printNumber = 0;
int boolLabelCount = 0;
int declaredTemps[200];

void initDeclaredTemps()
{
  int i;
  for(i = 0; i < 200; i++)
  {
    declaredTemps[i] = 0;
  }
}

void asmVecdec(TAC* tac, char* asmString0, char* asmString1, char* tempString)
{
  int vectorSize;
  int i;
  TAC* tacTemp;
  //fprintf(stderr, "DEBUG %s\n", tac->op2->text  ); //debug
  vectorSize = atoi(tac->op2->text);

  strcat(asmString0, "\n## TAC_VECDEC\n");
  if(! tac->op1) //se nao for inicializado
  {
    sprintf(tempString, "	.comm %s, %i, 32\n", tac->res->text, 4*vectorSize);
  }else{
    sprintf(tempString, "	.globl	%s\n	.type	%s, @object\n	.size	%s, %i\n%s:\n", tac->res->text,tac->res->text,tac->res->text,atoi(tac->op2->text)*4,tac->res->text);
    for(tacTemp = tac->prev; tacTemp->prev->type == TAC_SYMBOL; tacTemp = tacTemp->prev)
    {} // vai ate o primeiro TAC_SYMBOL
    for(tacTemp = tacTemp; tacTemp->type == TAC_SYMBOL; tacTemp = tacTemp->next)
    {
      if(tacTemp->res->type == SYMBOL_LIT_REAL)
      {
        strcat(tempString, "	.long ");
        strcat(tempString, "111111" );
        strcat(tempString, "\n");
      }else{
        if(tacTemp->res->type == SYMBOL_LIT_CHAR)
        {
          char* charValue[40];
          sprintf(charValue , "%d", tacTemp->res->text[1]);
          strcat(tempString, "	.byte ");
          strcat(tempString, charValue);
          strcat(tempString, "\n");
        }else{
          strcat(tempString, "	.long ");
          strcat(tempString, tacTemp->res->text );
          strcat(tempString, "\n");
        }
      }
    }
  }
  strcat(asmString0, tempString);
}

void asmVecWrite(TAC* tac, char* asmString0, char* asmString1, char* tempString)
{
  strcat(asmString1, "\n## TAC_VECWRITE\n");
  sprintf(tempString,"	movl	%s(%%rip), %%eax\n	movl	%%eax, %s+%i(%%rip)", tac->op1->text, tac->op2->text,  atoi(tac->op2->text)*4);
  strcat(asmString1, tempString);
}

void asmVecRead(TAC* tac, char* asmString0, char* asmString1, char* tempString)
{
  strcat(asmString1, "\n## TAC_VECREAD\n");
  sprintf(tempString,"	movl	%%eax, %s+%i(%%rip)\n	movl	%s(%%rip), %%eax", tac->op1->text, atoi(tac->op2->text)*4, tac->op2->text);
  strcat(asmString1, tempString);
}

void asmVardec(TAC* tac, char* asmString0, char* asmString1, char* tempString)
{
  strcat(asmString0, "\n## TAC_VARDEC\n");
  if(tac->op1->type == SYMBOL_LIT_REAL)
  {
    sprintf(tempString, "	.globl	%s\n	.type	%s, @object\n	.size	%s, 4\n%s:\n	.long	111111\n", tac->res->text,tac->res->text,tac->res->text,tac->res->text);
  }else{
    if(tac->op1->type == SYMBOL_LIT_CHAR)
    {
      char* charValue[40];
      sprintf(charValue , "%d", tac->op1->text[1]);
      sprintf(tempString, " .globl	%s\n .type	%s, @object\n .size	%s, 1\n%s:\n  .byte	%s\n",  tac->res->text,tac->res->text,tac->res->text,tac->res->text, charValue);

    }else{
      sprintf(tempString, "	.globl	%s\n	.type	%s, @object\n	.size	%s, 4\n%s:\n	.long	%s\n", tac->res->text,tac->res->text,tac->res->text,tac->res->text, tac->op1->text);
    }
  }
  strcat(asmString0, tempString);
}

void asmBeginFun(TAC* tac, char* asmString0, char* asmString1, char* tempString)
{
  strcat(asmString1, "\n## TAC_BEGGINFUN\n");
  sprintf(tempString,"	.globl	%s\n	.type	%s, @function\n%s:\n	pushq	%%rbp\n	movq	%%rsp, %%rbp\n",tac->res->text,tac->res->text,tac->res->text);
  strcat(asmString1, tempString);
}

void asmReturn(TAC* tac, char* asmString0, char* asmString1, char* tempString)
{
  char* charValue[40];
  strcat(asmString1, "\n## TAC_RETURN\n");
  sprintf(charValue , "%d", tac->op1->text);
  sprintf(tempString, "	movl	$%s, %%eax",charValue);
  strcat(asmString1, tempString);
}

void asmPrint(TAC* tac, char* asmString0, char* asmString1, char* tempString)
{
  strcat(asmString1, "\n## TAC_PRINT\n");
  sprintf(tempString,".LC%d:\n	.string	%s\n",printNumber,tac->res->text);
  strcat(asmString0, tempString);
  sprintf(tempString,"	movl	$.LC%d, %%edi\n	movl	$0, %%eax\n	call	printf\n",printNumber);
  strcat(asmString1, tempString);
  printNumber++;
}

void asmRead(TAC* tac, char* asmString0, char* asmString1, char* tempString)
{
  strcat(asmString1, "\n## TAC_READ\n");
  if(tac->res->dataType == DATATYPE_FLOAT || tac->res->dataType == DATATYPE_DOUBLE )
  sprintf(tempString,".LC%d:\n	.string	\"%%f\"\n",printNumber);
  else
  sprintf(tempString,".LC%d:\n	.string	\"%%d\"\n",printNumber);
  strcat(asmString0, tempString);
  sprintf(tempString,"	movl	$%s, %%esi\n	movl	$.LC%d, %%edi\n	movl	$0, %%eax\n	call	__isoc99_scanf\n",tac->res->text,printNumber);
  strcat(asmString1, tempString);
  printNumber++;
}

void asmDeclareTemp(TAC* tac, char* asmString0, char* asmString1, char* tempString)
{
  int index ;
  if(tac->res){
    if(tac->res->text[0] == '_')
    {
      index = tac->res->text[7] - '0';
      if(declaredTemps[9]==1){
        index = (tac->res->text[8] - '0') + 10;
      }
      if(declaredTemps[index] == 0)
      {
        declaredTemps[index] = 1;
        sprintf(tempString, "	.comm	%s,4,4\n", tac->res->text);
        strcat(asmString0, tempString);
      }
    }
  }
  if(tac->op1){
    if(tac->op1->text[0] == '_')
    {
      index = tac->op1->text[7] - '0';
      if(declaredTemps[9]==1){
        index = (tac->op1->text[8] - '0') + 10;
      }
      if(declaredTemps[index] == 0)
      {
        sprintf(tempString, "	.comm	%s,4,4\n", tac->op1->text);
        strcat(asmString0, tempString);
      }
    }
  }
  if(tac->op2){
    if(tac->op2->text[0] == '_')
    {
      index = tac->op2->text[7] - '0';
      if(declaredTemps[9]==1){
        index = (tac->op2->text[8] - '0') + 10;
      }
      if(declaredTemps[index] == 0)
      {
        sprintf(tempString, "	.comm	%s,4,4\n", tac->op2->text);
        strcat(asmString0, tempString);
      }
    }
  }
}

void asmAdd(TAC* tac, char* asmString0, char* asmString1, char* tempString)
{
  strcat(asmString1, "\n## TAC_ADD\n");
  setOperandos(tac, asmString0, asmString1, tempString);
  if(tac->op1 && tac->op2 && tac->res){
    sprintf(tempString, "\taddl	%%edx, %%eax\n	movl	%%eax, %s(%%rip)\n", tac->op2->text, tac->res->text);
    strcat(asmString1, tempString);
  }else{
    fprintf(stderr, "ERRO que nao deveria acontecer: asmAdd\n" );
  }

}

void asmSub(TAC* tac, char* asmString0, char* asmString1, char* tempString)
{
  strcat(asmString1, "\n## TAC_SUB\n");
  setOperandos(tac, asmString0, asmString1, tempString);
  if(tac->op1 && tac->op2 && tac->res){
    sprintf(tempString, "\tsubl	%%eax, %%edx\n  	movl	%%edx, %%eax\n  	movl	%%eax, %s(%%rip)\n", tac->res->text);
    strcat(asmString1, tempString);
  }else{
    fprintf(stderr, "ERRO que nao deveria acontecer: asmSub\n" );
  }

}

void asmMul(TAC* tac, char* asmString0, char* asmString1, char* tempString)
{
  strcat(asmString1, "\n## TAC_MUL\n");
  setOperandos(tac, asmString0, asmString1, tempString);
  if(tac->op1 && tac->op2 && tac->res){
    sprintf(tempString, "\timull	%%edx, %%eax\n	movl	%%eax, %s(%%rip)\n", tac->res->text);
    strcat(asmString1, tempString);
  }else{
    fprintf(stderr, "ERRO que nao deveria acontecer: asmMul\n" );
  }

}

void asmDiv(TAC* tac, char* asmString0, char* asmString1, char* tempString)
{
  strcat(asmString1, "\n## TAC_DIV\n");
  if(tac->op1 && tac->op2 && tac->res){
      //setando operandos
      if(isdigit(tac->op1->text[0]) && isdigit(tac->op2->text[0]))
      {
        int divValue = atoi(tac->op1->text) / atoi(tac->op2->text);
        fprintf(stderr, "\ndebug %i\n", divValue);
        sprintf(tempString, "\tmovl	$%i,%s(%%rip)\n", divValue, tac->res->text);
        strcat(asmString1, tempString);
      }else if(isdigit(tac->op1->text[0]))
      {

      }else if(isdigit(tac->op2->text[0]))
      {
        sprintf(tempString, "\tmovl	$%s, %%ecx\n", tac->op2->text);
        strcat(asmString1, tempString);

      }else{ // nenhum valor imediato
        sprintf(tempString, "\tmovl	%s(%%rip), %%ecx\n", tac->op2->text);
        strcat(asmString1, tempString);
      }
  }else{
    fprintf(stderr, "ERRO que nao deveria acontecer: asmDiv\n" );
  }

}

void asmParam(TAC* tac, char* asmString0, char* asmString1, char* tempString)
{
  strcat(asmString0, "\n## TAC_PARAM\n");
  sprintf(tempString, "	.comm	%s,4,4\n", tac->res->text);
  strcat(asmString0, tempString);
}

void asmLabel(TAC* tac, char* asmString0, char* asmString1, char* tempString)
{
  strcat(asmString1, "\n## TAC_LABEL\n");
  sprintf(tempString, ".%s:\n", tac->res->text);
  strcat(asmString1, tempString);
}

void asmMov(TAC* tac, char* asmString0, char* asmString1, char* tempString)
{
  strcat(asmString1, "\n## TAC_MOV\n");
  //if(tac->op1->text[0] >= '0' && tac->op1->text[0] <= '9')
  if(isdigit(tac->op1->text[0]))
  {
    sprintf(tempString, "	movl	$%s, %s(%%rip)\n", tac->op1->text, tac->res->text);
  }else{
    sprintf(tempString, "	movl	%s(%%rip), %%eax\n  movl	%%eax, %s(%%rip)\n", tac->op1->text, tac->res->text);
  }
  strcat(asmString1, tempString);
}

void asmIFN(TAC* tac, char* asmString0, char* asmString1, char* tempString)
{
  strcat(asmString1, "\n## TAC_IFN\n");
  sprintf(tempString, "	movl	%s(%%rip), %%eax\n	testl	%%eax, %%eax\n	js	.%s", tac->op1->text, tac->res->text);
  strcat(asmString1, tempString);
}

void asmIFZ(TAC* tac, char* asmString0, char* asmString1, char* tempString)
{
  strcat(asmString1, "\n## TAC_IFZ\n");
  sprintf(tempString, "	movl	%s(%%rip), %%eax\n	testl	%%eax, %%eax\n	je	.%s", tac->op1->text, tac->res->text);
  strcat(asmString1, tempString);
}

void asmCall(TAC* tac, char* asmString0, char* asmString1, char* tempString)
{
  strcat(asmString1, "\n## TAC_CALL\n");
  sprintf(tempString, "	movl	$0, %%eax\ncall	%s\n	movl	%%eax, %s(%%rip)\n", tac->op1->text, tac->res->text);
  strcat(asmString1, tempString);
}

void asmInc(TAC* tac, char* asmString0, char* asmString1, char* tempString)
{
  strcat(asmString1, "\n## TAC_INC\n");
  sprintf(tempString, "	movl	%s(%%rip), %%eax\n	addl	$1, %%eax\n	movl	%%eax, %s(%%rip)\n", tac->res->text, tac->res->text);
  strcat(asmString1, tempString);
}

void asmJump(TAC* tac, char* asmString0, char* asmString1, char* tempString)
{
  strcat(asmString1, "\n## TAC_JUMP\n");
  sprintf(tempString, "	jmp .%s\n", tac->res->text);
  strcat(asmString1, tempString);
}

void asmJmpFalse(TAC* tac, char* asmString0, char* asmString1, char* tempString)
{
  strcat(asmString1, "\n## TAC_JMPFALSE\n");
  sprintf(tempString, "	movl	%s(%%rip), %%eax\n	testl	%%eax, %%eax\n	je	.%s\n", tac->op1->text, tac->res->text);
  strcat(asmString1, tempString);
}

void boolExpressionResult(TAC* tac, char* asmString1, char* tempString)
{
  sprintf(tempString, ".boolLabelTrue_%i:\n	movl	$1,%s(%%rip)\n\tjmp .boolLabelEnd_%i\n", boolLabelCount, tac->res->text, boolLabelCount );
  strcat(asmString1, tempString);
  sprintf(tempString, ".boolLabelFalse_%i:\n	movl	$0,%s(%%rip)\n.boolLabelEnd_%i:\n", boolLabelCount, tac->res->text, boolLabelCount);
  strcat(asmString1, tempString);
  boolLabelCount += 1;
}

void setOperandos(TAC* tac, char* asmString0, char* asmString1, char* tempString)
{
  //bota op1 no edx e o op2 no eax
  if(isdigit(tac->op1->text[0]))
  {
    sprintf(tempString, "\tmovl	$%s, %%edx\n", tac->op1->text);
    strcat(asmString1, tempString);
  }else{
    sprintf(tempString, "\tmovl	%s(%%rip), %%edx\n", tac->op1->text);
    strcat(asmString1, tempString);
  }
  if(isdigit(tac->op2->text[0]))
  {
    sprintf(tempString, "\tmovl	$%s, %%eax\n", tac->op2->text);
    strcat(asmString1, tempString);

  }else{
    sprintf(tempString, "\tmovl	%s(%%rip), %%eax\n", tac->op2->text);
    strcat(asmString1, tempString);
  }
}

void asmEqual(TAC* tac, char* asmString0, char* asmString1, char* tempString)
{
  strcat(asmString1, "\n## TAC_EQUAL\n");
  setOperandos(tac, asmString0, asmString1, tempString);
  sprintf(tempString, "\tcmpl %%eax, %%edx\n\tje .boolLabelTrue_%i\n\tjmp .boolLabelFalse_%i\n", boolLabelCount, boolLabelCount);
  strcat(asmString1, tempString);
  boolExpressionResult(tac, asmString1, tempString);
}


void asmNotEqual(TAC* tac, char* asmString0, char* asmString1, char* tempString)
{
  strcat(asmString1, "\n## TAC_NOTEQUAL\n");
  setOperandos(tac, asmString0, asmString1, tempString);
  sprintf(tempString, "\tcmpl %%eax, %%edx\n\tjne .boolLabelTrue_%i\n\tjmp .boolLabelFalse_%i\n", boolLabelCount, boolLabelCount);
  strcat(asmString1, tempString);
  boolExpressionResult(tac, asmString1, tempString);
}

void asmLess(TAC* tac, char* asmString0, char* asmString1, char* tempString)
{
  strcat(asmString1, "\n## TAC_NOTEQUAL\n");
  setOperandos(tac, asmString0, asmString1, tempString);
  sprintf(tempString, "\tcmpl %%eax, %%edx\n\tjge .boolLabelFalse_%i\n\tjmp .boolLabelTrue_%i\n", boolLabelCount, boolLabelCount);
  strcat(asmString1, tempString);
  boolExpressionResult(tac, asmString1, tempString);
}

void asmGreater(TAC* tac, char* asmString0, char* asmString1, char* tempString)
{
  strcat(asmString1, "\n## TAC_NOTEQUAL\n");
  setOperandos(tac, asmString0, asmString1, tempString);
  sprintf(tempString, "\tcmpl %%eax, %%edx\n\tjle .boolLabelFalse_%i\n\tjmp .boolLabelTrue_%i\n", boolLabelCount, boolLabelCount);
  strcat(asmString1, tempString);
  boolExpressionResult(tac, asmString1, tempString);
}

void asmGreaterEqual(TAC* tac, char* asmString0, char* asmString1, char* tempString)
{
  strcat(asmString1, "\n## TAC_GREATEREQUAL\n");
  setOperandos(tac, asmString0, asmString1, tempString);
  sprintf(tempString, "\tcmpl %%eax, %%edx\n\tjl .boolLabelFalse_%i\n\tjmp .boolLabelTrue_%i\n", boolLabelCount, boolLabelCount);
  strcat(asmString1, tempString);
  boolExpressionResult(tac, asmString1, tempString);
}

void asmLessEqual(TAC* tac, char* asmString0, char* asmString1, char* tempString)
{
  strcat(asmString1, "\n## TAC_LESSEQUAL\n");
  setOperandos(tac, asmString0, asmString1, tempString);
  sprintf(tempString, "\tcmpl %%eax, %%edx\n\tjg .boolLabelFalse_%i\n\tjmp .boolLabelTrue_%i\n", boolLabelCount, boolLabelCount);
  strcat(asmString1, tempString);
  boolExpressionResult(tac, asmString1, tempString);
}

void asmOr(TAC* tac, char* asmString0, char* asmString1, char* tempString)
{
  strcat(asmString1, "\n## TAC_OR\n");
  setOperandos(tac, asmString0, asmString1, tempString);
  sprintf(tempString, "\tcmpl $1,%%eax\n\tje .boolLabelTrue_%i\n\tcmpl $1,%%edx\n\tje .boolLabelTrue_%i\n\tjmp .boolLabelFalse_%i\n", boolLabelCount, boolLabelCount, boolLabelCount);
  strcat(asmString1, tempString);
  boolExpressionResult(tac, asmString1, tempString);
}

void asmAnd(TAC* tac, char* asmString0, char* asmString1, char* tempString)
{
  strcat(asmString1, "\n## TAC_AND\n");
  setOperandos(tac, asmString0, asmString1, tempString);
  sprintf(tempString, "\tcmpl $0,%%eax\n\tje .boolLabelFalse_%i\n\tcmpl $0,%%edx\n\tje .boolLabelFalse_%i\n\tjmp .boolLabelTrue_%i\n", boolLabelCount, boolLabelCount, boolLabelCount);
  strcat(asmString1, tempString);
  boolExpressionResult(tac, asmString1, tempString);
}

char* generateAsm (TAC* first)
{
  //recebe uma corrente de TACs
  // e gera uma string
  // que eh o programa em assembly
  char* asmString0[ASM_STRING_SIZE]; //declaracoes assembly
  char* asmString1[ASM_STRING_SIZE];
  char* tempString[ASM_STRING_SIZE];

  strcat(asmString0, "###\n### string0\n	.data\n");
  strcat(asmString1, "###\n### string1\n	.text\n");


  strcat(asmString1, "	.file	\"testProgram.c\"\n");

  initDeclaredTemps();

  TAC* tac;
  for (tac = first; tac; tac= tac->next)
  {
    //fprintf(stderr, "debug %i\n", tac->type );
    if(tac->type != TAC_LABEL)
    asmDeclareTemp(tac, asmString0, asmString1, tempString);
    switch (tac->type) {
      case TAC_SYMBOL:
          //ignora
          break;
      case TAC_VARDEC:
          asmVardec(tac, asmString0, asmString1, tempString);
          break;
      case TAC_VECDEC:
          asmVecdec(tac, asmString0, asmString1, tempString);
          break;
      case TAC_RETURN:
          asmReturn(tac, asmString0, asmString1, tempString);
          break;
      case TAC_BEGGINFUN:
          asmBeginFun(tac, asmString0, asmString1, tempString);
          break;
      case TAC_ENDFUN:
          strcat(asmString1, "\n## TAC_ENDFUN\n");
          strcat(asmString1,"	popq	%rbp\n	ret\n	leave\n");
          break;
      case TAC_VECREAD:
          asmVecRead(tac, asmString0, asmString1, tempString);
          break;
      case TAC_VECWRITE:
          asmVecWrite(tac, asmString0, asmString1, tempString);
          break;
      case TAC_MOV:
          //asmDeclareTemp(tac, asmString0, asmString1, tempString);
          asmMov(tac, asmString0, asmString1, tempString);
          break;
      case TAC_READ:
          strcat(asmString0, "\n## TAC_READ\n");
          asmRead(tac, asmString0, asmString1, tempString);
          break;
      case TAC_PRINT:
          strcat(asmString0, "\n## TAC_PRINT\n");
          asmPrint(tac, asmString0, asmString1, tempString);
          break;
      case TAC_ARG:
          //asmDeclareTemp(tac, asmString0, asmString1, tempString);
          break;
      case TAC_CALL:
          //asmDeclareTemp(tac, asmString0, asmString1, tempString);
          asmCall(tac, asmString0, asmString1, tempString);
          break;
      case TAC_IFZ:
          asmIFZ(tac, asmString0, asmString1, tempString);
          break;
      case TAC_IFN:
          asmIFN(tac, asmString0, asmString1, tempString);
          break;
      case TAC_LABEL:
          asmLabel(tac, asmString0, asmString1, tempString);
          break;
      case TAC_JMP:
          asmJump(tac, asmString0, asmString1, tempString);
          break;
      case TAC_SUB:
          //asmDeclareTemp(tac, asmString0, asmString1, tempString);
          asmSub(tac, asmString0, asmString1, tempString);
          break;
      case TAC_ADD:
          //asmDeclareTemp(tac, asmString0, asmString1, tempString);
          asmAdd(tac, asmString0, asmString1, tempString);
          break;
      case TAC_MUL:
          //asmDeclareTemp(tac, asmString0, asmString1, tempString);
          asmMul(tac, asmString0, asmString1, tempString);
          break;
      case TAC_DIV:
          //asmDeclareTemp(tac, asmString0, asmString1, tempString);
          asmMul(tac, asmString0, asmString1, tempString);
          break;
      case TAC_INC:
          //asmDeclareTemp(tac, asmString0, asmString1, tempString);
          asmInc(tac, asmString0, asmString1, tempString);
          break;
      case TAC_PARAM:
          //todas variaveis sao globaiss
          asmParam(tac, asmString0, asmString1, tempString);
          break;
      case TAC_OR:
          asmOr(tac, asmString0, asmString1, tempString);
          break;
      case TAC_EQUAL:
          asmEqual(tac, asmString0, asmString1, tempString);
          break;
      case TAC_NOTEQUAL:
          asmNotEqual(tac, asmString0, asmString1, tempString);
          break;
      case TAC_LESSEQUAL:
          asmLessEqual(tac, asmString0, asmString1, tempString);
          break;
      case TAC_GREATEREQUAL:
          asmGreaterEqual(tac, asmString0, asmString1, tempString);
          break;
      case TAC_LESS:
          asmLess(tac, asmString0, asmString1, tempString);
          break;
      case TAC_GREATER:
          asmGreater(tac, asmString0, asmString1, tempString);
          break;
      case TAC_AND:
          asmAdd(tac, asmString0, asmString1, tempString);
          break;
      case TAC_JMPFALSE:
          asmJmpFalse(tac, asmString0, asmString1, tempString);
          break;
      default:
        fprintf(stderr, "\nERRO que nao era pra acontecer: generateAsm()\n" );
        break;
      }
  }



    strcat(asmString1,"	.ident	\"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.3) 4.8.4\"\n" );
    strcat(asmString1,"	.section	.note.GNU-stack,\"\",@progbits\n");

    strcat(asmString0,asmString1);

    return asmString0;
}
