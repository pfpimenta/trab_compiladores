#define SYMBOL_TABLE_SIZE 997

#define SYMBOL_LIT_INTEGER 1
#define SYMBOL_LIT_REAL 2
#define SYMBOL_LIT_CHAR 3
#define SYMBOL_LIT_STRING 4
#define SYMBOL_TK_IDENTIFIER 5

typedef int type_t;

struct symbol_s
{
	char* text;
	type_t type;
};

struct linkedList_s
{
	struct symbol_s symbol;
	struct linkedList_s* tail;
};

typedef struct symbol_s HASH_NODE;

typedef struct linkedList_s linkedList_t;

typedef linkedList_t** hashTable_ref;

// Symbol module

int equal(HASH_NODE symbol1, HASH_NODE symbol2);

// LinkedList module

linkedList_t* nil(void);

int isEmpty(linkedList_t* list);

linkedList_t* cons(HASH_NODE symbol, linkedList_t* list);

linkedList_t* find(HASH_NODE symbol, linkedList_t* list);


// HashTable module

int hashFunction(char* text, int tableSize);

hashTable_ref newHashTable(int size);

linkedList_t* addToTable(HASH_NODE symbol, hashTable_ref table, int tableSize);

linkedList_t* findInTable(HASH_NODE symbol, hashTable_ref table, int tableSize);

// SymbolTable module

void initMe(void);

linkedList_t* addSymbol(char* text, type_t type);

linkedList_t* findSymbol(HASH_NODE symbol);


// Printing Table

void printSymbol(HASH_NODE symbol);

void printType(type_t type);

void printList(linkedList_t* list);

void printTable(hashTable_ref table, int tableSize);

void printSymbolTable(void);
