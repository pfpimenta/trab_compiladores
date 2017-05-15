#ifndef ASTREE_H
#define ASTREE_H


#include <stdlib.h>
#include <stdio.h>

#include "hash.h"

#define MAX_SONS 4

#define PROGRAM 0
#define ASTREE_SYMBOL 1
#define ASTREE_ADD 2


typedef struct astree
{
    int type;
    HASH_NODE* symbol;
    struct ASTREE** son;
} ASTREE;


ASTREE* astreeCreate(int type, HASH_NODE* symbol, ASTREE* son0, ASTREE* son1, ASTREE* son2, ASTREE* son3);

void astreePrint(ASTREE* node, int level);

#endif