#ifndef HASHTEST
#define HASHTEST

#include "hash.h"

struct Queue {
    struct QueueElem* top;
};

struct QueueElem {
    struct QueueElem *next;
    int key;
};

struct QueueElem* queue_node_create(int key, struct Queue* Queue);

int test1(void);

int test2(void);

int test3(void);

int test4(void);

int test5(void);

int test6(void);

int test7(void);

int test8(void);

int test9(void);

#endif