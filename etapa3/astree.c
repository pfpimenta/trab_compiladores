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
    for(i=0; i < level; i++)
    {
        fprintf(stderr, "  ");
    }

    fprintf(stderr, "ASTREE(");
    switch(node->type)
    {
        case ASTREE_ADD:
        {
            fprintf(stderr,"ASTREE_ADD");
            break;
        }
    }
    if(node->symbol)
        fprintf(stderr, ",%s", node->symbol->text); // CHECK print (?)
    else
        fprintf(stderr, ",");
    for(i=0; i < MAX_SONS; i++)
    {
        astreePrint(node->son[i], level+1);
    }
};

void astreeNodePrint(ASTREE* node)
{
    if(!node) return;
    fprintf(stderr, "ASTREE NODE(");
    switch(node->type)
    {
        case ASTREE_ADD:
        {
            fprintf(stderr,"ASTREE_ADD");
            break;
        }
    }
    if(node->symbol)
        fprintf(stderr, ",%s", node->symbol->text); // CHECK print (?)
    else
        fprintf(stderr, ",");

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

			case ASTREE_KWBYTECHAR:
			{
				char* buffer = (char*)calloc(5 + strlen(ast->symbol->text)+1,sizeof(char));
				sprintf(buffer,"byte %s", ast->symbol->text);
				return buffer;
				break;
			}

			case ASTREE_KWBYTEINT:
			{
				char* buffer = (char*)calloc(5 + strlen(ast->symbol->text)+1,sizeof(char));
				sprintf(buffer,"byte %s", ast->symbol->text);
				return buffer;
				break;
			}

			case ASTREE_KWSHORTINT:
			{
				char* buffer = (char*)calloc(6 + strlen(ast->symbol->text)+1,sizeof(char));
				sprintf(buffer,"short %s", ast->symbol->text);
				return buffer;
				break;
			}

			case ASTREE_KWLONGINT:
			{
				char* buffer = (char*)calloc(5 + strlen(ast->symbol->text)+1,sizeof(char));
				sprintf(buffer,"long %s", ast->symbol->text);
				return buffer;
				break;
			}

			case ASTREE_KWFLOATINT:
			{
				char* buffer = (char*)calloc(6 + strlen(ast->symbol->text)+1,sizeof(char));
				sprintf(buffer,"float %s", ast->symbol->text);
				return buffer;
				break;
			}

			case ASTREE_KWFLOATREAL:
			{
				char* buffer = (char*)calloc(6 + strlen(ast->symbol->text)+1,sizeof(char));
				sprintf(buffer,"float %s", ast->symbol->text);
				return buffer;
				break;
			}

			case ASTREE_KWDOUBLEINT:
			{
				char* buffer = (char*)calloc(7 + strlen(ast->symbol->text) + 1,sizeof(char));
				sprintf(buffer,"double %s", ast->symbol->text);
				return buffer;
				break;
			}

			case ASTREE_KWBYTEARRAYINT:
			{
				char* son0_source = astreeDecompile(ast->son[0]);
				char* buffer = (char*)calloc(6 + strlen(ast->symbol->text) + 2 + strlen(son0_source) + 1,sizeof(char));
				sprintf(buffer,"byte [%s] %s", ast->symbol->text, son0_source);
				return buffer;
				break;
			}

			case ASTREE_KWBYTEARRAYCHAR:
			{
				char* son0_source = astreeDecompile(ast->son[0]);
				char* buffer = (char*)calloc(6 + strlen(ast->symbol->text) + 2 + strlen(son0_source) + 1 ,sizeof(char));
				sprintf(buffer,"byte [%s] %s", ast->symbol->text, son0_source);
				return buffer;
				break;
			}

			case ASTREE_KWBYTEARRAY:
			{

				char* buffer = (char*)calloc(6 + strlen(ast->symbol->text) + 1 + 1,sizeof(char));
				sprintf(buffer,"byte [%s]", ast->symbol->text);
				return buffer;
				break;
			}

			case ASTREE_KWSHORTARRAYINT:
			{
				char* son0_source = astreeDecompile(ast->son[0]);
				char* buffer = (char*)calloc(7 + strlen(ast->symbol->text) + 2 + strlen(son0_source) + 1,sizeof(char));
				sprintf(buffer,"short [%s] %s", ast->symbol->text, son0_source);
				return buffer;
				break;
			}

			case ASTREE_KWSHORTARRAY:
			{
				char* buffer = (char*)calloc(7 + strlen(ast->symbol->text) + 1 + 1,sizeof(char));
				sprintf(buffer,"short [%s]", ast->symbol->text);
				return buffer;
				break;
			}

			case ASTREE_KWLONGARRAYINT:
			{
				char* son0_source = astreeDecompile(ast->son[0]);
				char* buffer = (char*)calloc(6 + strlen(ast->symbol->text) + 2 + strlen(son0_source) + 1,sizeof(char));
				sprintf(buffer,"long [%s] %s", ast->symbol->text, son0_source);
				return buffer;
				break;
			}

			case ASTREE_KWLONGARRAY:
			{
				char* buffer = (char*)calloc(6 + strlen(ast->symbol->text) + 1 + 1,sizeof(char));
				sprintf(buffer,"long [%s]", ast->symbol->text);
				return buffer;
				break;
			}

			case ASTREE_KWFLOATARRAYFLOAT:
			{
				char* son0_source = astreeDecompile(ast->son[0]);
				char* buffer = (char*)calloc(7 + strlen(ast->symbol->text) + 2 + strlen(son0_source) + 1,sizeof(char));
				sprintf(buffer,"float [%s] %s", ast->symbol->text, son0_source);
				return buffer;
				break;
			}

			case ASTREE_KWFLOATARRAYINT:
			{
				char* son0_source = astreeDecompile(ast->son[0]);
				char* buffer = (char*)calloc(7 + strlen(ast->symbol->text) + 1 + strlen(son0_source) + 1,sizeof(char));
				sprintf(buffer,"float [%s] %s", ast->symbol->text, son0_source);
				return buffer;
				break;
			}

			case ASTREE_KWFLOATARRAY:
			{
				char* buffer = (char*)calloc(7 + strlen(ast->symbol->text) + 1 + 1,sizeof(char));
				sprintf(buffer,"float [%s]", ast->symbol->text);
				return buffer;
				break;
			}

			case ASTREE_KWDOUBLEARRAYINT:
			{
				char* son0_source = astreeDecompile(ast->son[0]);
				char* buffer = (char*)calloc(8 + strlen(ast->symbol->text) + 2 + strlen(son0_source) + 1,sizeof(char));
				sprintf(buffer,"double [%s] %s", ast->symbol->text, son0_source);
				return buffer;
				break;
			}

			case ASTREE_KWDOUBLEARRAY:
			{
				char* buffer = (char*)calloc(8 + strlen(ast->symbol->text) + 1 + 1,sizeof(char));
				sprintf(buffer,"double [%s]", ast->symbol->text);
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
