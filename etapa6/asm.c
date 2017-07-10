#include "asm.h"

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
    sprintf(tempString, " .comm %s, %i, 32\n", tac->res->text, 4*vectorSize);
  }else{
    sprintf(tempString, "");
    for(tacTemp = tac->prev; tacTemp->prev->type == TAC_SYMBOL; tacTemp = tacTemp->prev)
    {} // vai ate o primeiro TAC_SYMBOL
    for(tacTemp = tacTemp; tacTemp->type == TAC_SYMBOL; tacTemp = tacTemp->next)
    {
      if(tacTemp->res->type == SYMBOL_LIT_REAL)
      {
        strcat(tempString, " .long ");
        strcat(tempString, "111111" );
        strcat(tempString, "\n");
      }else{
        if(tacTemp->res->type == SYMBOL_LIT_CHAR)
        {
          char* charValue[40];
          sprintf(charValue , "%d", tacTemp->res->text[1]);
          strcat(tempString, " .byte ");
          strcat(tempString, charValue);
          strcat(tempString, "\n");
        }else{
          strcat(tempString, " .long ");
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

void endFun(TAC* tac, char* asmString0, char* asmString1, char* tempString)
{
  strcat(asmString1, "\n## TAC_BEGGINFUN\n");
  sprintf(tempString,"	popq	%%rbp\n	ret\n");
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

char* generateAsm (TAC* first)
{
  //recebe uma corrente de TACs
  // e gera uma string
  // que eh o programa em assembly
  char* asmString0[ASM_STRING_SIZE]; //declaracoes assembly
  char* asmString1[ASM_STRING_SIZE];
  char* tempString[ASM_STRING_SIZE];

  strcat(asmString0, "	.file	\"testProgram.c\"\n");

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
        strcat(asmString1,"	popq	%%rbp\n	ret\n");
        break;
      case TAC_VECREAD:
      case TAC_VECWRITE:
      case TAC_MOV:
      case TAC_READ:
          strcat(asmString0, "\n## TAC_READ\n");
          break;
      case TAC_PRINT:
          strcat(asmString0, "\n## TAC_PRINT\n");
          break;
      case TAC_ARG:
      case TAC_CALL:
          strcat(asmString0, "\n## TAC_CALL\n");
          break;
      case TAC_IFZ:
      case TAC_IFN:
      case TAC_LABEL:
      case TAC_JMP:
      case TAC_SUB:
      case TAC_ADD:
      case TAC_MUL:
      case TAC_DIV:
      case TAC_INC:
      case TAC_PARAM:
      case TAC_OR:
      case TAC_EQUAL:
      case TAC_NOTEQUAL:
      case TAC_LESSEQUAL:
      case TAC_GREATEREQUAL:
      case TAC_LESS:
      case TAC_GREATER:
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
