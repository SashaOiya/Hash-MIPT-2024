#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "hash.h"

struct HashTable* hash_table_create(int n) {
    struct HashTableElem** check = 0;
    struct HashTable* HashTable = 0;
    check = hash_create(n);
    assert(check);
    HashTable->hash = check;
    HashTable->HashSize = n;
}

struct HashTableElem** hash_create(int n) {
    struct HashTableElem** hash = 0;
    hash = (struct HashTableElem**)calloc(n, sizeof(struct HashTableElem*));
    return hash;
}

struct HashTableElem* find(int key, struct HashTable* HashTable) {
    int cell = 0;
    struct HashTableElem* temp = 0;
    cell = elt(key, HashTable->HashSize);
    temp = HashTable->hash[cell];
    if(HashTable->hash[cell] != NULL) {
        while(key != temp->key || temp->next != NULL) {
            if(temp->key == key) {
            return temp; 
            }
            temp = temp->next;
        }
    }
    return NULL;
}

void hash_table_elem_insert(int key, struct HashTable* HashTable, struct Queue* top) {
    int cell = 0;
    struct HashTableElem* new_node = 0;
    cell = elt(key, HashTable->HashSize);
    new_node = hash_table_elem_create(key, top, HashTable);
    assert(new_node);
    if(HashTable->hash[cell] == 0) {
        HashTable->hash[cell] = new_node;
    }
    else {
        new_node->next = HashTable->hash[cell];
        HashTable->hash[cell] = new_node;
    }
}

int elt(int key, int n) {
    return ((5 * key + 78) % 56) % n;
}

struct HashTableElem* hash_table_elem_create(int key, struct Queue* top, struct HashTable* HashTable) {
    int cell = 0;
    cell = elt(key, HashTable->HashSize);
    struct HashTableElem* new_node = 0;
    new_node = (struct HashTableElem*)calloc(1, sizeof(struct HashTableElem));
    new_node->key = key;
    new_node->QueueElem = queue_node_create(key, top); //smth creates node in the queue and returns pointer on the new node
    return new_node;
}

//for testing
//////////////////////////////////////////////////////////////////////////////////////////

struct Queue* queue_node_create(int key, struct Queue* top) {
    struct Queue* new_node = 0;
    new_node = (struct Queue*)calloc(1, sizeof(struct Queue));
    new_node->key = key;
    if(top != NULL) {
        new_node->next = top;
    }
    top = new_node;
    return top;
}

int test1(void) {
    int n = 3;
    struct HashTableElem** res = hash_create(n);
    printf("%p\n", res);
    return 1;
}

int test2(void) {

}

int test3(void) {
    int n = 1;
    struct HashTableElem** res = hash_create(n);
    find(1);
    find(1);

}

int main(void) {
    printf("test %d passed\n", test1());
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////