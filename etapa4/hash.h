#ifndef HASH_H
#define HASH_H

#define SYMBOL_TABLE_SIZE 997

#define SYMBOL_LIT_INTEGER 1
#define SYMBOL_LIT_REAL 2
#define SYMBOL_LIT_CHAR 3
#define SYMBOL_LIT_STRING 4
#define SYMBOL_TK_IDENTIFIER 5

#define DATATYPE_BYTE 1
#define DATATYPE_SHORT 2
#define DATATYPE_LONG 3
#define DATATYPE_FLOAT 4
#define DATATYPE_DOUBLE 5


#define NATURE_VAR 1
#define NATURE_ARRAY 2
#define NATURE_FUNC 3

typedef int type_t;
typedef int DATATYPE;
typedef int NATURE;

struct symbol_s
{
	char* text;
	type_t type;
	DATATYPE dataType;
	NATURE nature;
};

struct linkedList_s
{
	struct symbol_s symbol;
	struct linkedList_s* tail;
};

typedef struct symbol_s HASH_NODE;

typedef struct linkedList_s LINKED_LIST;

typedef LINKED_LIST** hashTable_ref;

// Symbol module

int equal(HASH_NODE symbol1, HASH_NODE symbol2);

// LinkedList module

LINKED_LIST* nil(void);

int isEmpty(LINKED_LIST* list);

LINKED_LIST* cons(HASH_NODE symbol, LINKED_LIST* list);

LINKED_LIST* find(HASH_NODE symbol, LINKED_LIST* list);


// HashTable module

int hashFunction(char* text, int tableSize);

hashTable_ref newHashTable(int size);

LINKED_LIST* addToTable(HASH_NODE symbol, hashTable_ref table, int tableSize);

LINKED_LIST* findInTable(HASH_NODE symbol, hashTable_ref table, int tableSize);

// SymbolTable module

void initMe(void);

LINKED_LIST* addSymbol(char* text, type_t type, DATATYPE dataType, NATURE nature);

LINKED_LIST* findSymbol(HASH_NODE symbol);


// Printing Table

void printSymbol(HASH_NODE symbol);

void printType(type_t type);

void printList(LINKED_LIST* list);

void printTable(hashTable_ref table, int tableSize);

void printSymbolTable(void);

#endif
