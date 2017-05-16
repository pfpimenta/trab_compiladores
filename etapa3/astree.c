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
        case ASTREE_SYMBOL:
        {
            fprintf(stderr, "ASTREE_SYMBOL");
            break;
        }
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
        case ASTREE_SYMBOL:
        {
            fprintf(stderr, "ASTREE_SYMBOL");
            break;
        }
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

char* astreeDecompile(ASREE* ast)
{
	if(ast == NULL)
	{
		return "";
	}
	else
	{
		switch(ast->node_type)
		{

			case ASTREE_PROGRAM:
			{
				
				break;
			}

			case ASTREE_VARDEC:
			{
				char* son0_source = astreeDecompile(ast->son[0]);
				char* buffer = (char*)calloc(30 + 1 + strlen(son0_source) + 1,sizeof(char));
				sprintf(buffer,"%d:%s;)",ast->symbol.value,son0_source);
				return buffer;
				break;
			}

			case ASTREE_KWBYTECHAR:
			{
				
				break;
			}

			case ASTREE_KWBYTEINT:
			{
				
				break;
			}

			case ASTREE_KWSHORTINT:
			{
				
				break;
			}

			case ASTREE_KWLONGINT:
			{
				
				break;
			}

			case ASTREE_KWFLOATINT:
			{
				
				break;
			}

			case ASTREE_KWFLOATREAL:
			{
				
				break;
			}

			case ASTREE_KWDOUBLEINT:
			{
				
				break;
			}

			case ASTREE_KWBYTEARRAYINT:
			{
				
				break;
			}

			case ASTREE_KWBYTEARRAYCHAR:
			{
				
				break;
			}

			case ASTREE_KWBYTEARRAY:
			{
				
				break;
			}

			case ASTREE_KWSHORTARRAYINT:
			{
				
				break;
			}

			case ASTREE_KWSHORTARRAY:
			{
				
				break;
			}

			case ASTREE_KWLONGARRAYINT:
			{
				
				break;
			}

			case ASTREE_KWLONGARRAY:
			{
				
				break;
			}

			case ASTREE_KWFLOATARRAYFLOAT:
			{
				
				break;
			}

			case ASTREE_KWFLOATARRAYINT:
			{
				
				break;
			}

			case ASTREE_KWFLOATARRAY:
			{
				
				break;
			}

			case ASTREE_KWDOUBLEARRAYINT:
			{
				
				break;
			}

			case ASTREE_KWDOUBLEARRAY:
			{
				
				break;
			}

			case ASTREE_KWFLOATARRAYINT:
			{
				
				break;
			}

			case ASTREE_INTLIST:
			{
				
				break;
			}

			case ASTREE_LITINT:
			{
				
				break;
			}

			case ASTREE_CHARLIST:
			{
				
				break;
			}

			case ASTREE_LITCHAR :
			{
				
				break;
			}

			case ASTREE_FLOATLIST:
			{
				
				break;
			}

			case ASTREE_LITREAL:
			{
				
				break;
			}

			case ASTREE_FUNCDEC :
			{
				
				break;
			}

			case ASTREE_PARAMLIST:
			{
				
				break;
			}

			case ASTREE_PARAM:
			{
				
				break;
			}

			case ASTREE_KWBYTE :
			{
				
				break;
			}

			case ASTREE_KWSHORT:
			{
				
				break;
			}

			case ASTREE_KWLONG:
			{
				
				break;
			}

			case ASTREE_KWFLOAT:
			{
				
				break;
			}

			case ASTREE_KWDOUBLE:
			{
				
				break;
			}

			case ASTREE_CMDLIST:
			{
				
				break;
			}

			case ASTREE_CMDCOLCHETES :
			{
				
				break;
			}

			case ASTREE_KWREAD:
			{
				
				break;
			}

			case ASTREE_KWPRINT:
			{
				
				break;
			}


			case ASTREE_KWRETURN :
			{
				
				break;
			}

			case ASTREE_PRINTLIST:
			{
				
				break;
			}

			case ASTREE_LITSTRING:
			{
				
				break;
			}

			case ASTREE_KWWHENTHEN:
			{
				
				break;
			}

			case ASTREE_KWWHENTHENELSE:
			{
				
				break;
			}

			case ASTREE_KWWHILE :
			{
				
				break;
			}

			case ASTREE_KWFOR:
			{
				
				break;
			}

			case ASTREE_ATRIB:
			{
				
				break;
			}

			case ASTREE_ATRIBARRAY:
			{
				
				break;
			}

			case ASTREE_EXPRPARENTESIS:
			{
				
				break;
			}

			case ASTREE_TKID:
			{
				
				break;
			}

			case ASTREE_TKIDARRAY:
			{
				
				break;
			}

			case ASTREE_TKIDFUNC :
			{
				
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

			case ASTREE_ARGS:
			{
				
				break;
			}

			case ASTREE_ARGSTAIL:
			{
				
				break;
			}

		}









