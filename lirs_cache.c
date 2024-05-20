#include "data.h"
#include "lirs_cache.h"
#include "list.h"
#include "queue.h"
#include "hash.h"

#define nullptr NULL


struct LIRSCache* create_lirs_cache(struct Data* Data) 
{
    struct LIRSCache* LIRSCache;
    struct HashTable* HashTAble;
    struct Cashe_t* CacheList;
    struct Queue* Queue;

    LIRSCache = (struct LIRSCache* ) calloc(1, sizeof(struct LIRSCache));

    Cache_Ctor(LIRSCache->CacheList, Data->cachesize);
    LIRSCache->Queue = create_queue();
    LIRSCache->HashTable = hash_table_create(Data->cachesize);

    return LIRSCache;
}

void set_lirs_cache(struct LIRSCache* LIRSCache, struct Data* Data)
{
    int hirs_size = 0;
    hirs_size = determine_hirs_size(Data->cachesize); //determines size of list of Hirs based on input data
    LIRSCache->HashTable->HashSize = Data->cachesize;
    LIRSCache->CacheList->cache_size = Data->cachesize;

    LIRSCache->CacheList->hirs->list_size = hirs_size;
    LIRSCache->CacheList->lirs->list_size = LIRSCache->CacheList->cache_size - hirs_size;
}

int determine_hirs_size(int cachesize)
{
    return ((cachesize/100) + 1); //the size of Hirs list should be about 1% of the size of the whole cache
}

void destruct_lirs_cache(struct LIRSCache* LIRSCache)
{
    Cache_Dtor(LIRSCache->CacheList);
    destroy_queue(LIRSCache->Queue);
    hash_dtor(LIRSCache->HashTable);

    LIRSCache->CacheList = nullptr;
    LIRSCache->Queue = nullptr;
    LIRSCache->HashTable = nullptr;

    free(LIRSCache);
}

int process_request(struct LIRSCache* LIRSCache, int request)
{
    assert(LIRSCache != nullptr);

    int cachehit = 0;

    struct HashTableElem* tmph;//accepts pointer to the block (hash table element) that will be processed
    
    assert(LIRSCache->HashTable != nullptr);
    tmph = find(request, LIRSCache->HashTable); 

    if(tmph != nullptr)
    {
                //UPON ACCECCING AN LIR BLOCK
       if(tmph->QueueElem != nullptr && tmph->QueueElem->state == LIR)
       {
           lift_queue_element(LIRSCache->Queue, tmph->QueueElem); //advanced function "enqueue()"
           if(tmph->QueueElem == LIRSCache->Queue->bottom)
               queue_pruning(LIRSCache->Queue, LIRSCache->HashTable); //"pruning queue until there is a LIR at the bottom"

           ++cachehit;
       } 
                   //UPON ACCECCING AN HIR RESIDENT BLOCK
       if(tmph->QueueElem->state == HIR && tmph->recency == RESIDENT)
       {   
           chahging_state_and_pruning(LIRSCache, tmph);
           ++cachehit;
       }
                   //UPON ACCECCING AN HIR NON-RESIDENT BLOCK
       if(tmph->QueueElem->state == HIR && tmph->recency == NON_RESIDENT)
       {
           if(tmph->QueueElem != nullptr)
           {
               delete_last_element_from_list(LIRSCache);

               List_Insert(LIRSCache->CacheList->hirs, tmph->ListElem->code);
               lift_queue_element(LIRSCache->Queue, tmph->QueueElem);
               chahging_state_and_pruning(LIRSCache, tmph);
           }
       }
    }

    else if(tmph == nullptr)
    {
        struct HashTableElem* newelem;
        newelem = hash_table_elem_create(request, LIRSCache->Queue, LIRSCache->HashTable);

        if((LIRSCache->CacheList->Lirs->list_size) < (LIRSCache->CacheList->cache_size) - (LIRSCache->CacheList->hirs->list_size))
        {    
            List_Insert(LIRSCache->CacheList->lirs, request);
            newelem->ListElem = LIRSCache->CacheList->lirs->head;
            newelem->recency = LIR;
            ++LIRSCache->CacheList->lirs->list_size;
        }
        else  
        {
            if((LIRSCache->CacheList->hirs->list_size) < (LIRSCache->CacheList->cache_size) - (LIRSCache->CacheList->lirs->list_size))
                ++LIRSCache->CacheList->hirs->list_size;
            else
                delete_last_element_from_list(LIRSCache);
                
            List_Insert(LIRSCache->CacheList->lirs, request);
            newelem->ListElem = LIRSCache->CacheList->hirs->tail;
            newelem->recency = HIR;     
        }
        
    }
    else
        cachehit = -1; //error

    assert(cachehit != -1);
    return cachehit;
}

void chahging_state_and_pruning(struct LIRSCache* LIRSCache, struct HashTableElem* tmph)
{
    if(tmph->QueueElem != nullptr)
        {
            lift_queue_element(LIRSCache->Queue, tmph->QueueElem); // place it on the top of queue 
            tmph->QueueElem->state = LIR; //states of block is stored in QueueElem and HashTableElem and they are equal
            
        
            snatch_list_elem(LIRSCache->CacheList->hirs, tmph->ListElem);//removes the specified element from the specified list
            List_Insert(LIRSCache->CacheList->lirs, tmph->ListElem->code);

            struct HashTableElem* tmpbottom; //pointer to the queue bottom element

            tmpbottom = find(LIRSCache->Queue->bottom->key, LIRSCache->HashTable);//takes pointer to queue bottom element
            tmpbottom->QueueElem->state = HIR; 
           

            snatch_list_elem(LIRSCache->CacheList->lirs, tmpbottom->ListElem);//removes the specified element from the specified list
            List_Insert(LIRSCache->CacheList->hirs, tmpbottom->ListElem->code); 

            /*thus I changed the state of the resident HIR to LIR, removed it from the HIR list,
            added it to the LIR list and also changed the state of the least called LIR to HIR
            and moved it from the HIR list to the LIR list*/

            queue_pruning(LIRSCache->Queue, LIRSCache->HashTable);           
        }
        else
        {
            enqueue(LIRSCache->Queue, tmph->key);
            lift_list_elem(LIRSCache->CacheList->hirs, tmph->ListElem);
        }
}

void delete_last_element_from_list(struct LIRSCache* LIRSCache)
{
    struct HashTableElem* tmplast; //pointer to the bottom HIR element in the HIR list 
    tmplast->ListElem = LIRSCache->CacheList->hirs->tail;
    tmplast->recency = NON_RESIDENT;
                   
    List_Delete(LIRSCache->CacheList->hirs);
    tmplast->ListElem = nullptr;
}