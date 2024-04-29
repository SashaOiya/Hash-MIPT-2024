#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "list.h"
#include "data.h"
#include "hash_table.h"
#include "lru_cache.h"

#define nullptr NULL 

//                      MAIN
int main()
{
    struct Data *Data;
    struct LRUCache* LRUCache;
    int cachehits = 0;

    Data = create_data();

    input_data(Data);

    LRUCache = create_lrucache();
 
    set_lrucache(LRUCache, Data);

    for(unsigned i = 0; i < Data->nrequests; ++i)
    {   
        cachehits += lift_or_insert_lrucache_elem(LRUCache, Data->requests[i]);
    }

    destruct_lrucache(LRUCache);
    
    destruct_data(Data);

    output(cachehits);

    return 0;
}
