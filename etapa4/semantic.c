#include "semantic.h"


void semanticVardec(ASTREE* node){
  if(node->symbol){
    if(node->symbol->type == SYMBOL_TK_IDENTIFIER && node->son[0]){
      //setando as natures
      switch (node->son[0]->type) {
        case ASTREE_KWCHAR:
        case ASTREE_KWINT:
        case ASTREE_KWREAL:
          node->symbol->nature = NATURE_VAR;
          break;
        case ASTREE_KWARRAYINT:
        case ASTREE_KWARRAYCHAR:
        case ASTREE_KWARRAYFLOAT:
        case ASTREE_KWARRAY:
          node->symbol->nature = NATURE_ARRAY;
          break;
      }
      //tem que consertar a parte da etapa3 que lidava com
      //os filhos de 'vartypeandvalue', q tem 1 filho a mais agora
	//obs: ja consertei astreePrint, falta a astreeDecompile?

      //setando os datatypes
      switch(node->son[0]->son[0]->type){
        case ASTREE_KWBYTE:
          node->symbol->dataType = DATATYPE_BYTE;
          break;
        case ASTREE_KWSHORT:
          node->symbol->dataType = DATATYPE_SHORT;
          break;
        case ASTREE_KWLONG:
          node->symbol->dataType = DATATYPE_LONG;
          break;
        case ASTREE_KWFLOAT:
          node->symbol->dataType = DATATYPE_FLOAT;
          break;
        case ASTREE_KWDOUBLE:
          node->symbol->dataType = DATATYPE_DOUBLE;
          break;
        default:
          //fprintf(stderr, "ERRO QUE NAO DEVIA ACONTECER\n");
          //fprintf(stderr, "tipo da astree fora do switch case\n");
          //fprintf(stderr, "(semanticVardec)\n");
          break;
      }
    }
  }
  else{
    fprintf(stderr, "astree foi gerada errada?? \n");
  }
  //debug:
  printSymbol(*node->symbol);
}

void semanticFuncdec(ASTREE* node)
{
  if(node->symbol){
    //setando as natures
    if(node->symbol->type == SYMBOL_TK_IDENTIFIER && node->son[0]){
      node->symbol->nature = NATURE_FUNC;
    }
    //setando as dataType
    switch(node->son[0]->type){
      case ASTREE_KWBYTE:
        node->symbol->dataType = DATATYPE_BYTE;
        break;
      case ASTREE_KWSHORT:
        node->symbol->dataType = DATATYPE_SHORT;
        break;
      case ASTREE_KWLONG:
        node->symbol->dataType = DATATYPE_LONG;
        break;
      case ASTREE_KWFLOAT:
        node->symbol->dataType = DATATYPE_FLOAT;
        break;
      case ASTREE_KWDOUBLE:
        node->symbol->dataType = DATATYPE_DOUBLE;
        break;
      default:
        //fprintf(stderr, "ERRO QUE NAO DEVIA ACONTECER\n");
        //fprintf(stderr, "tipo da astree fora do switch case\n");
        //fprintf(stderr, "(semanticFuncdec)\n");
        break;
    }

  }else{
    fprintf(stderr, " erro que nao era pra acontecer???\n");
  }


  //debug:
  printSymbol(*node->symbol);
}


void semanticSetDeclarations(ASTREE* node)
{
  //fprintf(stderr, "\n***DEBUG: entrou na semanticSetDeclarations");
  int i=0;
  if(!node) return;
  for(i=0; i<MAX_SONS; i++)
  {
    semanticSetDeclarations(node->son[i]);
  }

  ///* copiado da aula:
  switch (node->type) {
    case ASTREE_VARDEC:
      semanticVardec(node);
      break;
    case ASTREE_FUNCDEC:
      semanticFuncdec(node);
    default:
      //fprintf(stderr, "ERRO QUE NAO DEVIA ACONTECER\n");
      //fprintf(stderr, "tipo da astree fora do switch case\n");
      //fprintf(stderr, "(semanticSetDeclarations)\n");
      break;
  }
  if(node->type == ASTREE_VARDEC){
  }//*/

}
