#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

hashTable_ref tokenTable;

// LinkedList module

linkedList_t* nil(void)
{
	linkedList_t* list = (linkedList_t*) malloc( sizeof(linkedList_t) );

	list->token = NULL;
	list->tail = NULL;

	return list;
}

int isEmpty(linkedList_t list)
{
	return list.token == NULL;
}

linkedList_t* cons(token_ref token, type_t type, linkedList_t* list)
{
	if(list == NULL)
	{
		return NULL;
	}
	else
	{
		linkedList_t* newList = (linkedList_t*) malloc( sizeof(linkedList_t) );

		newList->token = (token_ref) malloc( strlen(token) );
		strcpy(newList->token, token);
		newList->type = type;

		newList->tail = list;

		return newList;
	}
}

linkedList_t* find(token_ref token, linkedList_t list)
{
	linkedList_t* aux = &list;

	while( !isEmpty(*aux) )
	{
		if(strcmp(aux->token, token) == 0)
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

int hashFunction(token_ref token, int tableSize)
{
	int index = 1;
	int i;

	for(i = 0; i < strlen(token); i++)
	{
		index = ( (index * token[i]) % tableSize ) + 1;
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

linkedList_t* addToTable(token_ref token, type_t type, hashTable_ref table, int tableSize)
{
	int index = hashFunction(token, tableSize);

	linkedList_t* pointer = find(token, *(table[index]));

	if(pointer != NULL)
	{
		return pointer;
	}
	else
	{
		table[index] = cons(token, type, table[index]);

		return table[index];
	}
}

linkedList_t* findInTable(token_ref token, hashTable_ref table, int tableSize)
{
	int index = hashFunction(token, tableSize);

	return find(token, *(table[index]));
}

// TokenTable module

void initMe(void)
{
	tokenTable = newHashTable(TOKEN_TABLE_SIZE);
}

linkedList_t* addToken(token_ref token, type_t type)
{
	return addToTable(token, type, tokenTable, TOKEN_TABLE_SIZE);
}

linkedList_t* findToken(token_ref token)
{
	return findInTable(token, tokenTable, TOKEN_TABLE_SIZE);
}

