#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "hash.h"

struct QueueElem { // Structure of queue elements
    int key;
    struct QueueElem* next;
    struct QueueElem* prev;
    int recency; // resident or non_resident
    int status;  // hir or lir
};

struct Queue {  // Queue structure
    struct QueueElem* head;
    struct QueueElem* tail;
};

struct Queue* create_queue() {        // Creates a queue and returns a pointer to it
    struct Queue* Queue  = (struct Queue*)calloc(1, sizeof(struct Queue));
    assert(Queue);
    if (Queue == NULL) {
        return NULL;
    }

    Queue->head = NULL;
    Queue->tail = NULL;

    return Queue;
}

// Destructor
void destroy_queue(struct Queue* queue) {
    if (Queue == NULL) {
        return;
    }

    struct QueueElem* current = Queue->head;
    while (current != NULL) {
        struct QueueElem* temp = current;
        current = current->next;
        free(temp);
    }

    free(queue);
}

// Takes a key element. Adds it to the beginning of the queue. Updates pointers to neighboring elements
struct QueueElem* queue_nod_create(int key, struct Queue* Queue) {

    struct Queue* newElement = (struct QueueElem*)calloc(1, sizeof(struct QueueElem));
    assert(newElement)

    newElement->key = key;

    if (Queue->head == NULL) {
        Queue->head = newElement;
        Queue->tail = newElement;
        newElement->prev = NULL;
        newElement->next = NULL;
    } else {
        newElement->prev = NULL;
        newElement->next = Queue->head;
        Queue->head->prev = newElement;
        Queue->head = newElement;
    }

    return newElement;
}

// Adds a new element to the end of the queue
void enqueue(struct Queue* Queue, int key) {
    struct QueueElem* new_node = (struct QueueElem*)calloc(1, sizeof(struct QueueElem));
    assert(new_node);
    new_node->key = key;
    new_node->next = NULL;

    if (Queue->tail == NULL) {
        Queue->head = new_node;
        Queue->tail = new_node;
    } else {
        Queue->tail->next = new_node;
        new_node->prev = Queue->tail;
        Queue->tail = new_node;
    }
}

// Removes an element from the beginning of the queue
void dequeue(struct Queue* Queue) {
    if (Queue->head == NULL) {
        return;
    }

    struct QueueElem* temp = Queue->head;
    Queue->head = temp->next;

    if (Queue->head == NULL) {
        Queue->tail = NULL;
    } else {
        Queue->head->prev = NULL;
    }

    free(temp);
}

// Lifts the specified element in the queue so that this element becomes the new head element
void lift_queue_element(struct Queue* Queue, struct QueueElem* element) {
    if (element == Queue->head) {
        return;
    }

    if (element == Queue->tail) {
        Queue->tail = element->prev;
        element->prev->next = NULL;
    } else {
        element->prev->next = element->next;
        element->next->prev = element->prev;
    }

    element->prev = NULL;
    element->next = Queue->head;
    Queue->head->prev = element;
    Queue->head = element;
}

// Clears the queue from elements with a specific status and attribute
void queue_pruning(struct Queue* queue) {
    struct QueueElem* current = queue->tail;

    while (current != NULL && current->status == LIR) {
        struct QueueElem* temp = current;
        current = current->prev;

        if (temp->recency == RESIDENT) {
            if (temp == queue->head) {
                queue->head = NULL;
                queue->tail = NULL;
            } else {
                temp->prev->next = NULL;
                queue->tail = temp->prev;
            }

            free(temp);
        } else {
            delete_hash_table_elem(hashtable, temp->key);
            if (temp == queue->head) {
                queue->head = NULL;
                queue->tail = NULL;
            } else {
                temp->prev->next = NULL;
                queue->tail = temp->prev;
            }

            free(temp);
        }
    }
}

    
