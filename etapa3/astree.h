#ifndef ASTREE_H
#define ASTREE_H


#include <stdlib.h>
#include <stdio.h>

#include "hash.h"

#define MAX_SONS 4

#define PROGRAM 0
#define VARDEC 1
#define KWBYTE 2
#define KWFLOAT 3
#define INTLIST 4
#define FLOATLIST 5
#define CHARLIST 6
#define ASTREE_SYMBOL 111
#define ASTREE_ADD 211


typedef struct astree
{
    int type;
    HASH_NODE* symbol;
    struct ASTREE* son[MAX_SONS];
} ASTREE;


ASTREE* astreeCreate(int type, HASH_NODE* symbol, ASTREE* son0, ASTREE* son1, ASTREE* son2, ASTREE* son3);

void astreePrint(ASTREE* node, int level);

#endif