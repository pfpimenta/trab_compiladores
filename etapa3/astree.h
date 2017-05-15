#include <stdlib.h>
#include <stdio.h>

#include "hash.h"

#define ASTREE_SYMBOL 0
#define ASTREE_ADD 1


typedef struct astree
{
    int type;
    HASH_NODE* symbol;
    struct ASTREE** son;
} ASTREE;


ASTREE* astreeCreate(int type, HASH_NODE* symbol, ASTREE* son0, ASTREE* son1, ASTREE* son2, ASTREE* son3);

void astreePrint(ASTREE* node, int level);
