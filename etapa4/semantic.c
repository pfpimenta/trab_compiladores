#include "semantic.h"


void semanticVardec(ASTREE* node){
  if(node->symbol){
    if(node->symbol->type == SYMBOL_TK_IDENTIFIER && node->son[0]){
      if(node->symbol->isDeclared)
      {
        fprintf(stderr, "ERRO SEMANTICO\nvariavel ja declarada: %s\n", node->symbol->text);
        exit(4);
      }
      node->symbol->isDeclared = 1;
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
    //vendo se ja foi declarada
    if(node->symbol->isDeclared)
    {
      fprintf(stderr, "ERRO SEMANTICO\nfuncao ja declarada: %s\n", node->symbol->text);
      exit(4);
    }
    node->symbol->isDeclared = 1;
    
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
}


void semanticCheck(ASTREE* node)
{
  int i=0;
  if(!node) return;
  //checka recursivamente
  for(i=0; i<MAX_SONS; i++)
  {
    semanticCheck(node->son[i]);
  }

  //verifica pra cada tipo
  switch (node->type) {


    case ASTREE_LITCHAR :
    {
        //verificar tipos de dados nas expressões:
        break;
    }

    case ASTREE_LITREAL:
    {
        fprintf(stderr,"ASTREE_LITREAL");
        break;
    }

    case ASTREE_FUNCDEC :
    {
        //verif. variaveis nao declaradas:
        //verif. natureza
        fprintf(stderr,"ASTREE_FUNCDEC");
        break;
    }

    case ASTREE_PARAM:
    {
        fprintf(stderr,"ASTREE_PARAM");
        break;
    }

    case ASTREE_KWREAD:
    {
        fprintf(stderr,"ASTREE_KWREAD");
        break;
    }

    case ASTREE_KWRETURN :
    {
        //verificar tipo do valor de retorno da função
        break;
    }

    case ASTREE_LITSTRING:
    {
        fprintf(stderr,"ASTREE_LITSTRING");
        break;
    }

    case ASTREE_KWFOR:
    {
        fprintf(stderr,"ASTREE_KWFOR");
        break;
    }

    case ASTREE_ATRIB:
    {
        //verif vars nao declaradas
        if(!node->symbol->isDeclared)
        {
          fprintf(stderr, "ERRO SEMANTICO\nvariavel nao declarada: %s\n", node->symbol->text);
          exit(4);
        }
        //verif natureza
        /*if(node->symbol->nature != )
        {
          fprintf(stderr, "ERRO SEMANTICO\n natureza incompativel: %s\n", node->symbol->text);
          exit(4);
        }*/
        break;
    }

    case ASTREE_ATRIBARRAY:
    {
        fprintf(stderr,"ASTREE_ATRIBARRAY");
        break;
    }

    case ASTREE_EXPRPARENTESIS:
    {
        fprintf(stderr,"ASTREE_EXPRPARENTESIS");
        break;
    }

    case ASTREE_TKID:
    {
        fprintf(stderr,"ASTREE_TKID");
        break;
    }

    case ASTREE_TKIDARRAY:
    {
        fprintf(stderr,"ASTREE_TKIDARRAY");
        break;
    }

    case ASTREE_TKIDFUNC :
    {
        fprintf(stderr,"ASTREE_TKIDFUNC");
        break;
    }

    case ASTREE_LESSEQUAL:
    {
        fprintf(stderr,"ASTREE_LESSEQUAL");
        break;
    }

    case ASTREE_GREATEREQUAL:
    {
        fprintf(stderr,"ASTREE_GREATEREQUAL");
        break;
    }

    case ASTREE_EQUAL :
    {
        fprintf(stderr,"ASTREE_EQUAL");
        break;
    }

    case ASTREE_NOTEQUAL:
    {
        fprintf(stderr,"ASTREE_NOTEQUAL");
        break;
    }

    case ASTREE_AND:
    {
        fprintf(stderr,"ASTREE_AND");
        break;
    }

    case ASTREE_OR:
    {
        fprintf(stderr,"ASTREE_OR");
        break;
    }

    case ASTREE_MULT:
    {
        fprintf(stderr,"ASTREE_MULT");
        break;
    }

    case ASTREE_ADD:
    {
        fprintf(stderr,"ASTREE_ADD");
        break;
    }

    case ASTREE_SUB:
    {
        fprintf(stderr,"ASTREE_SUB");
        break;
    }

    case ASTREE_DIV:
    {
        fprintf(stderr,"ASTREE_DIV");
        break;
    }

    case ASTREE_LESS:
    {
        fprintf(stderr,"ASTREE_LESS");
        break;
    }

    case ASTREE_GREATER:
    {
        fprintf(stderr,"ASTREE_GREATER");
        break;
    }

    default:
      //fprintf(stderr, "ERRO QUE NAO DEVIA ACONTECER\n");
      //fprintf(stderr, "tipo da astree fora do switch case\n");
      //fprintf(stderr, "(semanticSetDeclarations)\n");
      break;
  }

  //nenhum erro semantico encontrado
  return;
}
