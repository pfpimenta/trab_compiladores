#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

hashTable_ref symbolTable;

// LinkedList module

linkedList_t* nil(void)
{
	linkedList_t* list = (linkedList_t*) malloc( sizeof(linkedList_t) );

	list->symbol = NULL;
	list->tail = NULL;

	return list;
}

int isEmpty(linkedList_t list)
{
	return list.symbol == NULL;
}

linkedList_t* cons(symbol_ref symbol, type_t type, linkedList_t* list)
{
	if(list == NULL)
	{
		return NULL;
	}
	else
	{
		linkedList_t* newList = (linkedList_t*) malloc( sizeof(linkedList_t) );

		newList->symbol = (symbol_ref) malloc( strlen(symbol) );
		strcpy(newList->symbol, symbol);
		newList->type = type;

		newList->tail = list;

		return newList;
	}
}

linkedList_t* find(symbol_ref symbol, linkedList_t list)
{
	linkedList_t* aux = &list;

	while( !isEmpty(*aux) )
	{
		if(strcmp(aux->symbol, symbol) == 0)
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

int hashFunction(symbol_ref symbol, int tableSize)
{
	int index = 1;
	int i;

	for(i = 0; i < strlen(symbol); i++)
	{
		index = ( (index * symbol[i]) % tableSize ) + 1;
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

linkedList_t* addToTable(symbol_ref symbol, type_t type, hashTable_ref table, int tableSize)
{
	int index = hashFunction(symbol, tableSize);

	linkedList_t* pointer = find(symbol, *(table[index]));

	if(pointer != NULL)
	{
		return pointer;
	}
	else
	{
		table[index] = cons(symbol, type, table[index]);

		return table[index];
	}
}

linkedList_t* findInTable(symbol_ref symbol, hashTable_ref table, int tableSize)
{
	int index = hashFunction(symbol, tableSize);

	return find(symbol, *(table[index]));
}

// SymbolTable module

void initMe(void)
{
	symbolTable = newHashTable(SYMBOL_TABLE_SIZE);
}

linkedList_t* addSymbol(symbol_ref symbol, type_t type)
{
	return addToTable(symbol, type, symbolTable, SYMBOL_TABLE_SIZE);
}

linkedList_t* findSymbol(symbol_ref symbol)
{
	return findInTable(symbol, symbolTable, SYMBOL_TABLE_SIZE);
}

