#ifndef SEMANTIC_H
#define SEMANTIC_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"
#include "astree.h"


int getExprType(ASTREE* node);
int getNumParameters(ASTREE* node);
void semanticVardec(ASTREE* node);
void semanticFuncdec(ASTREE* node);
void semanticParam(ASTREE* node);
void semanticSetDeclarations(ASTREE* node);
void semanticCheck(ASTREE* node);

#endif
