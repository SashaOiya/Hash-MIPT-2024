#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "list.h"
#include "data.h"
#include "hash_table.h"
#include "lru_cache.h"

struct LRUCache* create_lrucache()
{
    struct TableElem** htarr;
    struct HashTable* HashTable;
    struct Cache* Cache;
    struct LRUCache* lrucpointer;

    lrucpointer = (struct LRUCache*) calloc(1, sizeof(struct LRUCache));

    htarr = create_htarr(HTSIZE);

    HashTable = create_table(htarr, HTSIZE);
    
    Cache = create_cache();

    lrucpointer->Cache = Cache;
    lrucpointer->HashTable = HashTable;

    return lrucpointer;  
}

void destruct_lrucache(struct LRUCache* LRUCache)
{
    destruct_cache(LRUCache->Cache);
    LRUCache->Cache = nullptr;
    
    destruct_table(LRUCache->HashTable, HTSIZE);
    LRUCache->HashTable = nullptr;

    free(LRUCache);

    LRUCache = nullptr;

    return;
}

void set_lrucache(struct LRUCache* LRUCache, struct Data* Data)
{
    LRUCache->Cache->capacity = Data->cachesize;

    LRUCache->Cache->count = 0;

    //create_list(LRUCache->Cache);

    return;
}

int lift_or_insert_lrucache_elem(struct LRUCache* LRUCache, int value)
{
    int counter = 0;
    int htid;

    htid = hash_func(value);

    if(LRUCache->HashTable->htarr[htid] == nullptr) 
    {           
        LRUCache->HashTable->htarr[htid] = create_telem(value);

        LRUCache->HashTable->htarr[htid]->ListElem =  create_celem(value);

        insert_list(LRUCache->Cache, LRUCache->HashTable->htarr[htid]->ListElem);

        if(LRUCache->HashTable->nelements < LRUCache->Cache->capacity)
        {
            ++LRUCache->HashTable->nelements;
        }
        else
        {
            destruct_lastelem(LRUCache);
        }
    }
    else
    {   
        ++counter;

        lift_listelem(LRUCache->Cache, LRUCache->HashTable->htarr[htid]->ListElem);
    }

//    print_list(LRUCache->Cache);
    
    return counter;
}

int hash_func(int value)
{
    return value;
}

int get_destr_htid(struct ListElem* ListElem)
{
    return ListElem->value;
}



void destruct_lastelem(struct LRUCache* LRUCache)
{
    int destr_htid;

    destr_htid = get_destr_htid(LRUCache->Cache->tail);

    destruct_telem(LRUCache->HashTable->htarr[destr_htid]);
    
    LRUCache->HashTable->htarr[destr_htid] = NULL;
    assert(LRUCache->HashTable->htarr[destr_htid] == NULL);

    LRUCache->Cache->tail = LRUCache->Cache->tail->prev;

    destruct_celem(LRUCache->Cache->tail->next);

    LRUCache->Cache->tail->next = nullptr; 
}