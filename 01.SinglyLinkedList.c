#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

void insertFront(struct Node **head, int data)
{
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = *head;
    *head = newNode;
    return;
}

void insertEnd(struct Node **head, int data)
{
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    struct Node *last = *head;
    newNode->data = data;
    newNode->next = NULL;
    if(*head == NULL)
    {
        *head = newNode;
        return;
    }
    while(last->next != NULL)
    {
        last = last->next;
    }
    last->next = newNode;
}

void deleteNode(struct Node **head, int key)
{
    struct Node *temp = *head;
    struct Node *prev = NULL;
    if(temp != NULL && temp->data == key)
    {
        *head = temp->next;
        free(temp);
        return;
    }
    while(temp != NULL && temp->data != key)
    {
        prev = temp;
        temp = temp->next;
    }
    if(temp == NULL)
    {
        return;
    }
    prev->next = temp->next;
    free(temp);
}

void reverseList(struct Node **head) {
    struct Node *prev = NULL;
    struct Node *current = *head;
    struct Node *next = NULL;
    while(current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}

void displayList(struct Node* node)
{
    while(node != NULL)
    {
        printf(" %d ->", node->data);
        node = node->next;
    }
    printf(" NULL\n");
}

void freeList(struct Node** head)
{
    struct Node* current = *head;
    struct Node* next;
    while(current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

int main()
{
    struct Node *myNode = NULL;
    insertEnd(&myNode, 10);
    insertFront(&myNode, 20);
    insertEnd(&myNode, 30);

    printf("Created List: ");
    displayList(myNode);

    deleteNode(&myNode, 10);

    printf("After deleting 10: ");
    displayList(myNode);

    reverseList(&myNode);

    printf("After Reversing List: ");
    displayList(myNode);

    freeList(&myNode);
    return 0;
}
