#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

hashTable_ref symbolTable;

// Symbol module

int equal(HASH_NODE symbol1, HASH_NODE symbol2)
{
	return (symbol1.type == symbol2.type) && (strcmp(symbol1.text, symbol2.text) == 0);
}

// LinkedList module

LINKED_LIST* nil(void)
{
	return NULL;
}

int isEmpty(LINKED_LIST* list)
{
	return list == NULL;
}

LINKED_LIST* cons(HASH_NODE symbol, LINKED_LIST* list)
{
	LINKED_LIST* newList = (LINKED_LIST*) malloc( sizeof(LINKED_LIST) );

	newList->symbol = symbol;
	newList->tail = list;

	return newList;
}

LINKED_LIST* find(HASH_NODE symbol, LINKED_LIST* list)
{
	LINKED_LIST* aux = list;

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
	hashTable_ref table = (hashTable_ref) calloc(size, sizeof(LINKED_LIST*));
	int i;

	for(i = 0; i < size; i++)
	{
		table[i] = nil();
	}

	return table;
}

LINKED_LIST* addToTable(HASH_NODE symbol, hashTable_ref table, int tableSize)
{
	int index = hashFunction(symbol.text, tableSize);

	LINKED_LIST* pointer = find(symbol, table[index]);

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

LINKED_LIST* findInTable(HASH_NODE symbol, hashTable_ref table, int tableSize)
{
	int index = hashFunction(symbol.text, tableSize);

	return find(symbol, table[index]);
}


// SymbolTable module

void initMe(void)
{
	symbolTable = newHashTable(SYMBOL_TABLE_SIZE);
}

LINKED_LIST* addSymbol(char* text, type_t type, DATATYPE dataType, NATURE nature)
{
	HASH_NODE symbol;
	symbol.text = (char*) calloc(strlen(text) + 1, sizeof(char));
	strcpy(symbol.text, text);
	symbol.type = type;
	symbol.dataType = dataType;
	symbol.nature = nature;
	//numParameters nao é passado por parametro
	symbol.numParameters = -1;
	symbol.isDeclared = 0;
	symbol.exprType = 0;

	return addToTable(symbol, symbolTable, SYMBOL_TABLE_SIZE);
}

LINKED_LIST* findSymbol(HASH_NODE symbol)
{
	return findInTable(symbol, symbolTable, SYMBOL_TABLE_SIZE);
}

// Printing Tables

void printSymbol(HASH_NODE symbol)
{
	fprintf(stderr,"\nHASH_NODE:");
	fprintf(stderr,"\ntext: %s",symbol.text);
	fprintf(stderr,"\ntype: ");
	printType(symbol.type);
	fprintf(stderr,"\ndataType: ");
	printDatatype(symbol.dataType);
	fprintf(stderr,"\nnature: ");
	printNature(symbol.nature);
	fprintf(stderr,"\nexprType: ");
	printExprType(symbol.exprType);
	fprintf(stderr,"\nnumParameters: %i", symbol.numParameters);
	fprintf(stderr,"\nisDeclared: %i", symbol.isDeclared);
	fprintf(stderr,"\n\n");
}

void printExprType(int exprType)
{
	switch(exprType)
	{
		case EXPR_INTEGER:
			fprintf(stderr,"integer");
			break;
		case EXPR_REAL:
			fprintf(stderr,"real");
			break;
		case EXPR_CHAR:
			fprintf(stderr,"char");
			break;
		case EXPR_STRING:
			fprintf(stderr,"string");
			break;
		case EXPR_BOOLEAN:
			fprintf(stderr,"bool");
			break;
	}
}

void printNature(NATURE nature)
{
	switch(nature)
	{
		case NATURE_VAR:
			fprintf(stderr,"var");
			break;
		case NATURE_ARRAY:
			fprintf(stderr,"array");
			break;
		case NATURE_FUNC:
			fprintf(stderr,"function");
			break;
	}
}

void printDatatype(DATATYPE dataType)
{
	switch(dataType)
	{
		case DATATYPE_BYTE:
			fprintf(stderr,"byte");
			break;
		case DATATYPE_SHORT:
			fprintf(stderr,"short");
			break;
		case DATATYPE_LONG:
			fprintf(stderr,"long");
			break;
		case DATATYPE_FLOAT:
			fprintf(stderr,"float");
			break;
		case DATATYPE_DOUBLE:
			fprintf(stderr,"double");
			break;
	}
}

void printType(type_t type)
{
	switch(type)
	{
		case SYMBOL_LIT_INTEGER:
			fprintf(stderr,"int");
			break;
		case SYMBOL_LIT_REAL:
			fprintf(stderr,"real");
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

void printList(LINKED_LIST* list)
{
	LINKED_LIST* aux = list;

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
