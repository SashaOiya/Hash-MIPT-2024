#include <stdio.h>

struct HashTable {
    struct HashTable *next;
    int data;
    struct Queue *QueueElem; 
};

struct HashTable** hash_create(int n);

struct Queue* find(int key, struct Queue* top, struct HashTable** hash, int n);

struct HashTable* node_create(int key, struct Queue* top, int cell, struct HashTable** hash);

int elt(int key, int n);

