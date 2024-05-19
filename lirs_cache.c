#include "lirs_cache.h"
#include "cache_list.h"
#include "queue.h"
#include "hash.h"

struct LIRSCache* create_lirs_cache(struct Data* Data) 
{
    struct LIRSCache* LIRSCache;
    struct HashTable* HashTAble;
    struct List* CacheList;
    struct Queue* Queue;

    LIRSCache = (struct LIRSCache* ) calloc(1, sizeof(struct LIRSCache));

    LIRSCache->CacheList = create_cache_list();
    LIRSCache->Queue = create_queue();
    LIRSCache->HashTable = create_hash_table();

    return LIRSCache;
}

void destruct_lirs_cache(struct LIRSCache* LIRSCache)
{
    destruct_cache_list(LIRSCache->CacheList);
    destruct_queue(LIRSCache->Queue);
    destruct_hash_table(LIRSCache->HashTable);

    LIRSCache->CacheList = nullptr;
    LIRSCache->Queue = nullptr;
    LIRSCache->HashTable = nullptr;

    free(LIRSCache);
}

int process_request(struct LIRSCache* LIRSCache, int request)
{
    assert(LIRSCache != nullptr);

    int cachehit = 0;

    struct HashTAbleElem* tmph;//accepts pointer to the block (hash table element) that will be processed
    
    assert(LIRSCache->HashTable != nullptr);
    tmph = find(request, LIRSCache->HashTable); 

    if(tmph != nullptr)
    {
                //UPON ACCECCING AN LIR BLOCK
       if(tmph->QueueElem != nullptr && tmph->QueueElem->state == LIR)
       {
           lift_queue_element(LIRSCache->Queue, tmph); //advanced function "enqueue()"
           if(tmph->QueueElem == LIRSCache->Queue->bottom)
               queue_pruning(); //"pruning queue until there is a LIR at the bottom"

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

               insert_list_element(LIRSCache->CacheList->Hirs, tmph->ListElem);
               lift_queue_element(LIRSCache->Queue, tmph);
               chahging_state_and_pruning(struct LIRSCache* LIRSCache, struct HashTAbleElem* tmph);
           }
       }
    }

    else if(tmph == nullptr)
    {
        struct HashTableElem* newelem;
        newelem = create_hash_table_elem(request, LIRSCache->Queue, LIRSCache->HashTable);

        if((LIRSCache->CacheList->Lirs->list_size) < (LIRSCache->CacheList->cache_size) - (LIRSCache->CacheList->Hirs->list_size))
        {    
            List_Insert(LIRSCache->CacheList->Lirs, request);
            newelem->ListElem = LIRSCache->CacheList->Lirs->head;
            newelem->recency = LIR;
            ++LIRSCache->CacheList->Lirs->list_size;
        }
        else  
        {
            if((LIRSCache->CacheList->Hirs->list_size) < (LIRSCache->CacheList->cache_size) - (LIRSCache->CacheList->Lirs->list_size)
                ++LIRSCache->CacheList->Hirs->list_size;
            else
                delete_last_element_from_list(LIRSCache);
                
            List_Insert(LIRSCache->CacheList->Lirs, request);
            newelem->ListElem = LIRSCache->CacheList->Hirs->head;
            newelem->recency = HIR;     
        }
        
    }
    else
        cachehit = -1; //error

    assert(cachehit != -1);
    return cachehit;
}

void chahging_state_and_pruning(struct LIRSCache* LIRSCache, struct HashTAbleElem* tmph)
{
    if(tmph->QueueElem != nullptr)
        {
            lift_queue_element(LIRSCache->Queue, tmph); // place it on the top of queue 
            tmph->QueueElem->state == LIR; //states of block is stored in QueueElem and HashTableElem and they are equal
            tmph->state == LIR;
        
            snatch_list_element(LIRSCache->CacheList->Hirs, tmph->ListElem);//removes the specified element from the specified list
            insert_list_element(LIRSCache->CacheList->Lirs, tmph->ListElem);

            struct HashTAbleElem* tmpbottom; //pointer to the queue bottom element

            tmpbottom = find(elt(LIRSCache->Queue->bottom->value, LIRSCache->HashTable->size), LIRSCache->HashTable);//takes pointer to queue bottom element
            tmpbottom->QueueElem->state == HIR; 
            tmpbottom->state == HIR;

            snatch_list_element(LIRSCache->CacheList->Lirs, tmpbottom->ListElem);//removes the specified element from the specified list
            insert_list_element(LIRSCache->CacheList->Hirs, tmpbottom->ListElem); 

            /*thus I changed the status of the resident HIR to LIR, removed it from the HIR list,
            added it to the LIR list and also changed the status of the least called LIR to HIR
            and moved it from the HIR list to the LIR list*/

            queue_pruning();           
        }
        else
        {
            insert_queue_element(LIRSCache->Queue, tmph);
            lift_list_elem(LIRSCache->CacheList->Hirs, tmph->ListElem);
        }
}

void delete_last_element_from_list(struct LIRSCashe* LIRSCache);
{
    struct HashTAbleElem* tmplast; //pointer to the tail HIR element in the HIR list 
    tmplast = LIRSCache->CacheList->Hirs->tail;
    tmplast->recency = NON_RESIDENT;
                   
    List_Delete(LIRSCache->CacheList->Hirs);
    tmplast->ListElem = nullptr;
}