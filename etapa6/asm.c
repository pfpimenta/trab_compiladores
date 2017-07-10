#include "asm.h"


char* generateAsm (TAC* tac)
{
  //recebe uma corrente de TACs
  // e gera uma string
  // que eh o programa em assembly
  char* asmString[200];

  strcpy(asmString, "	.file	\"testProgram.c\"\n");


  switch (tac->type) {
    case TAC_SYMBOL:
      //ignora
      break;
    case TAC_RETURN:
    case TAC_BEGGINFUN:
    case TAC_ENDFUN:
    case TAC_VECREAD:
    case TAC_VECWRITE:
    case TAC_MOV:
    case TAC_READ:
    case TAC_PRINT:
    case TAC_ARG:
    case TAC_CALL:
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
    case TAC_VARDEC:
    case TAC_VECDEC:
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


    strcat(asmString,"	.ident	\"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.3) 4.8.4\"\n" );
    strcat(asmString,"	.section	.note.GNU-stack,\"\",@progbits\n");

    return asmString;
}
