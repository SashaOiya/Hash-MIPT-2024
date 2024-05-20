#pragma once
#ifndef QUEUE_H
#define QUEUE_H
#include "hash.h"

struct QueueElem { // Structure of queue elements
    int key;
    struct QueueElem* next;
    struct QueueElem* prev;
    int recency; // resident or non_resident
    int state;  // hir or lir
};

struct Queue {  // Queue structure
    struct QueueElem* top;
    struct QueueElem* bottom;
};

enum {
    HIR,
    LIR,
};

struct Queue* create_queue();
void destroy_queue(struct Queue* queue);
struct QueueElem* queue_node_create(int key, struct Queue* Queue);
void enqueue(struct Queue* Queue, int key);
void dequeue(struct Queue* Queue);
void lift_queue_element(struct Queue* Queue, struct QueueElem* element);
void queue_pruning(struct Queue* queue, struct HashTable* HashTable);

#endif
