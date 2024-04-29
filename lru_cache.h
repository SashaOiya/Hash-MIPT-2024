#pragma once

struct LRUCache
{
    struct HashTable* HashTable;
    struct Cache* Cache;
};

struct LRUCache* create_lrucache();
void destruct_lrucache(struct LRUCache* LRUCache);

void set_lrucache(struct LRUCache* LRUCache, struct Data* Data);

int hash_func(int value);
int get_destr_htid(struct ListElem* ListElem);

int lift_or_insert_lrucache_elem(struct LRUCache* LRUCache, int value);

void destruct_lastelem(struct LRUCache* LRUCache);


