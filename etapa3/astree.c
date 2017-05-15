#include "astree.h"
#include <stdio.h>

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
    if(!node) return;
    //for i in level print ("  ")
    fprintf(stderr, "ASTREE(");
    switch(node->type)
    {
        case ASTREE_SYMBOL: fprintf(stderr, "ASTREE_SYMBOL"); break;
        case ASTREE_ADD: fprintf(stderr,"ASTREE_ADD"); break;
    }
    if(node->symbol)
        fprintf(stderr, ",%s", node->symbol->text); // CHECK print (?)
    else
        fprintf(stderr, ",");
};
