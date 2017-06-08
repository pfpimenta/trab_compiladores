#include "semantic.h"


int semanticErrorFlag = 0;

void checkArgsTypes(ASTREE* node)
{
  //node->type = ASTREE_ARGS
  //node->type = ASTREE_ARGSTAIL
  if(!node) return;
  if(node->son[0]->symbol->exprType == EXPR_BOOLEAN)
  {
    fprintf(stderr, "ERRO SEMANTICO\nargumento %s nao pode ser booleano\n", node->son[0]->symbol->text);
    //exit(4);
    semanticErrorFlag = 1;
  }
  if(node->son[0]->symbol->exprType == EXPR_STRING)
  {
    fprintf(stderr, "ERRO SEMANTICO\nargumento %s nao pode ser string\n", node->son[0]->symbol->text);
    //exit(4);
    semanticErrorFlag = 1;
  }
  if(node->type == ASTREE_ARGS)
  {
    checkArgsTypes(node->son[1]);
    return;
  }
  if(node->type == ASTREE_ARGSTAIL)
  {
    checkArgsTypes(node->son[1]);
    return;
  }
  //nao é pra chegar ate aqui
  fprintf(stderr, "ERRO Q N ERA PRA ACONTECER\ngetNumArgs");
  return;
}

int getExprType(ASTREE* node)
{
  switch (node->type) {
    case ASTREE_EXPRPARENTESIS:
      return getExprType(node->son[0]);
      break;
    case ASTREE_TKID:
      return node->symbol->exprType;
      break;
    case ASTREE_TKIDARRAY:
      return node->symbol->exprType;
      break;
    case ASTREE_TKIDFUNC:
      return node->symbol->exprType;
      break;
    case ASTREE_LITINT:
      return EXPR_INTEGER;
      break;
    case ASTREE_LITCHAR:
      return EXPR_CHAR;
      break;
    case ASTREE_LITREAL:
      return EXPR_REAL;
      break;
    case ASTREE_LITSTRING:
      return EXPR_STRING;
      break;
    case ASTREE_LESSEQUAL:
      return EXPR_BOOLEAN;
      break;
    case ASTREE_GREATEREQUAL:
      return EXPR_BOOLEAN;
      break;
    case ASTREE_EQUAL:
      return EXPR_BOOLEAN;
      break;
    case ASTREE_NOTEQUAL:
      return EXPR_BOOLEAN;
      break;
    case ASTREE_AND:
      return EXPR_BOOLEAN;
      break;
    case ASTREE_OR:
      return EXPR_BOOLEAN;
      break;
    case ASTREE_MULT:
      if(getExprType(node->son[0]) == EXPR_REAL || getExprType(node->son[1]) == EXPR_REAL)
      {
        return EXPR_REAL;
      }else{
        return EXPR_INTEGER;
      }
      break;
    case ASTREE_ADD:
      if(getExprType(node->son[0]) == EXPR_REAL || getExprType(node->son[1]) == EXPR_REAL)
      {
        return EXPR_REAL;
      }else{
        return EXPR_INTEGER;
      }
      break;
    case ASTREE_SUB:
      if(getExprType(node->son[0]) == EXPR_REAL || getExprType(node->son[1]) == EXPR_REAL)
      {
        return EXPR_REAL;
      }else{
        return EXPR_INTEGER;
      }
      break;
    case ASTREE_DIV:
      return EXPR_REAL;
      break;
    case ASTREE_LESS:
      return EXPR_BOOLEAN;
      break;
    case ASTREE_GREATER:
      return EXPR_BOOLEAN;
      break;
    break;
  }
}

int getNumArgs(ASTREE* node)
{
    //node->type = ASTREE_ARGS
    //node->type = ASTREE_ARGSTAIL
    if(!node) return 0;
    if(node->type == ASTREE_ARGS)
    {
      return 1 + getNumArgs(node->son[1]);
    }
    if(node->type == ASTREE_ARGSTAIL)
    {
      return 1 + getNumArgs(node->son[1]);
    }
    //nao é pra chegar ate aqui
    fprintf(stderr, "ERRO Q N ERA PRA ACONTECER\ngetNumArgs");
    return 0;
}

int getNumParameters(ASTREE* node)
{
  if(node->type==ASTREE_PARAM)
  {
    return 1;
  }
  if(node->son[1]->type==ASTREE_PARAM)
  {
    return 2;
  }
  if (node->son[1]->type==ASTREE_PARAMLIST)
  {
    return 1 + getNumParameters(node->son[1]);
  }else{
    fprintf(stderr, "ERRO QUE N DEVIA ACONTECER\ngetNumParameters\n" );
  }
}

