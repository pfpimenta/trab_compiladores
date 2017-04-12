
#define SYMBOL_TABLE_SIZE 997

typedef char* symbol_ref;
typedef int type_t;

struct linkedList_s
{
	symbol_ref symbol;
	type_t type;
	struct linkedList_s* tail;
};

typedef struct linkedList_s linkedList_t;

typedef linkedList_t** hashTable_ref;

// Symbol module

void printSymbol(symbol_ref symbol);

// LinkedList module

linkedList_t* nil(void);

int isEmpty(linkedList_t list);

linkedList_t* cons(symbol_ref symbol, type_t type, linkedList_t* list);

linkedList_t* find(symbol_ref symbol, linkedList_t list);

void printList(linkedList_t list);

// HashTable module

int hashFunction(symbol_ref symbol, int tableSize);

hashTable_ref newHashTable(int size);

linkedList_t* addToTable(symbol_ref symbol, type_t type, hashTable_ref table, int tableSize);

linkedList_t* findInTable(symbol_ref symbol, hashTable_ref table, int tableSize);

void printTable(hashTable_ref table, int tableSize);

// SymbolTable module

void initMe(void);

linkedList_t* addSymbol(symbol_ref symbol, type_t type);

linkedList_t* findSymbol(symbol_ref symbol);

void printSymbolTable(void);
