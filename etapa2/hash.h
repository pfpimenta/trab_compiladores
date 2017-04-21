
#define TOKEN_TABLE_SIZE 997

#define SYMBOL_LIT_INTEGER 1
#define SYMBOL_LIT_REAL 2
#define SYMBOL_LIT_CHAR 3
#define SYMBOL_LIT_STRING 4
#define SYMBOL_TK_IDENTIFIER 5


typedef char* token_ref;
typedef int type_t;

union value_s
{
	int intLit;
	char charLit;
	int boolLit;
	char* stringLit;
	char* identifier;
};

struct symbol_s
{
	union value_s value;
	char* text;
	type_t type;
};

struct linkedList_s
{
	token_ref token;
	type_t type;
	struct linkedList_s* tail;
};

typedef struct linkedList_s linkedList_t;

typedef struct symbol_s symbol_t;

typedef linkedList_t** hashTable_ref;


// LinkedList

linkedList_t* nil(void);

int isEmpty(linkedList_t list);

linkedList_t* cons(token_ref token, type_t type, linkedList_t* list);

linkedList_t* find(token_ref token, linkedList_t list);


// HashTable

int hashFunction(token_ref token, int tableSize);

hashTable_ref newHashTable(int size);

linkedList_t* addToTable(token_ref token, type_t type, hashTable_ref table, int tableSize);

linkedList_t* findInTable(token_ref token, hashTable_ref table, int tableSize);


// TokenTable

void initMe(void);

linkedList_t* addToken(token_ref token, type_t type);

linkedList_t* findToken(token_ref token);


// Printing Table

void printType(type_t type);

void printSymbol(symbol_t symbol);

void printList(linkedList_t* list);

void printTable(hashTable_ref table, int tableSize);

void printSymbolTable(void);
