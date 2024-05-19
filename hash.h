#ifndef HASH
#define HASH

#include <stdio.h>

enum {
    NON_RESIDENT,
    RESIDENT,
};

struct HashTable {
    struct HashTableElem** hash;
    int HashSize;
};

struct HashTableElem {
    struct HashTableElem *next;
    struct HashTableElem *prev;
    int key;
    struct Queue *QueueElem; 
    int recency;
    struct Cache_Elem_t* CacheElem;
};

struct HashTable* hash_table_create(int n);

struct HashTableElem** hash_create(int n);

struct HashTableElem* find(int key, struct HashTable* HashTable);

struct HashTableElem* hash_table_elem_create(int key, struct Queue* top, struct HashTable* HashTable);

void hash_table_elem_insert(int key, struct HashTable* HashTable, struct Queue* top);

void delete_hash_table_elem(struct HashTableElem* ElemForDelete, struct HashTable* HashTable);

int elt(int key, int n);

void hash_dtor(struct HashTable* HashTable);

void hash_list_dtor(struct HashTableElem* top);

//for testing
//////////////////////////////////////////////////////////////////////////////////////////

struct Queue {
    struct QueueElem* top;
};

struct QueueElem {
    struct QueueElem *next;
    int key;
};

struct Queue* queue_node_create(int key, struct Queue* top);

int test1(void);

int test2(void);

int test3(void);

//////////////////////////////////////////////////////////////////////////////////////////

#endif

