#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

hashTable_ref symbolTable;

// Symbol module

int equal(symbol_t symbol1, symbol_t symbol2)
{
	return (symbol1.type == symbol2.type) && (strcmp(symbol1.text, symbol2.text) == 0);
}

// LinkedList module

linkedList_t* nil(void)
{
	return NULL;
}

int isEmpty(linkedList_t* list)
{
	return list == NULL;
}

linkedList_t* cons(symbol_t symbol, linkedList_t* list)
{
	linkedList_t* newList = (linkedList_t*) malloc( sizeof(linkedList_t) );

	newList->symbol = symbol;
	newList->tail = list;

	return newList;
}

linkedList_t* find(symbol_t symbol, linkedList_t* list)
{
	linkedList_t* aux = list;

	while( !isEmpty(aux) )
	{
		if(equal(aux->symbol, symbol))
		{
			return aux;
		}
		else
		{
			aux = aux->tail;
		}
	}

	return NULL;
}


// HashTable module

int hashFunction(char* text, int tableSize)
{
	int index = 1;
	int i;

	for(i = 0; i < strlen(text); i++)
	{
		index = ( (index * text[i]) % tableSize ) + 1;
	}	

	return index - 1;
}

hashTable_ref newHashTable(int size)
{
	hashTable_ref table = (hashTable_ref) calloc(size, sizeof(linkedList_t*));
	int i;

	for(i = 0; i < size; i++)
	{
		table[i] = nil();
	}

	return table;
}

linkedList_t* addToTable(symbol_t symbol, hashTable_ref table, int tableSize)
{
	int index = hashFunction(symbol.text, tableSize);

	linkedList_t* pointer = find(symbol, table[index]);

	if(pointer != NULL)
	{
		return pointer;
	}
	else
	{
		table[index] = cons(symbol, table[index]);

		return table[index];
	}
}

linkedList_t* findInTable(symbol_t symbol, hashTable_ref table, int tableSize)
{
	int index = hashFunction(symbol.text, tableSize);

	return find(symbol, table[index]);
}


// SymbolTable module

void initMe(void)
{
	symbolTable = newHashTable(SYMBOL_TABLE_SIZE);
}

char* removeQuotes(char* s)
{
	int newLength = strlen(s) - 2;
	char* s2 = (char*) calloc(newLength + 1, sizeof(char));
	strncpy(s2, s + 1, newLength);

	return s2;
}

linkedList_t* addSymbol(char* text, type_t type)
{
	symbol_t symbol;
	symbol.text = (char*) calloc(strlen(text) + 1, sizeof(char));
	strcpy(symbol.text, text);
	symbol.type = type;

	return addToTable(symbol, symbolTable, SYMBOL_TABLE_SIZE);
}

linkedList_t* findSymbol(symbol_t symbol)
{
	return findInTable(symbol, symbolTable, SYMBOL_TABLE_SIZE);
}

// Printing Tables

void printSymbol(symbol_t symbol)
{
	fprintf(stderr,"(");
	fprintf(stderr,"%s",symbol.text);
	fprintf(stderr," : ");
	printType(symbol.type);
	fprintf(stderr,")");
}

void printType(type_t type)
{
	switch(type)
	{
		case SYMBOL_LIT_INTEGER:
			fprintf(stderr,"int");
			break;
		case SYMBOL_LIT_REAL:
			fprintf(stderr,"true");
			break;
		case SYMBOL_LIT_CHAR:
			fprintf(stderr,"char");
			break;
		case SYMBOL_LIT_STRING:
			fprintf(stderr,"string");
			break;
		case SYMBOL_TK_IDENTIFIER:
			fprintf(stderr,"id");
			break;
	}
}

void printList(linkedList_t* list)
{
	linkedList_t* aux = list;

	while( !isEmpty(aux) )
	{
		printSymbol(aux->symbol);
		
		fprintf(stderr," :: ");
		
		aux = aux->tail;
	}

	fprintf(stderr,"[]");
}

void printTable(hashTable_ref table, int tableSize)
{
	int i;

	fprintf(stderr,"{\n");

	for(i = 0; i < tableSize; i++)
	{
		fprintf(stderr,"\t");
		printList(table[i]);
		fprintf(stderr,"\n");
	}

	fprintf(stderr,"}\n");
}

void printSymbolTable(void)
{
	printTable(symbolTable, SYMBOL_TABLE_SIZE);
}