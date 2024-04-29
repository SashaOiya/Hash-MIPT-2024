#pragma once

struct ListElem 
{
    struct ListElem* prev;
    struct ListElem* next;
    int value;
};

struct Cache 
{
    struct ListElem* head;
    struct ListElem* tail;
    unsigned count;
    unsigned capacity;
};

struct Cache* create_cache();
struct ListElem* create_celem(int value);
void destruct_celem(struct ListElem* celem);

struct ListElem* get_head(struct Cache* cache);
struct ListElem* get_next(struct ListElem* celem);

void destruct_cache(struct Cache* cache);
void insert_list(struct Cache* List, struct ListElem* celem);
void lift_listelem(struct Cache* List, struct ListElem* ListElem);
void print_list(struct Cache* List);
