#include "semantic.h"

int getNumParameters(ASTREE* node)
{
  if(node->son[1]->type==ASTREE_PARAM)
  {
    return 1;
  }else{
    return 1 + getNumParameters(node->son[1]);
  }
}

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
    //setando o numero de parametros
    if(node->son[1] == 0)
    {
      node->symbol->numParameters = 0;
    }else{
      node->symbol->numParameters = getNumParameters(node->son[1]);
    }
  }else{
    fprintf(stderr, " erro que nao era pra acontecer???\n");
  }


  //debug:
  printSymbol(*node->symbol);
}

void semanticParam(ASTREE* node)
{
  if(node->symbol){
    //vendo se ja foi declarada
    if(node->symbol->isDeclared)
    {
      fprintf(stderr, "ERRO SEMANTICO\nvariavel de parametro ja declarada: %s\n", node->symbol->text);
      exit(4);
    }
    node->symbol->isDeclared = 1;

    //setando as natures
    if(node->symbol->type == SYMBOL_TK_IDENTIFIER && node->son[0]){
      node->symbol->nature = NATURE_VAR;
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

    //debug
    printSymbol(*node->symbol);
  }
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
      break;
    case ASTREE_PARAM:
      semanticParam(node);
      break;
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

    case ASTREE_VARDEC :
    {
      //verif vars nao declaradas
      if(!node->symbol->isDeclared)
      {
        fprintf(stderr, "ERRO SEMANTICO\nvariavel nao declarada: %s\n", node->symbol->text);
        exit(4);
      }
      //verif. natureza

      break;
    }
    case ASTREE_LITCHAR :
    {
        //verificar tipos de dados nas expressões:
        break;
    }

    case ASTREE_LITREAL:
    {

        break;
    }

    case ASTREE_FUNCDEC :
    {
      //verif vars nao declaradas
      if(!node->symbol->isDeclared)
      {
        fprintf(stderr, "ERRO SEMANTICO\nvariavel nao declarada: %s\n", node->symbol->text);
        exit(4);
      }
      //verif. natureza

      break;
    }

    case ASTREE_PARAM:
    {
      //verif vars nao declaradas
      if(!node->symbol->isDeclared)
      {
        fprintf(stderr, "ERRO SEMANTICO\nvariavel nao declarada: %s\n", node->symbol->text);
        exit(4);
      }
        break;
    }

    case ASTREE_KWREAD:
    {
      //verif vars nao declaradas
      if(!node->symbol->isDeclared)
      {
        fprintf(stderr, "ERRO SEMANTICO\nvariavel nao declarada: %s\n", node->symbol->text);
        exit(4);
      }
        break;
    }

    case ASTREE_KWRETURN :
    {
        //verificar tipo do valor de retorno da função
        break;
    }

    case ASTREE_LITSTRING:
    {

        break;
    }

    case ASTREE_KWFOR:
    {
      //verif vars nao declaradas
      if(!node->symbol->isDeclared)
      {
        fprintf(stderr, "ERRO SEMANTICO\nvariavel nao declarada: %s\n", node->symbol->text);
        exit(4);
      }
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
        /*if(node->symbol->nature != getAstreeNature(node->son[0]))
        {
          fprintf(stderr, "ERRO SEMANTICO\n Natureza incompativel: %s é da natureza %i ,  esperado %i\n",
                  node->symbol->text, node->son[0]->symbol->nature, node->symbol->nature);
          exit(4);
        }*/
        break;
    }

    case ASTREE_ATRIBARRAY:
    {
      //verif vars nao declaradas
      if(!node->symbol->isDeclared)
      {
        fprintf(stderr, "ERRO SEMANTICO\nvariavel nao declarada: %s\n", node->symbol->text);
        exit(4);
      }
        break;
    }

    case ASTREE_EXPRPARENTESIS:
    {

        break;
    }

    case ASTREE_TKID:
    {
      //verif vars nao declaradas
      if(!node->symbol->isDeclared)
      {
        fprintf(stderr, "ERRO SEMANTICO\nvariavel nao declarada: %s\n", node->symbol->text);
        exit(4);
      }

      //verifica natureza
      if(node->symbol->nature != NATURE_VAR)
      {
        fprintf(stderr, "ERRO SEMANTICO\n Natureza incompativel: %s eh da natureza: %i ,  esperado: %i\n",
                node->symbol->text, node->symbol->nature, NATURE_VAR);
        exit(4);
      }
      break;
    }

    case ASTREE_TKIDARRAY:
    {
      //verif vars nao declaradas
      if(!node->symbol->isDeclared)
      {
        fprintf(stderr, "ERRO SEMANTICO\nvariavel nao declarada: %s\n", node->symbol->text);
        exit(4);
      }
      //verifica natureza
      if(node->symbol->nature != NATURE_ARRAY)
      {
        fprintf(stderr, "ERRO SEMANTICO\n Natureza incompativel: %s é da natureza %i ,  esperado %i\n",
                node->symbol->text, node->symbol->nature, NATURE_ARRAY);
        exit(4);
      }
      break;
    }

    case ASTREE_TKIDFUNC :
    {
      //verif vars nao declaradas
      if(!node->symbol->isDeclared)
      {
        fprintf(stderr, "ERRO SEMANTICO\nvariavel nao declarada: %s\n", node->symbol->text);
        exit(4);
      }
      //verifica natureza
      if(node->symbol->nature != NATURE_FUNC)
      {
        fprintf(stderr, "ERRO SEMANTICO\n Natureza incompativel: %s é da natureza %i ,  esperado %i\n",
                node->symbol->text, node->symbol->nature, NATURE_FUNC);
        exit(4);
      }
      break;
    }

    case ASTREE_LESSEQUAL:
    {

        break;
    }

    case ASTREE_GREATEREQUAL:
    {

        break;
    }

    case ASTREE_EQUAL :
    {

        break;
    }

    case ASTREE_NOTEQUAL:
    {

        break;
    }

    case ASTREE_AND:
    {

        break;
    }

    case ASTREE_OR:
    {

        break;
    }

    case ASTREE_MULT:
    {

        break;
    }

    case ASTREE_ADD:
    {

        break;
    }

    case ASTREE_SUB:
    {

        break;
    }

    case ASTREE_DIV:
    {

        break;
    }

    case ASTREE_LESS:
    {

        break;
    }

    case ASTREE_GREATER:
    {

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
