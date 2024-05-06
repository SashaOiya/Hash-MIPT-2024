#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int number;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct Queue {
    Node *head;
    Node *tail;
} Queue;

int dequeue(Queue *queue) {
    int value;
    value = queue->head->number;

    if (queue->head == queue->tail) {
        free(queue->head);
        queue->head = NULL;
        queue->tail = NULL;
    } else {
        queue->head = queue->head->prev;
        free(queue->head->next);
        queue->head->next = NULL;
    }

    return value;
}

void Queue_Elem(Queue *queue, int value) {
    Node *n = malloc(sizeof(Node));
    if (n == NULL) {
        return;
    }

    n->number = value;
    n->next = NULL;
    n->prev = NULL;

    if ((queue->head == NULL) && (queue->tail == NULL)) {
        queue->head = n;
        queue->tail = n;

    } else {
        queue->tail->prev = n;
        n->next = queue->tail;
        queue->tail = n;
    }
}

int main(void) {
    Queue queue;
    queue.head = NULL;
    queue.tail = NULL;

    int number, x;

    number = 31;
    enqueue(&queue, number);

    number = 2123;
    enqueue(&queue, number);

    number = 322312312;
    enqueue(&queue, number);


    Node *tmp = queue.head;
    while (tmp != NULL)
    {
      printf("%d\n", tmp->number);
      tmp = tmp->prev;
    }


    x = dequeue(&queue);
    printf("%d\n", x);


    x = dequeue(&queue);
    printf("%d\n", x);


}
