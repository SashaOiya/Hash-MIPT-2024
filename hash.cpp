#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "hash.h"
#include "hashtest.h"

struct HashTable* hash_table_create(int n) {
    struct HashTableElem** check = 0;
    struct HashTable* HashTable = 0;
    HashTable = (struct HashTable*)calloc(1, sizeof(struct HashTable));
    assert(HashTable);
    check = hash_create(n);
    assert(check);
    HashTable->hash = check;
    HashTable->HashSize = n;
    return HashTable;
}

struct HashTableElem** hash_create(int n) {
    struct HashTableElem** hash = 0;
    hash = (struct HashTableElem**)calloc(n, sizeof(struct HashTableElem*));
    assert(hash);
    return hash;
}

struct HashTableElem* find(int key, struct HashTable* HashTable) {
    int cell = 0;
    struct HashTableElem* temp = 0;
    cell = elt(key, HashTable->HashSize);
    temp = HashTable->hash[cell];
    if(HashTable->hash[cell] != NULL) {
        while(temp->key != key && temp->next != NULL) {
            temp = temp->next;
        }
        if(temp->key == key) {
            return temp; 
        }
        else {
            return NULL;
        }
    }
    else {
        return NULL;
    }
}

void hash_table_elem_insert(int key, struct HashTable* HashTable, struct Queue* Queue) {
    int cell = 0;
    struct HashTableElem* new_node = 0;
    cell = elt(key, HashTable->HashSize);
    new_node = hash_table_elem_create(key, Queue, HashTable);
    assert(new_node);
    if(HashTable->hash[cell] == 0) {
        HashTable->hash[cell] = new_node;
    }
    else {
        new_node->next = HashTable->hash[cell];
        HashTable->hash[cell]->prev = new_node;
        HashTable->hash[cell] = new_node;
    }
}

int elt(int key, int n) {
    return ((5 * key + 78) % 56) % n;
}

struct HashTableElem* hash_table_elem_create(int key, struct Queue* Queue, struct HashTable* HashTable) {
    int cell = 0;
    cell = elt(key, HashTable->HashSize);
    struct HashTableElem* new_node = 0;
    new_node = (struct HashTableElem*)calloc(1, sizeof(struct HashTableElem));
    assert(new_node);
    new_node->key = key;
    new_node->recency = RESIDENT;
    new_node->QueueElem = queue_node_create(key, Queue); //smth creates node in the queue and returns pointer on the new node
    return new_node;
}

void delete_hash_table_elem(struct HashTableElem* ElemForDelete, struct HashTable* HashTable) {
    if(ElemForDelete->prev == NULL) {
        int cell = 0;
        cell = elt(ElemForDelete->key, HashTable->HashSize);
        HashTable->hash[cell] = ElemForDelete->next;
    }
    else {
        ElemForDelete->prev->next = ElemForDelete->next;
    }
    free(ElemForDelete);
}

void hash_dtor(struct HashTable* HashTable) {
    for(int i = 0; i < HashTable->HashSize; i++) {
        if(HashTable->hash[i] != NULL) {
            hash_list_dtor(HashTable->hash[i]);
            HashTable->hash[i] = NULL;
        }
    }
    free(HashTable->hash);
    free(HashTable);
}

void hash_list_dtor(struct HashTableElem* top) {
    while(top->next != NULL) {
        top = top->next;
    }
    while(top->prev != NULL) {
        free(top->next);
        top = top->prev;
        }
    free(top);
}