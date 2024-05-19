#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "hash.h"

struct HashTable* hash_table_create(int n) {
    struct HashTableElem** check = 0;
    struct HashTable* HashTable = 0;
    HashTable = (struct HashTable*)calloc(1, sizeof(struct HashTable));
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
}

void hash_dtor(struct HashTable* HashTable) {
    for(int i = 0; i < HashTable->HashSize; i++) {
        if(HashTable->hash[i] != NULL) {
            hash_list_dtor(HashTable->hash[i]);
        }
    }
    free(HashTable->hash);
    free(HashTable);
}

void hash_list_dtor(struct HashTableElem* top) {
    while(top->next != NULL) {
        top = top->next;
    }
    top = top->prev;
    while(top->prev != NULL) {
        free(top->next);
        top = top->prev;
    }
    free(top);
}

//for testing
//////////////////////////////////////////////////////////////////////////////////////////

struct QueueElem* queue_node_create(int key, struct Queue* Queue) {
    struct QueueElem* new_node = 0;
    new_node = (struct QueueElem*)calloc(1, sizeof(struct QueueElem));
    new_node->key = key;
    if(Queue->top != NULL) {
        new_node->next = Queue->top;
    }
    Queue->top = new_node;
    return Queue->top;
}

int test1(void) { //tests function hash_table_create and hash_create;
    int n = 3;
    struct HashTable* HashTable = hash_table_create(n);
    printf("Hash table pointer %p\n", HashTable);
    printf("Hash pointer %p\n", HashTable->hash);
    printf("size of hash = %d\n", HashTable->HashSize);
    for(int i = 0; i < n; i++) {
        printf("[%p]\n", HashTable->hash[i]);
    }
    return 1;
}

int test2(void) { //tests function hash_table_elem create
    int key = 23;
    int n = 4;
    struct Queue* Queue = 0;
    struct HashTableElem* hashelem = 0;
    Queue = (struct Queue*)calloc(1, sizeof(struct Queue));
    struct HashTable* HashTable = hash_table_create(n);

    hashelem = hash_table_elem_create(key, Queue, HashTable);

    printf("Hash table pointer %p\n", HashTable);
    printf("Hash pointer %p\n", HashTable->hash);
    printf("size of hash = %d\n", HashTable->HashSize);
    for(int i = 0; i < n; i++) {
        printf("[%p]\n", HashTable->hash[i]);
    }

    printf("Hash elem pointer %p\n", hashelem);
    printf("key %d\n", hashelem->key);
    printf("cache elem %p\n", hashelem->CacheElem);
    printf("next %p\n", hashelem->next);
    printf("prev %p\n", hashelem->prev);
    printf("queue elem %p\n", hashelem->QueueElem);
    printf("recency %d\n", hashelem->recency);

    return 2;
} 

int test3(void) { //tests hash_table_elem_insert
    int key = 48;
    int n = 5;
    struct Queue* Queue = 0;
    struct HashTableElem* hashelem = 0;
    Queue = (struct Queue*)calloc(1, sizeof(struct Queue));
    struct HashTable* HashTable = hash_table_create(n);

    hash_table_elem_insert(key, HashTable, Queue);

    printf("Hash table pointer %p\n", HashTable);
    printf("Hash pointer %p\n", HashTable->hash);
    printf("size of hash = %d\n", HashTable->HashSize);
    for(int i = 0; i < n; i++) {
        printf("[%p]\n", HashTable->hash[i]);
        if(HashTable->hash[i] != NULL) {
            printf("!!!!!!!!!!!!!!!!!!!!!!!!\n");
            printf("key %d\n", HashTable->hash[i]->key);
            printf("cache elem %p\n", HashTable->hash[i]->CacheElem);
            printf("next %p\n", HashTable->hash[i]->next);
            printf("prev %p\n", HashTable->hash[i]->prev);
            printf("queue elem %p\n", HashTable->hash[i]->QueueElem);
            printf("recency %d\n", HashTable->hash[i]->recency);
            printf("!!!!!!!!!!!!!!!!!!!!!!!!\n");
        }
    }

    return 3;
} 

