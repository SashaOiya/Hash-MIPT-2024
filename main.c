#include <stdio.h>
#include <stdlib.h>

struct QueueElem {
    int key;
    struct QueueElem* next;
    struct QueueElem* prev;
};

struct Queue {
    struct QueueElem* head;
    struct QueueElem* tail;
};

void enqueue(struct Queue* queue, int key) {
    struct QueueElem* newNode = (struct QueueElem*)malloc(sizeof(struct QueueElem));
    newNode->key = key;
    newNode->next = NULL;

    if (queue->tail == NULL) {
        queue->head = newNode;
        queue->tail = newNode;
    } else {
        queue->tail->next = newNode;
        newNode->prev = queue->tail;
        queue->tail = newNode;
    }
}

void dequeue(struct Queue* queue) {
    if (queue->head == NULL) {
        printf("Queue is empty\n");
        return;
    }

    struct QueueElem* temp = queue->head;
    queue->head = temp->next;

    if (queue->head == NULL) {
        queue->tail = NULL;
    } else {
        queue->head->prev = NULL;
    }

    free(temp);
}

void lift_element(struct Queue* queue, struct QueueElem* element) {
    if (element == queue->head) {
        return;
    }

    if (element == queue->tail) {
        queue->tail = element->prev;
        element->prev->next = NULL;

    } else {
        element->prev->next = element->next;
        element->next->prev = element->prev;
    }

    element->prev = NULL;
    element->next = queue->head;
    queue->head->prev = element;
    queue->head = element;
}
