#include <stdio.h>
#include "astree.h"

ASTREE* astreeCreate(int type, HASH_NODE* symbol,
                    ASTREE* son0, ASTREE* son1, ASTREE* son2, ASTREE* son3)
{
    ASTREE* newnode = 0;
    newnode = calloc(1, sizeof(ASTREE));

    newnode->type = type;
    newnode->symbol = symbol;
    newnode->son[0] = son0;
    newnode->son[1] = son1;
    newnode->son[2] = son2;
    newnode->son[3] = son3;

    return newnode;

};

void astreePrint(ASTREE* node, int level)
{
    int i;

    if(!node) return;
    fprintf(stderr, "\n");
    for(i=0; i < level; i++)
    {
        fprintf(stderr, "  ");
    }

    switch(node->type)
    {
      case ASTREE_PROGRAM:
      {
          fprintf(stderr,"ASTREE_PROGRAM");
          break;
      }

      case ASTREE_VARDEC:
      {
          fprintf(stderr,"ASTREE_VARDEC");
          break;
      }

      case ASTREE_KWCHAR:
      {
          fprintf(stderr,"ASTREE_KWCHAR");
          break;
      }

      case ASTREE_KWINT:
      {
          fprintf(stderr,"ASTREE_KWINT");
          break;
      }

      case ASTREE_KWREAL:
      {
          fprintf(stderr,"ASTREE_KWREAL");
          break;
      }

      case ASTREE_KWARRAYINT:
      {
          fprintf(stderr,"ASTREE_KWARRAYINT");
          break;
      }

      case ASTREE_KWARRAYCHAR:
      {
          fprintf(stderr,"ASTREE_KWARRAYCHAR");
          break;
      }



      case ASTREE_KWARRAYFLOAT:
      {
          fprintf(stderr,"ASTREE_KWFLOATARRAYFLOAT");
          break;
      }


      case ASTREE_KWARRAY:
      {
          fprintf(stderr,"ASTREE_KWDOUBLEARRAY");
          break;
      }

      case ASTREE_INTLIST:
      {
          fprintf(stderr,"ASTREE_INTLIST");
          break;
      }

      case ASTREE_LITINT:
      {
          fprintf(stderr,"ASTREE_LITINT");
          break;
      }

      case ASTREE_CHARLIST:
      {
          fprintf(stderr,"ASTREE_CHARLIST");
          break;
      }

      case ASTREE_LITCHAR :
      {
          fprintf(stderr,"ASTREE_LITCHAR");
          break;
      }

      case ASTREE_FLOATLIST:
      {
          fprintf(stderr,"ASTREE_FLOATLIST");
          break;
      }

      case ASTREE_LITREAL:
      {
          fprintf(stderr,"ASTREE_LITREAL");
          break;
      }

      case ASTREE_FUNCDEC :
      {
          fprintf(stderr,"ASTREE_FUNCDEC");
          break;
      }

      case ASTREE_PARAMLIST:
      {
          fprintf(stderr,"ASTREE_PARAMLIST");
          break;
      }

      case ASTREE_PARAM:
      {
          fprintf(stderr,"ASTREE_PARAM");
          break;
      }

      case ASTREE_KWBYTE :
      {
          fprintf(stderr,"ASTREE_KWBYTE");
          break;
      }

      case ASTREE_KWSHORT:
      {
          fprintf(stderr,"ASTREE_KWSHORT");
          break;
      }

      case ASTREE_KWLONG:
      {
          fprintf(stderr,"ASTREE_KWLONG");
          break;
      }

      case ASTREE_KWFLOAT:
      {
          fprintf(stderr,"ASTREE_KWFLOAT");
          break;
      }

      case ASTREE_KWDOUBLE:
      {
          fprintf(stderr,"ASTREE_KWDOUBLE");
          break;
      }

      case ASTREE_CMDLIST:
      {
          fprintf(stderr,"ASTREE_CMDLIST");
          break;
      }

      case ASTREE_CMDCOLCHETES :
      {
          fprintf(stderr,"ASTREE_CMDCOLCHETES");
          break;
      }

      case ASTREE_KWREAD:
      {
          fprintf(stderr,"ASTREE_KWREAD");
          break;
      }

      case ASTREE_KWPRINT:
      {
          fprintf(stderr,"ASTREE_KWPRINT");
          break;
      }

      case ASTREE_KWRETURN :
      {
          fprintf(stderr,"ASTREE_KWRETURN");
          break;
      }

      case ASTREE_PRINTLIST:
      {
          fprintf(stderr,"ASTREE_PRINTLIST");
          break;
      }

      case ASTREE_LITSTRING:
      {
          fprintf(stderr,"ASTREE_LITSTRING");
          break;
      }


      case ASTREE_KWWHENTHEN:
      {
          fprintf(stderr,"ASTREE_KWWHENTHEN");
          break;
      }

      case ASTREE_KWWHENTHENELSE:
      {
          fprintf(stderr,"ASTREE_KWWHENTHENELSE");
          break;
      }

      case ASTREE_KWWHILE :
      {
          fprintf(stderr,"ASTREE_KWWHILE");
          break;
      }

      case ASTREE_KWFOR:
      {
          fprintf(stderr,"ASTREE_KWFOR");
          break;
      }

      case ASTREE_ATRIB:
      {
          fprintf(stderr,"ASTREE_ATRIB");
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

      case ASTREE_ARGS:
      {
          fprintf(stderr,"ASTREE_ARGS");
          break;
      }

      case ASTREE_ARGSTAIL:
      {
          fprintf(stderr,"ASTREE_ARGSTAIL");
          break;
      }
    }
    if(node->symbol)
        fprintf(stderr, ": %s", node->symbol->text);
    else
        fprintf(stderr, ":");
    level += 1;
    for(i=0; i < MAX_SONS; i++)
    {
        astreePrint(node->son[i], level);
    }
};

void astreeNodePrint(ASTREE* node)
{
    if(!node) return;
    fprintf(stderr, "\nASTREE NODE(");
    switch(node->type)
    {
        case ASTREE_PROGRAM:
        {
            fprintf(stderr,"ASTREE_PROGRAM");
            break;
        }

        case ASTREE_VARDEC:
        {
            fprintf(stderr,"ASTREE_VARDEC");
            break;
        }

        case ASTREE_KWCHAR:
        {
            fprintf(stderr,"ASTREE_KWCHAR");
            break;
        }

        case ASTREE_KWINT:
        {
            fprintf(stderr,"ASTREE_KWINT");
            break;
        }

        case ASTREE_KWREAL:
        {
            fprintf(stderr,"ASTREE_KWREAL");
            break;
        }

        case ASTREE_KWARRAYINT:
        {
            fprintf(stderr,"ASTREE_KWARRAYINT");
            break;
        }

        case ASTREE_KWARRAYCHAR:
        {
            fprintf(stderr,"ASTREE_KWARRAYCHAR");
            break;
        }

        case ASTREE_KWARRAYFLOAT:
        {
            fprintf(stderr,"ASTREE_KWARRAYFLOAT");
            break;
        }

        case ASTREE_KWARRAY:
        {
            fprintf(stderr,"ASTREE_KWARRAY");
            break;
        }

        case ASTREE_INTLIST:
        {
            fprintf(stderr,"ASTREE_INTLIST");
            break;
        }

        case ASTREE_LITINT:
        {
            fprintf(stderr,"ASTREE_LITINT");
            break;
        }

        case ASTREE_CHARLIST:
        {
            fprintf(stderr,"ASTREE_CHARLIST");
            break;
        }

        case ASTREE_LITCHAR :
        {
            fprintf(stderr,"ASTREE_LITCHAR");
            break;
        }

        case ASTREE_FLOATLIST:
        {
            fprintf(stderr,"ASTREE_FLOATLIST");
            break;
        }

        case ASTREE_LITREAL:
        {
            fprintf(stderr,"ASTREE_LITREAL");
            break;
        }

        case ASTREE_FUNCDEC :
        {
            fprintf(stderr,"ASTREE_FUNCDEC");
            break;
        }

        case ASTREE_PARAMLIST:
        {
            fprintf(stderr,"ASTREE_PARAMLIST");
            break;
        }

        case ASTREE_PARAM:
        {
            fprintf(stderr,"ASTREE_PARAM");
            break;
        }

        case ASTREE_KWBYTE :
        {
            fprintf(stderr,"ASTREE_KWBYTE");
            break;
        }

        case ASTREE_KWSHORT:
        {
            fprintf(stderr,"ASTREE_KWSHORT");
            break;
        }

        case ASTREE_KWLONG:
        {
            fprintf(stderr,"ASTREE_KWLONG");
            break;
        }

        case ASTREE_KWFLOAT:
        {
            fprintf(stderr,"ASTREE_KWFLOAT");
            break;
        }

        case ASTREE_KWDOUBLE:
        {
            fprintf(stderr,"ASTREE_KWDOUBLE");
            break;
        }

        case ASTREE_CMDLIST:
        {
            fprintf(stderr,"ASTREE_CMDLIST");
            break;
        }

        case ASTREE_CMDCOLCHETES :
        {
            fprintf(stderr,"ASTREE_CMDCOLCHETES");
            break;
        }

        case ASTREE_KWREAD:
        {
            fprintf(stderr,"ASTREE_KWREAD");
            break;
        }

        case ASTREE_KWPRINT:
        {
            fprintf(stderr,"ASTREE_KWPRINT");
            break;
        }

        case ASTREE_KWRETURN :
        {
            fprintf(stderr,"ASTREE_KWRETURN");
            break;
        }

        case ASTREE_PRINTLIST:
        {
            fprintf(stderr,"ASTREE_PRINTLIST");
            break;
        }

        case ASTREE_LITSTRING:
        {
            fprintf(stderr,"ASTREE_LITSTRING");
            break;
        }


        case ASTREE_KWWHENTHEN:
        {
            fprintf(stderr,"ASTREE_KWWHENTHEN");
            break;
        }

        case ASTREE_KWWHENTHENELSE:
        {
            fprintf(stderr,"ASTREE_KWWHENTHENELSE");
            break;
        }

        case ASTREE_KWWHILE :
        {
            fprintf(stderr,"ASTREE_KWWHILE");
            break;
        }

        case ASTREE_KWFOR:
        {
            fprintf(stderr,"ASTREE_KWFOR");
            break;
        }

        case ASTREE_ATRIB:
        {
            fprintf(stderr,"ASTREE_ATRIB");
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

        case ASTREE_ARGS:
        {
            fprintf(stderr,"ASTREE_ARGS");
            break;
        }

        case ASTREE_ARGSTAIL:
        {
            fprintf(stderr,"ASTREE_ARGSTAIL");
            break;
        }

    }
    if(node->symbol)
        fprintf(stderr, ": %s", node->symbol->text);
    else
        fprintf(stderr, ": ___");

}

char* astreeDecompile(ASTREE* ast)
{
	if(!ast)
	{
		return "";
	}
	else
	{
		switch(ast->type)
		{

			case ASTREE_PROGRAM:
			{
				char* son0_source = astreeDecompile(ast->son[0]);
				char* son1_source = astreeDecompile(ast->son[1]);
				char* buffer = (char*)calloc(strlen(son0_source) + strlen(son1_source) + 1,sizeof(char));
				sprintf(buffer,"%s%s",son0_source,son1_source);
				return buffer;
				break;
			}

			case ASTREE_VARDEC:
			{
				char* son0_source = astreeDecompile(ast->son[0]);
				char* buffer = (char*)calloc(strlen(ast->symbol->text) + 3 + strlen(son0_source) + 2 + 1,sizeof(char));
				sprintf(buffer,"%s : %s;\n",ast->symbol->text,son0_source);
				return buffer;
				break;
			}

			case ASTREE_KWCHAR:
			{
				char* son0_source = astreeDecompile(ast->son[0]);
				char* buffer = (char*)calloc(5 + strlen(ast->symbol->text)+1,sizeof(char));
				sprintf(buffer,"%s %s", son0_source, ast->symbol->text);
				return buffer;
				break;
			}

			case ASTREE_KWINT:
			{
				char* son0_source = astreeDecompile(ast->son[0]);
				char* buffer = (char*)calloc(5 + strlen(ast->symbol->text)+1,sizeof(char));
				sprintf(buffer,"%s %s", son0_source, ast->symbol->text);
				return buffer;
				break;
			}



			case ASTREE_KWREAL:
			{
				char* son0_source = astreeDecompile(ast->son[0]);
				char* buffer = (char*)calloc(6 + strlen(ast->symbol->text)+1,sizeof(char));
				sprintf(buffer,"%s %s", son0_source, ast->symbol->text);
				return buffer;
				break;
			}

			case ASTREE_KWARRAYINT:
			{
				char* son0_source = astreeDecompile(ast->son[0]);
				char* son1_source = astreeDecompile(ast->son[1]);
				char* buffer = (char*)calloc(6 + strlen(ast->symbol->text) + 2 + strlen(son0_source) + 1,sizeof(char));
				sprintf(buffer,"%s [%s] %s", son0_source, ast->symbol->text, son1_source);
				return buffer;
				break;
			}

			case ASTREE_KWARRAYCHAR:
			{
				char* son0_source = astreeDecompile(ast->son[0]);
				char* son1_source = astreeDecompile(ast->son[1]);
				char* buffer = (char*)calloc(6 + strlen(ast->symbol->text) + 2 + strlen(son0_source) + 1 ,sizeof(char));
				sprintf(buffer,"%s [%s] %s", son0_source, ast->symbol->text, son1_source);
				return buffer;
				break;
			}

			case ASTREE_KWARRAYFLOAT:
			{
				char* son0_source = astreeDecompile(ast->son[0]);
				char* son1_source = astreeDecompile(ast->son[1]);
				char* buffer = (char*)calloc(7 + strlen(ast->symbol->text) + 2 + strlen(son0_source) + 1,sizeof(char));
				sprintf(buffer,"%s [%s] %s", son0_source, ast->symbol->text, son1_source);
				return buffer;
				break;
			}

			case ASTREE_KWARRAY:
			{
				char* son0_source = astreeDecompile(ast->son[0]);
				char* buffer = (char*)calloc(8 + strlen(ast->symbol->text) + 1 + 1,sizeof(char));
				sprintf(buffer,"%s [%s]", son0_source, ast->symbol->text);
				return buffer;
				break;
			}

			case ASTREE_INTLIST:
			{
				char* son0_source = astreeDecompile(ast->son[0]);
				char* buffer = (char*)calloc(strlen(ast->symbol->text) + 1 + strlen(son0_source) + 1,sizeof(char));
				sprintf(buffer,"%s %s", ast->symbol->text, son0_source);
				return buffer;
				break;
			}

			case ASTREE_LITINT:
			{
				char* buffer = (char*)calloc(strlen(ast->symbol->text) + 1,sizeof(char));
				sprintf(buffer,"%s", ast->symbol->text);
				return buffer;
				break;
			}

			case ASTREE_CHARLIST:
			{
				char* son0_source = astreeDecompile(ast->son[0]);
				char* buffer = (char*)calloc(strlen(ast->symbol->text) + 1 + strlen(son0_source) + 1,sizeof(char));
				sprintf(buffer,"%s %s", ast->symbol->text, son0_source);
				return buffer;
				break;
			}

			case ASTREE_LITCHAR :
			{
				char* buffer = (char*)calloc(strlen(ast->symbol->text) + 1,sizeof(char));
				sprintf(buffer,"%s", ast->symbol->text);
				return buffer;
				break;
			}

			case ASTREE_FLOATLIST:
			{
				char* son0_source = astreeDecompile(ast->son[0]);
				char* buffer = (char*)calloc(strlen(ast->symbol->text) + 1 + strlen(son0_source) + 1,sizeof(char));
				sprintf(buffer,"%s %s", ast->symbol->text, son0_source);
				return buffer;
				break;
			}

			case ASTREE_LITREAL:
			{
				char* buffer = (char*)calloc(strlen(ast->symbol->text) + 1,sizeof(char));
				sprintf(buffer,"%s", ast->symbol->text);
				return buffer;
				break;
			}

			case ASTREE_FUNCDEC :
			{
				char* son0_source = astreeDecompile(ast->son[0]);
				char* son1_source = astreeDecompile(ast->son[1]);
				char* son2_source = astreeDecompile(ast->son[2]);
				char* buffer = (char*)calloc(strlen(son0_source) + 1 + strlen(ast->symbol->text) + 2 + strlen(son1_source) + 1 + strlen(son2_source) + 2 + 1 ,sizeof(char));
				sprintf(buffer,"%s %s (%s)%s;\n",son0_source,ast->symbol->text,son1_source,son2_source);
				return buffer;
				break;
			}

			case ASTREE_PARAMLIST:
			{
				char* son0_source = astreeDecompile(ast->son[0]);
				char* son1_source = astreeDecompile(ast->son[1]);
				char* buffer = (char*)calloc(strlen(son0_source) + 1 + strlen(son1_source) + 1,sizeof(char));
				sprintf(buffer,"%s,%s", son0_source, son1_source);
				return buffer;
				break;
			}

			case ASTREE_PARAM:
			{
				char* son0_source = astreeDecompile(ast->son[0]);
				char* buffer = (char*)calloc(strlen(son0_source) + 1 + strlen(ast->symbol->text) + 1,sizeof(char));
				sprintf(buffer,"%s %s", son0_source, ast->symbol->text);
				return buffer;
				break;
			}

			case ASTREE_KWBYTE :
			{
				return "byte";
				break;
			}

			case ASTREE_KWSHORT:
			{
				return "short";
				break;
			}

			case ASTREE_KWLONG:
			{
				return "long";
				break;
			}

			case ASTREE_KWFLOAT:
			{
				return "float";
				break;
			}

			case ASTREE_KWDOUBLE:
			{
				return "double";
				break;
			}

			case ASTREE_CMDLIST:
			{
				char* son0_source = astreeDecompile(ast->son[0]);
  			char* son1_source = astreeDecompile(ast->son[1]);
				char* buffer = (char*)calloc( strlen(son0_source) + strlen(son1_source) + 2 + 1, sizeof(char));
				sprintf(buffer,"%s%s;\n", son0_source, son1_source);
				return buffer;
        break;
			}

			case ASTREE_CMDCOLCHETES :
			{
				char* son0_source = astreeDecompile(ast->son[0]);
				char* buffer = (char*)calloc( 1 + strlen(son0_source) + 1 + 1, sizeof(char));
				sprintf(buffer,"{%s}", son0_source);
				return buffer;
        break;
			}

			case ASTREE_KWREAD:
			{
				char* buffer = (char*)calloc( 5 + strlen(ast->symbol->text) + 1, sizeof(char));
				sprintf(buffer,"read %s", ast->symbol->text);
				return buffer;
        break;
			}

			case ASTREE_KWPRINT:
			{
				char* son0_source = astreeDecompile(ast->son[0]);
				char* buffer = (char*)calloc( 6 + strlen(son0_source) + 1, sizeof(char));
				sprintf(buffer,"print %s", son0_source);
				return buffer;
        break;
			}


			case ASTREE_KWRETURN :
			{
				char* son0_source = astreeDecompile(ast->son[0]);
				char* buffer = (char*)calloc( 7 + strlen(son0_source) + 1, sizeof(char));
				sprintf(buffer,"return %s", son0_source);
				return buffer;
        break;
			}

			case ASTREE_PRINTLIST:
			{
				char* son0_source = astreeDecompile(ast->son[0]);
  			char* son1_source = astreeDecompile(ast->son[1]);
				char* buffer = (char*)calloc(strlen(son0_source) + 1 + strlen(son1_source) + 1, sizeof(char));
				sprintf(buffer,"%s %s", son0_source, son1_source);
				return buffer;
				break;
			}

			case ASTREE_LITSTRING:
			{
        char* buffer = (char*)calloc( strlen(ast->symbol->text) + 1, sizeof(char));
        sprintf(buffer,"%s", ast->symbol->text);
        return buffer;
				break;
			}


			case ASTREE_KWWHENTHEN:
			{
				char* son0_source = astreeDecompile(ast->son[0]);
  			char* son1_source = astreeDecompile(ast->son[1]);
				char* buffer = (char*)calloc( 5  + strlen(son0_source) + 7 + strlen(son1_source) + 1,sizeof(char));
				sprintf(buffer,"when(%s) then\n%s", son0_source, son1_source);
				return buffer;
				break;
			}

			case ASTREE_KWWHENTHENELSE:
			{
				char* son0_source = astreeDecompile(ast->son[0]);
  			char* son1_source = astreeDecompile(ast->son[1]);
    		char* son2_source = astreeDecompile(ast->son[2]);
				char* buffer = (char*)calloc( 5  + strlen(son0_source) + 7 + strlen(son1_source) + 6 + strlen(son2_source) + 1,sizeof(char));
				sprintf(buffer,"when(%s) then\n%s\nelse\n%s", son0_source, son1_source, son2_source);
				return buffer;
				break;
			}

			case ASTREE_KWWHILE :
			{
				char* son0_source = astreeDecompile(ast->son[0]);
  			char* son1_source = astreeDecompile(ast->son[1]);
				char* buffer = (char*)calloc( 6 + strlen(son0_source) + 2 + strlen(son1_source) + 1,sizeof(char));
				sprintf(buffer,"while(%s)\n%s", son0_source, son1_source);
				return buffer;
				break;
			}

			case ASTREE_KWFOR:
			{
				char* son0_source = astreeDecompile(ast->son[0]);
  			char* son1_source = astreeDecompile(ast->son[1]);
    		char* son2_source = astreeDecompile(ast->son[2]);
				char* buffer = (char*)calloc( 4+ strlen(ast->symbol->text) + 3 + strlen(son0_source) + 4 + strlen(son1_source) + 2 + strlen(son2_source) + 1,sizeof(char));
				sprintf(buffer,"for(%s = %s to %s)\n%s", ast->symbol->text, son0_source, son1_source, son2_source);
				return buffer;
				break;
			}

			case ASTREE_ATRIB:
			{
				char* son0_source = astreeDecompile(ast->son[0]);
				char* buffer = (char*)calloc( strlen(ast->symbol->text) + 3 + strlen(son0_source) + 1,sizeof(char));
				sprintf(buffer,"%s = %s", ast->symbol->text, son0_source);
				return buffer;
				break;
			}

			case ASTREE_ATRIBARRAY:
			{
				char* son0_source = astreeDecompile(ast->son[0]);
				char* son1_source = astreeDecompile(ast->son[1]);
				char* buffer = (char*)calloc( strlen(ast->symbol->text) + 3 + strlen(son0_source) + 3 + strlen(son1_source) + 1,sizeof(char));
				sprintf(buffer,"%s # %s = %s", ast->symbol->text, son0_source, son1_source);
				return buffer;
				break;
			}

			case ASTREE_EXPRPARENTESIS:
			{
				char* buffer = (char*)calloc( 1 + strlen(ast->symbol->text) + 1 + 1,sizeof(char));
				sprintf(buffer,"(%s)", ast->symbol->text);
				return buffer;
				break;
			}

			case ASTREE_TKID:
			{
				char* buffer = (char*)calloc( strlen(ast->symbol->text) + 1,sizeof(char));
				sprintf(buffer,"%s", ast->symbol->text);
				return buffer;
				break;
			}

			case ASTREE_TKIDARRAY:
			{
				char* son0_source = astreeDecompile(ast->son[0]);
				char* buffer = (char*)calloc( strlen(ast->symbol->text) + 1 + strlen(son0_source) + 1 + 1,sizeof(char));
				sprintf(buffer,"%s [%s]", ast->symbol->text, son0_source);
				return buffer;
				break;
			}

			case ASTREE_TKIDFUNC :
			{
				char* son0_source = astreeDecompile(ast->son[0]);
				char* buffer = (char*)calloc( strlen(ast->symbol->text) + 1 + strlen(son0_source) + 1 + 1,sizeof(char));
				sprintf(buffer,"%s (%s)", ast->symbol->text, son0_source);
				return buffer;
				break;
			}

			case ASTREE_LESSEQUAL:
			{
				char* son0_source = astreeDecompile(ast->son[0]);
				char* son1_source = astreeDecompile(ast->son[1]);
				char* buffer = (char*)calloc( strlen(son0_source) + 4 + strlen(son1_source) + 1,sizeof(char));
				sprintf(buffer,"%s <= %s", son0_source, son1_source);
				return buffer;
				break;
			}

			case ASTREE_GREATEREQUAL:
			{
				char* son0_source = astreeDecompile(ast->son[0]);
				char* son1_source = astreeDecompile(ast->son[1]);
				char* buffer = (char*)calloc( strlen(son0_source) + 4 + strlen(son1_source) + 1,sizeof(char));
				sprintf(buffer,"%s >= %s", son0_source, son1_source);
				return buffer;
				break;
			}

			case ASTREE_EQUAL :
			{
				char* son0_source = astreeDecompile(ast->son[0]);
				char* son1_source = astreeDecompile(ast->son[1]);
				char* buffer = (char*)calloc( strlen(son0_source) + 4 + strlen(son1_source) + 1,sizeof(char));
				sprintf(buffer,"%s == %s", son0_source, son1_source);
				return buffer;
				break;
			}

			case ASTREE_NOTEQUAL:
			{
				char* son0_source = astreeDecompile(ast->son[0]);
				char* son1_source = astreeDecompile(ast->son[1]);
				char* buffer = (char*)calloc( strlen(son0_source) + 4 + strlen(son1_source) + 1,sizeof(char));
				sprintf(buffer,"%s != %s", son0_source, son1_source);
				return buffer;
				break;
			}

			case ASTREE_AND:
			{
				char* son0_source = astreeDecompile(ast->son[0]);
				char* son1_source = astreeDecompile(ast->son[1]);
				char* buffer = (char*)calloc( strlen(son0_source) + 4 + strlen(son1_source) + 1,sizeof(char));
				sprintf(buffer,"%s && %s", son0_source, son1_source);
				return buffer;
				break;
			}

			case ASTREE_OR:
			{
				char* son0_source = astreeDecompile(ast->son[0]);
				char* son1_source = astreeDecompile(ast->son[1]);
				char* buffer = (char*)calloc( strlen(son0_source) + 4 + strlen(son1_source) + 1,sizeof(char));
				sprintf(buffer,"%s || %s", son0_source, son1_source);
				return buffer;
				break;
			}

			case ASTREE_MULT:
			{
				char* son0_source = astreeDecompile(ast->son[0]);
				char* son1_source = astreeDecompile(ast->son[1]);
				char* buffer = (char*)calloc( strlen(son0_source) + 3 + strlen(son1_source) + 1,sizeof(char));
				sprintf(buffer,"%s * %s", son0_source, son1_source);
				return buffer;
				break;
			}

			case ASTREE_ADD:
			{
				char* son0_source = astreeDecompile(ast->son[0]);
				char* son1_source = astreeDecompile(ast->son[1]);
				char* buffer = (char*)calloc( strlen(son0_source) + 3 + strlen(son1_source) + 1,sizeof(char));
				sprintf(buffer,"%s + %s", son0_source, son1_source);
				return buffer;
				break;
			}

			case ASTREE_SUB:
			{
				char* son0_source = astreeDecompile(ast->son[0]);
				char* son1_source = astreeDecompile(ast->son[1]);
				char* buffer = (char*)calloc( strlen(son0_source) + 3 + strlen(son1_source) + 1,sizeof(char));
				sprintf(buffer,"%s - %s", son0_source, son1_source);
				return buffer;
				break;
			}

			case ASTREE_DIV:
			{
				char* son0_source = astreeDecompile(ast->son[0]);
				char* son1_source = astreeDecompile(ast->son[1]);
				char* buffer = (char*)calloc( strlen(son0_source) + 3 + strlen(son1_source) + 1,sizeof(char));
				sprintf(buffer,"%s / %s", son0_source, son1_source);
				return buffer;
				break;
			}

			case ASTREE_LESS:
			{
				char* son0_source = astreeDecompile(ast->son[0]);
				char* son1_source = astreeDecompile(ast->son[1]);
				char* buffer = (char*)calloc( strlen(son0_source) + 3 + strlen(son1_source) + 1,sizeof(char));
				sprintf(buffer,"%s < %s", son0_source, son1_source);
				return buffer;
				break;
			}

			case ASTREE_GREATER:
			{
				char* son0_source = astreeDecompile(ast->son[0]);
				char* son1_source = astreeDecompile(ast->son[1]);
				char* buffer = (char*)calloc( strlen(son0_source) + 3 + strlen(son1_source) + 1,sizeof(char));
				sprintf(buffer,"%s > %s", son0_source, son1_source);
				return buffer;
				break;
			}

			case ASTREE_ARGS:
			{
				char* son0_source = astreeDecompile(ast->son[0]);
				char* son1_source = astreeDecompile(ast->son[1]);
				char* buffer = (char*)calloc( strlen(son0_source) + strlen(son1_source) + 1,sizeof(char));
				sprintf(buffer,"%s%s", son0_source, son1_source);
				return buffer;
				break;
			}

			case ASTREE_ARGSTAIL:
			{
				char* son0_source = astreeDecompile(ast->son[0]);
				char* son1_source = astreeDecompile(ast->son[1]);
				char* buffer = (char*)calloc( 2 + strlen(son0_source) + strlen(son1_source) + 1,sizeof(char));
				sprintf(buffer,", %s%s", son0_source, son1_source);
				return buffer;
				break;
			}

		}
  }
}