int test4(void) { //tests hash_table_elem_insert
    int key1 = 45;
    int key2 = 76;
    int n = 5;
    struct Queue* Queue = 0;
    struct HashTableElem* hashelem = 0;
    Queue = (struct Queue*)calloc(1, sizeof(struct Queue));
    struct HashTable* HashTable = hash_table_create(n);

    hash_table_elem_insert(key1, HashTable, Queue);
    hash_table_elem_insert(key2, HashTable, Queue);

    printf("Hash table pointer %p\n", HashTable);
    printf("Hash pointer %p\n", HashTable->hash);
    printf("size of hash = %d\n", HashTable->HashSize);
    for(int i = 0; i < n; i++) {
        printf("[%p]\n", HashTable->hash[i]);
        if(HashTable->hash[i] != NULL) {
            printf("!!!!!!!!!!!!!!!!!!!!!!!!\n");
            printf("key %d\n", HashTable->hash[i]->key);
            printf("cache elem %p\n", HashTable->hash[i]->CacheElem);
            printf("next %p\n", HashTable->hash[i]->next);
            printf("prev %p\n", HashTable->hash[i]->prev);
            printf("queue elem %p\n", HashTable->hash[i]->QueueElem);
            printf("recency %d\n", HashTable->hash[i]->recency);
            printf("!!!!!!!!!!!!!!!!!!!!!!!!\n");
        }
    }

    return 4;
} 

