#include "semantic.h"

void semanticSetDeclarations(ASTREE* node)
{
  int i=0;
  if(!node) return;
  for(i=0; i<MAX_SONS; i++)
  {
    semanticSetDeclarations(node->son[i]);
  }
  /* copiado da aula:
  if(node->type == ASTREE_VARDEC){
    if(node->symbol){
      if(node->symbol->type == SYMBOL_TK_IDENTIFIER){
        node->symbol->type = SYMBOL_VAR;
      }
    }
  }*/
}
