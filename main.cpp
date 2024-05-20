#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "data.h"
#include "lirs_cache.h"
#include "list.h"
#include "queue.h"
#include "hash.h"

int main()
{
    struct Data* Data;
    struct LIRSCache* LIRSCashe;
    
    int cachehits = 0;

    Data = create_data();

    input_data(Data);

    LIRSCache = create_lirs_cache(Data);

    for(unsigned i = 0; i < Data->nrequests; ++i)
    {
        cachehits += process_request(LIRSCache, Data->requests[i]);
    }

    destruct_lirs_cache(LIRSCache);

    destruct_data(Data);

    output(cachehits);

    return 0;
}
