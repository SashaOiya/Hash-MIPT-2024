#pragma once
#ifndef QUEUE_H
#define QUEUE_H
#include "hash.h"

struct Queue* create_queue();
void destroy_queue(struct Queue* queue);
struct QueueElem* queue_nod_create(int key, struct Queue* Queue);
void enqueue(struct Queue* Queue, int key);
void dequeue(struct Queue* Queue);
void lift_queue_element(struct Queue* Queue, struct QueueElem* element);
void queue_pruning(struct Queue* queue, struct HashTable* HashTable);

#endif