int test5(void) { //tests hash_table_elem_insert
    int key1 = 45;
    int key2 = 77;
    int n = 2;
    struct Queue* Queue = 0;
    struct HashTableElem* hashelem = 0;
    Queue = (struct Queue*)calloc(1, sizeof(struct Queue));
    struct HashTable* HashTable = hash_table_create(n);

    hash_table_elem_insert(key1, HashTable, Queue);
    hash_table_elem_insert(key2, HashTable, Queue);

    printf("Hash table pointer %p\n", HashTable);
    printf("Hash pointer %p\n", HashTable->hash);
    printf("size of hash = %d\n", HashTable->HashSize);
    for(int i = 0; i < n; i++) {
        hashelem = HashTable->hash[i];
        printf("[%p]\n", HashTable->hash[i]);
        if(HashTable->hash[i] != NULL) {
            printf("!!!!!!!!!!!!!!!!!!!!!!!!\n");
            printf("key %d\n", HashTable->hash[i]->key);
            printf("cache elem %p\n", HashTable->hash[i]->CacheElem);
            printf("next %p\n", HashTable->hash[i]->next);
            while(hashelem->next != NULL) {
                printf("<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
                printf("key %d\n", hashelem->next->key);
                printf("cache elem %p\n", hashelem->next->CacheElem);
                printf("next %p\n", hashelem->next->next);
                printf("prev %p\n", hashelem->next->prev);
                printf("queue elem %p\n", hashelem->next->QueueElem);
                printf("recency %d\n", hashelem->next->recency);
                printf("<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
                hashelem = hashelem->next;
            }
            printf("prev %p\n", HashTable->hash[i]->prev);
            printf("queue elem %p\n", HashTable->hash[i]->QueueElem);
            printf("recency %d\n", HashTable->hash[i]->recency);
            printf("!!!!!!!!!!!!!!!!!!!!!!!!\n");
        }
    }

    return 5;
} 

int test6(void) { //tests hash_table_elem_insert
    int key1 = 45;
    int key2 = 77;
    int key3 = 71;
    int key4 = 84;
    int n = 3;
    struct Queue* Queue = 0;
    struct HashTableElem* hashelem = 0;
    Queue = (struct Queue*)calloc(1, sizeof(struct Queue));
    struct HashTable* HashTable = hash_table_create(n);

    hash_table_elem_insert(key1, HashTable, Queue);
    hash_table_elem_insert(key2, HashTable, Queue);
    hash_table_elem_insert(key3, HashTable, Queue);
    hash_table_elem_insert(key4, HashTable, Queue);

    printf("Hash table pointer %p\n", HashTable);
    printf("Hash pointer %p\n", HashTable->hash);
    printf("size of hash = %d\n", HashTable->HashSize);
    for(int i = 0; i < n; i++) {
        hashelem = HashTable->hash[i];
        printf("[%p]\n", HashTable->hash[i]);
        if(HashTable->hash[i] != NULL) {
            printf("!!!!!!!!!!!!!!!!!!!!!!!!\n");
            printf("key %d\n", HashTable->hash[i]->key);
            printf("cache elem %p\n", HashTable->hash[i]->CacheElem);
            printf("next %p\n", HashTable->hash[i]->next);
            while(hashelem->next != NULL) {
                printf("<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
                printf("key %d\n", hashelem->next->key);
                printf("cache elem %p\n", hashelem->next->CacheElem);
                printf("next %p\n", hashelem->next->next);
                printf("prev %p\n", hashelem->next->prev);
                printf("queue elem %p\n", hashelem->next->QueueElem);
                printf("recency %d\n", hashelem->next->recency);
                printf("<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
                hashelem = hashelem->next;
            }
            printf("prev %p\n", HashTable->hash[i]->prev);
            printf("queue elem %p\n", HashTable->hash[i]->QueueElem);
            printf("recency %d\n", HashTable->hash[i]->recency);
            printf("!!!!!!!!!!!!!!!!!!!!!!!!\n");
        }
    }

    return 6;
} 

int test7(void) { //tests find
    int key1 = 45;
    int key2 = 77;
    int key3 = 71;
    int key4 = 84;
    int n = 4;
    struct HashTableElem* res1 = 0;
    struct HashTableElem* res2 = 0;
    struct Queue* Queue = 0;
    struct HashTableElem* hashelem = 0;
    Queue = (struct Queue*)calloc(1, sizeof(struct Queue));
    struct HashTable* HashTable = hash_table_create(n);

    hash_table_elem_insert(key1, HashTable, Queue);
    hash_table_elem_insert(key2, HashTable, Queue);
    hash_table_elem_insert(key3, HashTable, Queue);
    hash_table_elem_insert(key4, HashTable, Queue);

    printf("Hash table pointer %p\n", HashTable);
    printf("Hash pointer %p\n", HashTable->hash);
    printf("size of hash = %d\n", HashTable->HashSize);
    for(int i = 0; i < n; i++) {
        hashelem = HashTable->hash[i];
        printf("[%p]\n", HashTable->hash[i]);
        if(HashTable->hash[i] != NULL) {
            printf("!!!!!!!!!!!!!!!!!!!!!!!!\n");
            printf("key %d\n", HashTable->hash[i]->key);
            printf("cache elem %p\n", HashTable->hash[i]->CacheElem);
            printf("next %p\n", HashTable->hash[i]->next);
            while(hashelem->next != NULL) {
                printf("<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
                printf("key %d\n", hashelem->next->key);
                printf("cache elem %p\n", hashelem->next->CacheElem);
                printf("next %p\n", hashelem->next->next);
                printf("prev %p\n", hashelem->next->prev);
                printf("queue elem %p\n", hashelem->next->QueueElem);
                printf("recency %d\n", hashelem->next->recency);
                printf("<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
                hashelem = hashelem->next;
            }
            printf("prev %p\n", HashTable->hash[i]->prev);
            printf("queue elem %p\n", HashTable->hash[i]->QueueElem);
            printf("recency %d\n", HashTable->hash[i]->recency);
            printf("!!!!!!!!!!!!!!!!!!!!!!!!\n");
        }
    } 
    res1 = find(39, HashTable);
    res2 = find(45, HashTable);

    printf("<%p>\n<%p>\n", res1, res2);

    return 7;
} 

int main(void) {
    /* printf("test %d passed\n", test1());
    printf("--------------------------------------\n");
    printf("test %d passed\n", test2());
    printf("--------------------------------------\n");
    printf("test %d passed\n", test3());
    printf("--------------------------------------\n"); 
    printf("test %d passed\n", test4());
    printf("--------------------------------------\n");
    printf("test %d passed\n", test5());
    printf("--------------------------------------\n"); 
    printf("test %d passed\n", test6());
    printf("--------------------------------------\n"); */
    printf("test %d passed\n", test7());
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////