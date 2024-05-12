#ifndef HASH
#define HASH

#include <stdio.h>

//разбить функцию файнд и креэйт

struct HashTable {
    struct HashTableElem** hash;
    int HashSize;
};

struct HashTableElem {
    struct HashTableElem *next;
    int key; 
    struct Queue *QueueElem; 
};

struct HashTable* hash_table_create(int n);

struct HashTableElem** hash_create(int n);

struct Queue* find(int key, struct Queue* top, struct HashTableElem** hash, int n);

struct HashTableElem* hash_table_elem_create(int key, struct Queue* top, int cell, struct HashTableElem** hash);

//hash_table_elem_insert -> create -> ann's create

// возращается адрес на ячейку спика хэш таблицы 

int elt(int key, int n);

//for testing
//////////////////////////////////////////////////////////////////////////////////////////

struct Queue {
    struct Queue *next;
    int key;
};

struct Queue* queue_node_create(int key, struct Queue* top);

int test1(void);

int test2(void);

int test3(void);

//////////////////////////////////////////////////////////////////////////////////////////

#endif

