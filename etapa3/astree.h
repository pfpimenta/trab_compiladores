
struct astree
{
    int type;
    HASH_NODE* symbol;
    ASTREE* son;
};

typedef struct astree ASTREE;

ASTREE* astreeCreate(int type, HASH_NODE* symbol,
                    ASTREE* son0, ASTREE* son1, ASTREE* son2, ASTREE* son3);
void astreePrint(ASTREE* node, int level)
