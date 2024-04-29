#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data.h"

struct Data* create_data()
{
    struct Data* data;
    
    data = (struct Data*) calloc(1, sizeof(struct Data));

    data->nrequests = 0;
    data->requests = nullptr;

    data->cachesize = 0;

    return data;
}

void input_data(struct Data* Data)
{
    scanf("%u%u", &Data->cachesize, &Data->nrequests);

    Data->requests = (int*) calloc(Data->nrequests, sizeof(int));

    for(unsigned i = 0; i < Data->nrequests; ++i)
    {
        scanf("%d", &Data->requests[i]);
    }

    return;
}

void destruct_data(struct Data* data)
{
    data->nrequests = 0;
    data->cachesize = 0;

    free(data->requests);
    data->requests = nullptr;

    free(data);
    data = nullptr;

    return;
}

void output(int cachehits)
{
    printf("%d\n", cachehits);

    return;
}