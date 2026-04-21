#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;
};

void insertFront(struct Node **head, int data)
{
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = *head;
    newNode->prev = NULL;
    
    if(*head != NULL)
    {
        (*head)->prev = newNode;
    }
    *head = newNode;
}

void insertEnd(struct Node **head, int data)
{
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    struct Node *last = *head;    
    newNode->data = data;
    newNode->next = NULL;

    if(*head == NULL)
    {
        newNode->prev = NULL;
        *head = newNode;
        return;
    }

    while(last->next != NULL)
    {
        last = last->next;
    }

    last->next = newNode;
    newNode->prev = last;
}

void deleteNode(struct Node **head, int key)
{
    struct Node *temp = *head;

    while(temp != NULL && temp->data != key)
    {
        temp = temp->next;
    }

    if(temp == NULL)
    {
        return;
    }

    if(*head == temp)
    {
        *head = temp->next;
    }

    if(temp->next != NULL)
    {
        temp->next->prev = temp->prev;
    }

    if(temp->prev != NULL)
    {
        temp->prev->next = temp->next;
    }
    free(temp);
}


void displayList(struct Node* node)
{
    while(node != NULL)
    {
        printf(" %d <->", node->data);
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

    printf("Created Doubly Linked List: ");
    displayList(myNode);

    deleteNode(&myNode, 10);
    printf("After deleting 10: ");
    displayList(myNode);

    freeList(&myNode);
    return 0;
}