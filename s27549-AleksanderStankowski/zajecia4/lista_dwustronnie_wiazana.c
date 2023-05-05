#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

Node* createNode(int data) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("malloc err");
        return 1;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertNode(Node** head, int data) {
    Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

void popNode(Node** head, Node* nodeToPop, Node** tail) {
    if
    *temp = head;
    head = tail;
    tail = temp;
    free(nodeToPop);
}

void appendNode(Node** head, int data) {
    Node* newNode = createNode(data);
    newNode->next = NULL;
    newNode->prev = head;
    *head = *newNode;
}

void printList(Node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}
