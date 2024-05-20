#pragma once

struct LIRSCache 
{
    struct List* Cache_t;
    struct HashTable* HashTable;
    struct Queue* Queue;
};

struct LIRSCache* create_lirs_cache(struct Data* Data); //creates a "raw" LIRSCache struct

void set_lirs_cache(struct LIRSCache* LIRSCache, struct Data* Data); //prepares LIRSCache based on input data

int determine_hirs_size(int cachesize); //determines size of list of Hirs based on input data

void destruct_lirs_cache(struct LIRSCache* LIRSCache); // destructs LIRSCache struct

int process_request(struct LIRSCache* LIRSCache, int request); //processes the incoming request

void chahging_state_and_pruning(struct LIRSCache* LIRSCache, struct HashTAbleElem* tmph); /*auxiliary function that changes states of
                                                                    Lir and Hir blocks an then calls a function that pruns the queue*/

void delete_last_element_from_list(struct LIRSCashe* LIRSCache); /*auxiliary function that changes resency of the last element of the 
                                                                                                        Hirs list and then deletes it*/