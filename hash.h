#ifndef HASH
#define HASH

#include <stdio.h>
//#include "hashtest.h"

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
    
    struct Cache_Elem_t* ListElem;
};

struct HashTable* hash_table_create(int n); //creates structure with a hash table

struct HashTableElem** hash_create(int n); //creates an array (hash)

struct HashTableElem* find(int key, struct HashTable* HashTable); //finds a key in the hash table; returns pointer on a node of the hash table, where key is

struct HashTableElem* hash_table_elem_create(int key, struct Queue* Queue, struct HashTable* HashTable); //creates a node of a list in the hash table

void hash_table_elem_insert(int key, struct HashTable* HashTable, struct Queue* Queue); //inserts new node in the hash table

void delete_hash_table_elem(struct HashTableElem* ElemForDelete, struct HashTable* HashTable); //deletes a node

int elt(int key, int n); //hash function

void hash_dtor(struct HashTable* HashTable); //destructs the hash

void hash_list_dtor(struct HashTableElem* top); //destructs lists in the hash

#endif

