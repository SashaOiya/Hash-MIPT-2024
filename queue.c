#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "queue.h"
#include "lirs_cache.h"
#include "hash.h"



struct Queue* create_queue() {        // Creates a queue and returns a pointer to it
    struct Queue* Queue  = (struct Queue*)calloc(1, sizeof(struct Queue));
    assert(Queue);
    if (Queue == NULL) {
        return NULL;
    }

    Queue->top = NULL;
    Queue->bottom = NULL;

    return Queue;
}

// Destructor
void destroy_queue(struct Queue* Queue) {
    if (Queue == NULL) {
        return;
    }

    struct QueueElem* current = Queue->top;
    while (current != NULL) {
        struct QueueElem* temp = current;
        current = current->next;
        free(temp);
    }

    free(Queue);
}

// Takes a key element. Adds it to the beginning of the queue. Updates pointers to neighboring elements
struct QueueElem* queue_node_create(int key, struct Queue* Queue) {

    struct QueueElem* newElement = (struct QueueElem*)calloc(1, sizeof(struct QueueElem));
    assert(newElement);

    newElement->key = key;

    if (Queue->top == NULL) {
        Queue->top = newElement;
        Queue->bottom = newElement;
        newElement->prev = NULL;
        newElement->next = NULL;
    } else {
        newElement->prev = NULL;
        newElement->next = Queue->top;
        Queue->top->prev = newElement;
        Queue->top = newElement;
    }

    return newElement;
}

// Adds a new element to the end of the queue
void enqueue(struct Queue* Queue, int key) {
    struct QueueElem* new_node = (struct QueueElem*)calloc(1, sizeof(struct QueueElem));
    assert(new_node);
    new_node->key = key;
    new_node->next = NULL;

    if (Queue->bottom == NULL) {
        Queue->top = new_node;
        Queue->bottom = new_node;
    } else {
        Queue->bottom->next = new_node;
        new_node->prev = Queue->bottom;
        Queue->bottom = new_node;
    }
}

// Removes an element from the beginning of the queue
void dequeue(struct Queue* Queue) {
    if (Queue->top == NULL) {
        return;
    }

    struct QueueElem* temp = Queue->top;
    Queue->top = temp->next;

    if (Queue->top == NULL) {
        Queue->bottom = NULL;
    } else {
        Queue->top->prev = NULL;
    }

    free(temp);
}

// Lifts the specified element in the queue so that this element becomes the new head element
void lift_queue_element(struct Queue* Queue, struct QueueElem* element) {
    if (element == Queue->top) {
        return;
    }

    if (element == Queue->bottom) {
        Queue->bottom = element->prev;
        element->prev->next = NULL;
    } else {
        element->prev->next = element->next;
        element->next->prev = element->prev;
    }

    element->prev = NULL;
    element->next = Queue->top;
    Queue->top->prev = element;
    Queue->top = element;
}

// Clears the queue from elements with a specific status and attribute
void queue_pruning(struct Queue* Queue, struct HashTable* HashTable) {
    struct QueueElem* current = Queue->bottom;

    while (current != NULL && current->state == LIR) {
        struct QueueElem* temp = current;
        current = current->prev;

        if (temp->recency == RESIDENT) {
            if (temp == Queue->top) {
                Queue->top = NULL;
                Queue->bottom = NULL;
            } else {
                temp->prev->next = NULL;
                Queue->bottom = temp->prev;
            }

            free(temp);
        } else {
            
            delete_hash_table_elem(find(Queue->bottom->key, HashTable), HashTable);
            if (temp == Queue->top) {
                Queue->top = NULL;
                Queue->bottom = NULL;
            } else {
                temp->prev->next = NULL;
                Queue->bottom = temp->prev;
            }

            free(temp);
        }
    }
}

    
