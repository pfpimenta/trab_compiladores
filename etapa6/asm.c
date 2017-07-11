#include "asm.h"

int printNumber = 0;
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
    sprintf(tempString, "");
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

void asmDeclareTemp(TAC* tac, char* asmString0, char* asmString1, char* tempString)
{
  int index ;
  if(tac->res->text[0] == '_')
  {
    index = tac->res->text[7] - '0';
    if(declaredTemps[8]==1){
      index = (tac->res->text[8] - '0') + 10;
    }
    if(declaredTemps[index] == 0)
    {
      declaredTemps[index] = 1;
      sprintf(tempString, "	.comm	%s,4,4\n", tac->res->text);
      strcat(asmString0, tempString);
    }
  }
  if(tac->op1->text[0] == '_')
  {
    index = tac->op1->text[7] - '0';
    if(declaredTemps[8]==1){
      index = (tac->res->text[8] - '0') + 10;
    }
    if(declaredTemps[index] == 0)
    {
      sprintf(tempString, "	.comm	%s,4,4\n", tac->op1->text);
      strcat(asmString0, tempString);
    }
  }
  if(tac->op2->text[0] == '_')
  {
    index = tac->op2->text[7] - '0';
    if(declaredTemps[8]==1){
      index = (tac->res->text[8] - '0') + 10;
    }
    if(declaredTemps)
    if(declaredTemps[index] == 0)
    {
      sprintf(tempString, "	.comm	%s,4,4\n", tac->op2->text);
      strcat(asmString0, tempString);
    }
  }
}

void asmAdd(TAC* tac, char* asmString0, char* asmString1, char* tempString)
{
  strcat(asmString1, "\n## TAC_ADD\n");
  if(tac->op1 && tac->op2 && tac->res){
    sprintf(tempString, "	movl	%s(%%rip), %%edx\n", tac->op1->text);
    strcat(asmString1, tempString);
    sprintf(tempString, "	movl	%s(%%rip), %%eax\n	addl	%%edx, %%eax\n	movl	%%eax, %s(%%rip)\n", tac->op2->text, tac->res->text);
    strcat(asmString1, tempString);
  }else{
    fprintf(stderr, "ERRO que nao deveria acontecer: asmAdd\n" );
  }

}

void asmSub(TAC* tac, char* asmString0, char* asmString1, char* tempString)
{
  strcat(asmString1, "\n## TAC_SUB\n");
  if(tac->op1 && tac->op2 && tac->res){
    sprintf(tempString, "  	movl	%s(%%rip), %%edx\n  	movl	%s(%%rip), %%eax\n", tac->op1->text, tac->op2->text);
    strcat(asmString1, tempString);
    sprintf(tempString, "  	subl	%%eax, %%edx\n  	movl	%%edx, %%eax\n  	movl	%%eax, %s(%%rip)\n", tac->res->text);
    strcat(asmString1, tempString);
  }else{
    fprintf(stderr, "ERRO que nao deveria acontecer: asmSub\n" );
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

char* generateAsm (TAC* first)
{
  //recebe uma corrente de TACs
  // e gera uma string
  // que eh o programa em assembly
  char* asmString0[ASM_STRING_SIZE]; //declaracoes assembly
  char* asmString1[ASM_STRING_SIZE];
  char* tempString[ASM_STRING_SIZE];

  strcat(asmString0, "	.file	\"testProgram.c\"\n");

  initDeclaredTemps();

  TAC* tac;
  for (tac = first; tac; tac= tac->next)
  {
    //fprintf(stderr, "debug %i\n", tac->type );
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
          break;
      case TAC_VECWRITE:
          break;
      case TAC_MOV:
          break;
      case TAC_READ:
          strcat(asmString0, "\n## TAC_READ\n");
          //asmRead(tac, asmString0, asmString1, tempString); //TODO
          break;
      case TAC_PRINT:
          strcat(asmString0, "\n## TAC_PRINT\n");
          asmPrint(tac, asmString0, asmString1, tempString);
          break;
      case TAC_ARG:
          break;
      case TAC_CALL:
          strcat(asmString1, "\n## TAC_CALL\n");
          break;
      case TAC_IFZ:
          break;
      case TAC_IFN:
          break;
      case TAC_LABEL:
          asmLabel(tac, asmString0, asmString1, tempString);
          break;
      case TAC_JMP:
          break;
      case TAC_SUB:
          asmDeclareTemp(tac, asmString0, asmString1, tempString);
          asmSub(tac, asmString0, asmString1, tempString);
          break;
      case TAC_ADD:
          asmDeclareTemp(tac, asmString0, asmString1, tempString);
          asmAdd(tac, asmString0, asmString1, tempString);
          break;
      case TAC_MUL:
          asmDeclareTemp(tac, asmString0, asmString1, tempString);
          break;
      case TAC_DIV:
          asmDeclareTemp(tac, asmString0, asmString1, tempString);
          break;
      case TAC_INC:
          //asmDeclareTemp(tac, asmString0, asmString1, tempString);
          break;
      case TAC_PARAM:
          //todas variaveis sao globais
          asmParam(tac, asmString0, asmString1, tempString);
          break;
      case TAC_OR:
          break;
      case TAC_EQUAL:
          break;
      case TAC_NOTEQUAL:
          break;
      case TAC_LESSEQUAL:
          break;
      case TAC_GREATEREQUAL:
          break;
      case TAC_LESS:
          break;
      case TAC_GREATER:
          break;
      case TAC_AND:
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
