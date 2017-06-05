#include "semantic.h"


void semanticVardec(ASTREE* node){
  //struct ASTREE* son;
  if(node->symbol){
    if(node->symbol->type == SYMBOL_TK_IDENTIFIER && node->son[0]){
      //son = node->son[0];
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
    }
  }
  else{
    fprintf(stderr, "astree foi gerada errada?? \n");
  }
}

void semanticFuncdec(ASTREE* node)
{
  
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
  }
  if(node->type == ASTREE_VARDEC){
  }//*/

}