void semanticVardec(ASTREE* node){
  if(node->symbol){
    if(node->symbol->type == SYMBOL_TK_IDENTIFIER && node->son[0]){
      if(node->symbol->isDeclared)
      {
        fprintf(stderr, "ERRO SEMANTICO\nvariavel ja declarada: %s\n", node->symbol->text);
        //exit(4);
        semanticErrorFlag = 1;
      }
      node->symbol->isDeclared = 1;
      //setando as natures e exprTypes
      switch (node->son[0]->type) {
        case ASTREE_KWCHAR:
          node->symbol->exprType = EXPR_CHAR;
          node->symbol->nature = NATURE_VAR;
          break;
        case ASTREE_KWINT:
          node->symbol->exprType = EXPR_INTEGER;
          node->symbol->nature = NATURE_VAR;
          break;
        case ASTREE_KWREAL:
          node->symbol->exprType = EXPR_REAL;
          node->symbol->nature = NATURE_VAR;
          break;
        case ASTREE_KWARRAYINT:
          node->symbol->exprType = EXPR_INTEGER;
          node->symbol->nature = NATURE_ARRAY;
          break;
        case ASTREE_KWARRAYCHAR:
          node->symbol->exprType = EXPR_CHAR;
          node->symbol->nature = NATURE_ARRAY;
          break;
        case ASTREE_KWARRAYFLOAT:
          node->symbol->exprType = EXPR_REAL;
          node->symbol->nature = NATURE_ARRAY;
          break;
        case ASTREE_KWARRAY:
          node->symbol->exprType = EXPR_INTEGER;
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
  //printSymbol(*node->symbol);
}


void findReturn(ASTREE* node)
{
    int i;
    if(!node) return;
    if (node->type == ASTREE_KWRETURN)
    {
	      if(getExprType(node->son[0]) == EXPR_BOOLEAN || getExprType(node->son[0]) == EXPR_STRING)     //Dúvida: os DataTypes são intercambiáveis? Exemplo: long a (byte x, long y) return x+y
	      {
          fprintf(stderr, "ERRO SEMANTICO\nretorno invalido \n");
          //exit(4);
          semanticErrorFlag = 1;
        }
    }
    for(i=0; i < MAX_SONS; i++)
    {
        findReturn(node->son[i]);
    }
}

void semanticFuncdec(ASTREE* node)
{
  if(node->symbol){
    //vendo se ja foi declarada
    if(node->symbol->isDeclared)
    {
      fprintf(stderr, "ERRO SEMANTICO\nfuncao ja declarada: %s\n", node->symbol->text);
      //exit(4);
      semanticErrorFlag = 1;
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
  //printSymbol(*node->symbol);
}

void semanticParam(ASTREE* node)
{
  if(node->symbol){
    //vendo se ja foi declarada
    if(node->symbol->isDeclared)
    {
      fprintf(stderr, "ERRO SEMANTICO\nvariavel de parametro ja declarada: %s\n", node->symbol->text);
      //exit(4);
      semanticErrorFlag = 1;
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
    //printSymbol(*node->symbol);
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
        //exit(4);
        semanticErrorFlag = 1;
      }
      break;
    }

    case ASTREE_FUNCDEC :
    {
      //verif vars nao declaradas
      if(!node->symbol->isDeclared)
      {
        fprintf(stderr, "ERRO SEMANTICO\nvariavel nao declarada: %s\n", node->symbol->text);
        //exit(4);
        semanticErrorFlag = 1;
      }
      //verifica natureza
      if(node->symbol->nature != NATURE_FUNC && node->symbol->nature != 0)
      {
        fprintf(stderr, "ERRO SEMANTICO\n Natureza incompativel: %s eh da natureza: %i ,  esperado: %i\n",
                node->symbol->text, node->symbol->nature, NATURE_FUNC);
        //exit(4);
        semanticErrorFlag = 1;
      }

      //verifica se o tipo do return esta correto
      findReturn(node->son[2]);

      break;
    }

    case ASTREE_PARAM:
    {
      //verif vars nao declaradas
      if(!node->symbol->isDeclared)
      {
        fprintf(stderr, "ERRO SEMANTICO\nvariavel nao declarada: %s\n", node->symbol->text);
        //exit(4);
        semanticErrorFlag = 1;
      }
        break;
    }

    case ASTREE_KWREAD:
    {
      //verif vars nao declaradas
      if(!node->symbol->isDeclared)
      {
        fprintf(stderr, "ERRO SEMANTICO\nvariavel nao declarada: %s\n", node->symbol->text);
        //exit(4);
        semanticErrorFlag = 1;
      }
        break;
    }

    case ASTREE_KWPRINT:
    {
      //verifica tipo das expr
      if(node->son[0] != ASTREE_LITSTRING && node->son[0] != ASTREE_PRINTLIST){
        if(getExprType(node->son[0]) == EXPR_BOOLEAN || getExprType(node->son[0])== EXPR_STRING)
  	     {
  	        fprintf(stderr, "ERRO SEMANTICO\nPrint com tipo(s) invalido(s).\n", node->symbol->text);
            //exit(4);
            semanticErrorFlag = 1;
  	     }
      }
      break;
    }

    case ASTREE_KWRETURN:
    {
      //verifica tipo das expr
      if(getExprType(node->son[0]) == EXPR_BOOLEAN || getExprType(node->son[0])== EXPR_STRING)
	     {
	        fprintf(stderr, "ERRO SEMANTICO\nRetorno invalido.\n", node->symbol->text);
          //exit(4);
          semanticErrorFlag = 1;
	     }
      break;
    }

    case ASTREE_PRINTLIST:
    {
      //verifica tipo das expr
      if(node->son[0] != ASTREE_LITSTRING){
        if(getExprType(node->son[0]) == EXPR_BOOLEAN || getExprType(node->son[0])== EXPR_STRING)
  	     {
  	        fprintf(stderr, "ERRO SEMANTICO\nPrint com tipo(s) invalido(s).\n", node->symbol->text);
            //exit(4);
            semanticErrorFlag = 1;
  	     }
      }
      break;
    }

    case ASTREE_KWWHENTHEN:
    {
      //verifica tipo das expr
      if(getExprType(node->son[0]) != EXPR_BOOLEAN)
       {
          fprintf(stderr, "ERRO SEMANTICO\nWhen com tipo(s) invalido(s) (nao booleanos).\n", node->symbol->text);
          //exit(4);
          semanticErrorFlag = 1;
       }
      break;
    }

    case ASTREE_KWWHENTHENELSE:
    {
      //verifica tipo das expr
      if(getExprType(node->son[0]) != EXPR_BOOLEAN)
       {
          fprintf(stderr, "ERRO SEMANTICO\nWhen com tipo(s) invalido(s) (nao booleanos).\n", node->symbol->text);
          //exit(4);
          semanticErrorFlag = 1;
       }
      break;
    }

    case ASTREE_KWWHILE:
    {
      //verifica tipo das expr
      if(getExprType(node->son[0]) != EXPR_BOOLEAN)
       {
          fprintf(stderr, "ERRO SEMANTICO\nWhile com tipo(s) invalido(s) (nao booleanos).\n", node->symbol->text);
          //exit(4);
          semanticErrorFlag = 1;
       }
      break;
    }



    case ASTREE_KWFOR:
    {
      //verif vars nao declaradas
      if(!node->symbol->isDeclared)
      {
        fprintf(stderr, "ERRO SEMANTICO\nvariavel nao declarada: %s\n", node->symbol->text);
        //exit(4);
        semanticErrorFlag = 1;
      }
      //verifica tipo das expr
      if(getExprType(node->son[0]) == EXPR_BOOLEAN || getExprType(node->son[0])== EXPR_STRING)
      {
        fprintf(stderr, "ERRO SEMANTICO\nFor com tipo(s) invalido(s).\n", node->symbol->text);
        //exit(4);
        semanticErrorFlag = 1;
      }
      if(getExprType(node->son[1]) == EXPR_BOOLEAN || getExprType(node->son[1])== EXPR_STRING)
      {
        fprintf(stderr, "ERRO SEMANTICO\nFor com tipo(s) invalido(s).\n", node->symbol->text);
        //exit(4);
        semanticErrorFlag = 1;
      }
      break;
    }

    case ASTREE_ATRIB:
    {
        //verif vars nao declaradas
        if(!node->symbol->isDeclared)
        {
          fprintf(stderr, "ERRO SEMANTICO\nvariavel nao declarada: %s\n", node->symbol->text);
          //exit(4);
          semanticErrorFlag = 1;
        }
        //verifica natureza
        if(node->symbol->nature != NATURE_VAR && node->symbol->nature != 0)
        {
          fprintf(stderr, "ERRO SEMANTICO\n Natureza incompativel: %s eh da natureza: %i ,  esperado: %i\n",
                  node->symbol->text, node->symbol->nature, NATURE_VAR);
          //exit(4);
          semanticErrorFlag = 1;
        }
        //verifica tipo das expr
        if(getExprType(node->son[0]) == EXPR_BOOLEAN || getExprType(node->son[0])== EXPR_STRING)
        {
          fprintf(stderr, "ERRO SEMANTICO\nAtribuiçao com tipo(s) invalido(s) (nao booleanos).\n", node->symbol->text);
          //exit(4);
          semanticErrorFlag = 1;
        }
        break;
    }

    case ASTREE_ATRIBARRAY:
    {
      //verif vars nao declaradas
      if(!node->symbol->isDeclared)
      {
        fprintf(stderr, "ERRO SEMANTICO\nvariavel nao declarada: %s\n", node->symbol->text);
        //exit(4);
        semanticErrorFlag = 1;
      }
      //verifica natureza
      if(node->symbol->nature != NATURE_ARRAY && node->symbol->nature != 0)
      {
        fprintf(stderr, "ERRO SEMANTICO\n Natureza incompativel: %s eh da natureza: %i ,  esperado: %i\n",
                node->symbol->text, node->symbol->nature, NATURE_ARRAY);
        //exit(4);
        semanticErrorFlag = 1;
      }
     //verifica indice do vetor
      if(getExprType(node->son[0]) == EXPR_BOOLEAN || getExprType(node->son[0])== EXPR_REAL)
	     {
	        fprintf(stderr, "ERRO SEMANTICO\nIndice do vetor %s invalido.\n", node->symbol->text);
          //exit(4);
          semanticErrorFlag = 1;
	     }
       //verifica tipo das expr
       if(getExprType(node->son[1]) == EXPR_BOOLEAN || getExprType(node->son[1])== EXPR_STRING)
       {
         fprintf(stderr, "ERRO SEMANTICO\nAtribuiçao com tipo(s) invalido(s) (nao booleanos).\n", node->symbol->text);
         //exit(4);
         semanticErrorFlag = 1;
       }
        break;
    }

    case ASTREE_TKID:
    {
      //verif vars nao declaradas
      if(!node->symbol->isDeclared)
      {
        fprintf(stderr, "ERRO SEMANTICO\nvariavel nao declarada: %s\n", node->symbol->text);
        //exit(4);
        semanticErrorFlag = 1;
      }

      //verifica natureza
      if(node->symbol->nature != NATURE_VAR && node->symbol->nature != 0)
      {
        fprintf(stderr, "ERRO SEMANTICO\n Natureza incompativel: %s eh da natureza: %i ,  esperado: %i\n",
                node->symbol->text, node->symbol->nature, NATURE_VAR);
        //exit(4);
        semanticErrorFlag = 1;
      }
      break;
    }

    case ASTREE_TKIDARRAY:
    {
      //verif vars nao declaradas
      if(!node->symbol->isDeclared)
      {
        fprintf(stderr, "ERRO SEMANTICO\nvariavel nao declarada: %s\n", node->symbol->text);
        //exit(4);
        semanticErrorFlag = 1;
      }
      //verifica natureza
      if(node->symbol->nature != NATURE_ARRAY && node->symbol->nature != 0)
      {
        fprintf(stderr, "ERRO SEMANTICO\n Natureza incompativel: %s é da natureza %i ,  esperado %i\n",
                node->symbol->text, node->symbol->nature, NATURE_ARRAY);
        //exit(4);
        semanticErrorFlag = 1;
      }
      //verifica indice do vetor
      if(getExprType(node->son[0]) == EXPR_BOOLEAN || getExprType(node->son[0])== EXPR_REAL)
	     {
	        fprintf(stderr, "ERRO SEMANTICO\nIndice do vetor %s invalido.\n", node->symbol->text);
          //exit(4);
          semanticErrorFlag = 1;
	     }
      break;
    }

    case ASTREE_TKIDFUNC :
    {
      //verif vars nao declaradas
      if(!node->symbol->isDeclared)
      {
        fprintf(stderr, "ERRO SEMANTICO\nvariavel nao declarada: %s\n", node->symbol->text);
        //exit(4);
        semanticErrorFlag = 1;
      }
      //verifica natureza
      if(node->symbol->nature != NATURE_FUNC && node->symbol->nature != 0)
      {
        fprintf(stderr, "ERRO SEMANTICO\n Natureza incompativel: %s é da natureza %i ,  esperado %i\n",
                node->symbol->text, node->symbol->nature, NATURE_FUNC);
        //exit(4);
        semanticErrorFlag = 1;
      }

      //verifica tipo dos argumentos
      checkArgsTypes(node->son[0]);

      //verifica num de argumentos
      int numParameters = node->symbol->numParameters;
      int numArgs = getNumArgs(node->son[0]);
      if(numArgs != numParameters)
      {
        fprintf(stderr, "ERRO SEMANTICO\n numero de errado argumentos: %s é deveria receber %i argumentos,  mas recebeu %i\n",
                node->symbol->text, numParameters, numArgs);
        //exit(4);
        semanticErrorFlag = 1;
      }
      break;
    }

    case ASTREE_LESSEQUAL:
    {
        if(getExprType(node->son[0]) == EXPR_STRING || getExprType(node->son[1]) == EXPR_STRING){
          fprintf(stderr, "ERRO SEMANTICO\ncomparando strings");
          //exit(4);
          semanticErrorFlag = 1;
        }
        if(getExprType(node->son[0]) == EXPR_BOOLEAN || getExprType(node->son[1]) == EXPR_BOOLEAN)
        {
          fprintf(stderr, "ERRO SEMANTICO\ncomparando tamanhos de booleanos");
          //exit(4);
          semanticErrorFlag = 1;
        }
        break;
    }

    case ASTREE_GREATEREQUAL:
    {
        if(getExprType(node->son[0]) == EXPR_STRING || getExprType(node->son[1]) == EXPR_STRING){
          fprintf(stderr, "ERRO SEMANTICO\ncomparando strings\n");
          //exit(4);
          semanticErrorFlag = 1;
        }
        if(getExprType(node->son[0]) == EXPR_BOOLEAN || getExprType(node->son[1]) == EXPR_BOOLEAN)
        {
          fprintf(stderr, "ERRO SEMANTICO\ncomparando tamanhos de booleanos\n");
          //exit(4);
          semanticErrorFlag = 1;
        }
        break;
    }

    case ASTREE_EQUAL :
    {
        if(getExprType(node->son[0]) == EXPR_STRING || getExprType(node->son[1]) == EXPR_STRING){
          fprintf(stderr, "ERRO SEMANTICO\ncomparando strings\n");
          //exit(4);
          semanticErrorFlag = 1;
        }
        if(getExprType(node->son[0]) == EXPR_BOOLEAN || getExprType(node->son[1]) == EXPR_BOOLEAN)
        {
          fprintf(stderr, "ERRO SEMANTICO\ncomparando tamanhos de booleanos\n");
          //exit(4);
          semanticErrorFlag = 1;
        }
        break;
    }

    case ASTREE_NOTEQUAL:
    {
        if(getExprType(node->son[0]) == EXPR_STRING || getExprType(node->son[1]) == EXPR_STRING){
          fprintf(stderr, "ERRO SEMANTICO\ncomparando strings\n");
          //exit(4);
          semanticErrorFlag = 1;
        }
        if(getExprType(node->son[0]) == EXPR_BOOLEAN || getExprType(node->son[1]) == EXPR_BOOLEAN)
        {
          fprintf(stderr, "ERRO SEMANTICO\ncomparando tamanhos de booleanos\n");
          //exit(4);
          semanticErrorFlag = 1;
        }
        break;
    }

    case ASTREE_AND:
    {
      if(getExprType(node->son[0]) == EXPR_STRING || getExprType(node->son[1]) == EXPR_STRING){
        fprintf(stderr, "ERRO SEMANTICO\nusando strings no lugar de booleanos\n");
        //exit(4);
        semanticErrorFlag = 1;
      }
      if(getExprType(node->son[0]) != EXPR_BOOLEAN || getExprType(node->son[1]) != EXPR_BOOLEAN)
      {
        fprintf(stderr, "ERRO SEMANTICO\nusando numeros no lugar de booleanos\n");
        //exit(4);
        semanticErrorFlag = 1;
      }
      break;
    }

    case ASTREE_OR:
    {
      if(getExprType(node->son[0]) == EXPR_STRING || getExprType(node->son[1]) == EXPR_STRING){
        fprintf(stderr, "ERRO SEMANTICO\nusando strings no lugar de booleanos\n");
        //exit(4);
        semanticErrorFlag = 1;
      }
      if(getExprType(node->son[0]) != EXPR_BOOLEAN || getExprType(node->son[1]) != EXPR_BOOLEAN)
      {
        fprintf(stderr, "ERRO SEMANTICO\nusando numeros no lugar de booleanos\n");
        //exit(4);
        semanticErrorFlag = 1;
      }
      break;
    }

    case ASTREE_MULT:
    {
      if(getExprType(node->son[0]) == EXPR_STRING || getExprType(node->son[1]) == EXPR_STRING){
        fprintf(stderr, "ERRO SEMANTICO\nmultiplicando strings\n");
        //exit(4);
        semanticErrorFlag = 1;
      }
      if(getExprType(node->son[0]) == EXPR_BOOLEAN || getExprType(node->son[1]) == EXPR_BOOLEAN)
      {
        fprintf(stderr, "ERRO SEMANTICO\n multiplicando booleanos\n");
        //exit(4);
        semanticErrorFlag = 1;
      }
      break;
    }

    case ASTREE_ADD:
    {
      if(getExprType(node->son[0]) == EXPR_STRING || getExprType(node->son[1]) == EXPR_STRING){
        fprintf(stderr, "ERRO SEMANTICO\nsomando strings\n");
        //exit(4);
        semanticErrorFlag = 1;
      }
      if(getExprType(node->son[0]) == EXPR_BOOLEAN || getExprType(node->son[1]) == EXPR_BOOLEAN)
      {
        fprintf(stderr, "ERRO SEMANTICO\n somando booleanos\n");
        //exit(4);
        semanticErrorFlag = 1;
      }
      break;
    }

    case ASTREE_SUB:
    {
      if(getExprType(node->son[0]) == EXPR_STRING || getExprType(node->son[1]) == EXPR_STRING){
        fprintf(stderr, "ERRO SEMANTICO\n subtraindo strings\n");
        //exit(4);
        semanticErrorFlag = 1;
      }
      if(getExprType(node->son[0]) == EXPR_BOOLEAN || getExprType(node->son[1]) == EXPR_BOOLEAN)
      {
        fprintf(stderr, "ERRO SEMANTICO\n subtraindo booleanos\n");
        //exit(4);
        semanticErrorFlag = 1;
      }
      break;
    }

    case ASTREE_DIV:
    {
      if(getExprType(node->son[0]) == EXPR_STRING || getExprType(node->son[1]) == EXPR_STRING){
        fprintf(stderr, "ERRO SEMANTICO\n dividindo strings\n");
        //exit(4);
        semanticErrorFlag = 1;
      }
      if(getExprType(node->son[0]) == EXPR_BOOLEAN || getExprType(node->son[1]) == EXPR_BOOLEAN)
      {
        fprintf(stderr, "ERRO SEMANTICO\n dividindo booleanos\n");
        //exit(4);
        semanticErrorFlag = 1;
      }
      break;
    }

    case ASTREE_LESS:
    {
        if(getExprType(node->son[0]) == EXPR_STRING || getExprType(node->son[1]) == EXPR_STRING){
          fprintf(stderr, "ERRO SEMANTICO\ncomparando strings\n");
          //exit(4);
          semanticErrorFlag = 1;
        }
        if(getExprType(node->son[0]) == EXPR_BOOLEAN || getExprType(node->son[1]) == EXPR_BOOLEAN)
        {
          fprintf(stderr, "ERRO SEMANTICO\ncomparando tamanhos de booleanos\n");
          //exit(4);
          semanticErrorFlag = 1;
        }
        break;
    }

    case ASTREE_GREATER:
    {
        if(getExprType(node->son[0]) == EXPR_STRING || getExprType(node->son[1]) == EXPR_STRING){
          fprintf(stderr, "ERRO SEMANTICO\ncomparando strings\n");
          //exit(4);
          semanticErrorFlag = 1;
        }
        if(getExprType(node->son[0]) == EXPR_BOOLEAN || getExprType(node->son[1]) == EXPR_BOOLEAN)
        {
          fprintf(stderr, "ERRO SEMANTICO\ncomparando tamanhos de booleanos\n");
          //exit(4);
          semanticErrorFlag = 1;
        }
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
