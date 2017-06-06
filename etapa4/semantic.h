#ifndef SEMANTIC_H
#define SEMANTIC_H
#include "astree.h"

void semanticVardec(ASTREE* node);
void semanticFuncdec(ASTREE* node);
void semanticSetDeclarations(ASTREE* node);
void semanticCheck(ASTREE* node);

#endif
