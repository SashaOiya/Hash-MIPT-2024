#ifndef HASH
#define HASH

#include <stdio.h>
#include "hashtest.h"

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
    struct QueueElem *QueueElem; 
    int recency;
    struct Cache_Elem_t* CacheElem;
};

struct HashTable* hash_table_create(int n);

struct HashTableElem** hash_create(int n);

struct HashTableElem* find(int key, struct HashTable* HashTable);

struct HashTableElem* hash_table_elem_create(int key, struct Queue* Queue, struct HashTable* HashTable);

void hash_table_elem_insert(int key, struct HashTable* HashTable, struct Queue* Queue);

void delete_hash_table_elem(struct HashTableElem* ElemForDelete, struct HashTable* HashTable);

int elt(int key, int n);

void hash_dtor(struct HashTable* HashTable);

void hash_list_dtor(struct HashTableElem* top);

#endif

