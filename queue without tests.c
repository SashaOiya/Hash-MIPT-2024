#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

struct Node* head = NULL;
struct Node* tail = NULL;

void enqueue(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = tail;

    if (tail == NULL) {
        head = newNode;
    } else {
        tail->next = newNode;
    }

    tail = newNode;
}

void dequeue() {
    if (head == NULL) {
        return;
    }

    struct Node* temp = head;
    head = head->next;

    if (head == NULL) {
        tail = NULL;
    } else {
        head->prev = NULL;
    }

    free(temp);
}

void display() {
    struct Node* temp = front;

    if (temp == NULL) {
        return;
    }

    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
}


int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);

    dequeue();
    display();

}
