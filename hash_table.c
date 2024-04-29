#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_table.h"

struct TableElem** create_htarr(unsigned size)
{
    struct TableElem** arr;
    arr = (struct TableElem**) calloc(size, sizeof(struct TableElem*));

    return arr;
}

void destruct_htarr(struct TableElem** arr)
{
    free(arr);
    arr = nullptr;

    return;
}

struct HashTable* create_table(struct TableElem** arr, unsigned size)
{   
    struct HashTable* htpointer;

    htpointer = (struct HashTable*) calloc(1, sizeof(struct HashTable));

    htpointer->htarr = arr;
    htpointer->size = size;
    htpointer->nelements = 0;

    return htpointer; 
}

struct TableElem* create_telem(int key)
{
    struct TableElem* tmp;

    tmp = (struct TableElem*) calloc(1, sizeof(struct TableElem));

    tmp->key = key;
    tmp->ListElem = nullptr;

    return tmp;
}

void destruct_telem(struct TableElem* telem)
{
    telem->key = 0;

    telem->ListElem = nullptr;

    free(telem);

    return;
}

void destruct_table(struct HashTable* htable, unsigned size)
{
    for(unsigned i = 0; i < size; ++i)
    {
        if(htable->htarr[i] != nullptr)
            destruct_telem(htable->htarr[i]);
    }
    
    htable->size = 0;
    htable->nelements = 0;

    destruct_htarr(htable->htarr);

    free(htable);
    htable = nullptr;

    return;
}
