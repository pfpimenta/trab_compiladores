#ifndef ASTREE_H
#define ASTREE_H


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"

#define MAX_SONS 4


#define ASTREE_PROGRAM 0
#define ASTREE_VARDEC 1
#define ASTREE_KWCHAR 2
#define ASTREE_KWINT 3
#define ASTREE_KWREAL 7
#define ASTREE_KWARRAYINT 9
#define ASTREE_KWARRAYCHAR 10
#define ASTREE_KWARRAYFLOAT 16
#define ASTREE_KWARRAY 20
#define ASTREE_INTLIST 21
#define ASTREE_LITINT 22
#define ASTREE_CHARLIST 23
#define ASTREE_LITCHAR 24
#define ASTREE_FLOATLIST 25
#define ASTREE_LITREAL 26
#define ASTREE_FUNCDEC 27
#define ASTREE_PARAMLIST 28
#define ASTREE_PARAM 29
#define ASTREE_KWBYTE 30
#define ASTREE_KWSHORT 31
#define ASTREE_KWLONG 32
#define ASTREE_KWFLOAT 33
#define ASTREE_KWDOUBLE 34
#define ASTREE_CMDLIST 35
#define ASTREE_CMDCOLCHETES 36
#define ASTREE_KWREAD 37
#define ASTREE_KWPRINT 38
#define ASTREE_KWRETURN 39
#define ASTREE_PRINTLIST 40
#define ASTREE_LITSTRING 41
#define ASTREE_KWWHENTHEN 42
#define ASTREE_KWWHENTHENELSE 43
#define ASTREE_KWWHILE 44
#define ASTREE_KWFOR 45
#define ASTREE_ATRIB 46
#define ASTREE_ATRIBARRAY 47
#define ASTREE_EXPRPARENTESIS 48
#define ASTREE_TKID 49
#define ASTREE_TKIDARRAY 50
#define ASTREE_TKIDFUNC 51
#define ASTREE_LESSEQUAL 52
#define ASTREE_GREATEREQUAL 53
#define ASTREE_EQUAL 54
#define ASTREE_NOTEQUAL 55
#define ASTREE_AND 56
#define ASTREE_OR 57
#define ASTREE_MULT 58
#define ASTREE_ADD 59
#define ASTREE_SUB 60
#define ASTREE_DIV 61
#define ASTREE_LESS 62
#define ASTREE_GREATER 63
#define ASTREE_ARGS 64
#define ASTREE_ARGSTAIL 65


typedef struct astree
{
    int type;
    HASH_NODE* symbol;
    struct astree* son[MAX_SONS];

} ASTREE;

ASTREE* root;

ASTREE* astreeCreate(int type, HASH_NODE* symbol, ASTREE* son0, ASTREE* son1, ASTREE* son2, ASTREE* son3);

void astreePrint(ASTREE* node, int level);

void astreeNodePrint(ASTREE* node);

char* astreeDecompile(ASTREE* ast);

#endif
