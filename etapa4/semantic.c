#include "semantic.h"

void semanticSetDeclarations(ASTREE* node)
{
  fprintf(stderr, "\n***DEBUG: entrou na semanticSetDeclarations");
  int i=0;
  if(!node) return;
  for(i=0; i<MAX_SONS; i++)
  {
    semanticSetDeclarations(node->son[i]);
  }

  ///* copiado da aula:
  if(node->type == ASTREE_VARDEC){
    if(node->symbol){
      if(node->symbol->type == SYMBOL_TK_IDENTIFIER){
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
  }//*/
}
