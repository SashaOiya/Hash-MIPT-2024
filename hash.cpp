#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

struct HashTable** hash_create(int n) {
    struct HashTable** hash = 0;
    hash = (struct HashTable**)calloc(n, sizeof(struct HashTable*));
    return hash;
}

struct Queue* find(int key, struct Queue* top, struct HashTable** hash, int n) {
    int cell = 0;
    struct HashTable* temp = 0;
    cell = elt(key, n);
    temp = hash[cell];
    if(hash[cell] != NULL) {
        while(key != temp->data) {
            temp = temp->next;
        }
        return temp->QueueElem; 
    }
    else {
        node_create(key, top, cell, hash);
    }
}

int elt(int key, int n) {
    return ((5 * key + 78) % 56) % n;
}

struct HashTable* node_create(int key, struct Queue* top, int cell, struct HashTable** hash) {
    struct HashTable* new_node = 0;
    new_node = (struct HashTable*)calloc(1, sizeof(struct HashTable));
    hash[cell] = new_node;
    new_node->data = key;
    new_node->QueueElem = queue_node_create(); //smth creates node in the queue and returns pointer on the new node
}