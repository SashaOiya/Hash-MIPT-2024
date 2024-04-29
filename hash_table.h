#pragma once

struct TableElem
{
    struct ListElem* ListElem;
    int key;
};

struct HashTable
{
    unsigned size;
    unsigned nelements;

    struct TableElem** htarr;
};

struct TableElem** create_htarr(unsigned size);
void destruct_htarr(struct TableElem** arr);

struct HashTable* create_table(struct TableElem** arr, unsigned size);
struct TableElem* create_telem(int key);

void destruct_telem(struct TableElem* telem);
void destruct_table(struct HashTable* htable, unsigned size);

enum HTSIZE
{
    HTSIZE = 10000000
};
