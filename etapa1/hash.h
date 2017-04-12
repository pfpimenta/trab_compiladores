
#define TOKEN_TABLE_SIZE 997

typedef char* token_ref;
typedef int type_t;

struct linkedList_s
{
	token_ref token;
	type_t type;
	struct linkedList_s* tail;
};

typedef struct linkedList_s linkedList_t;

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
