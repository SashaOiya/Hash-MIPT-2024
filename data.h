#pragma once

struct Data
{
    unsigned nrequests;
    unsigned cachesize;

    int* requests;
};

struct Data* create_data();
void input_data(struct Data* Data);
void destruct_data(struct Data* Data);

void output(int cachehits);