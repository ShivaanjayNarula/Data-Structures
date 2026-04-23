#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Queue
{
    int front, rear, size;
    unsigned capacity;
    int* array;
};

struct Queue* createQueue(unsigned capacity)
{
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));

    queue->capacity = capacity;
    queue->front = 0;
    queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    
    return queue;
}

int isFull(struct Queue* queue)
{
    return (queue->size == queue->capacity);
}

int isEmpty(struct Queue* queue)
{
    return (queue->size == 0);
}

void resizeQueue(struct Queue* queue)
{
    int oldCapacity = queue->capacity;
    int newCapacity = oldCapacity * 2;
    int* newArray = (int*)malloc(newCapacity * sizeof(int));

    for(int i = 0; i < queue->size; i++)
    {
        newArray[i] = queue->array[(queue->front + i) % oldCapacity];
    }

    free(queue->array);
    queue->array = newArray;
    queue->capacity = newCapacity;
    queue->front = 0;
    queue->rear = queue->size - 1;

    printf("Queue resized to capacity %u\n", newCapacity);
}

void enqueue(struct Queue* queue, int item)
{
    if(isFull(queue))
    {
        resizeQueue(queue);
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
    printf("%d added to the queue\n", item);
}

void dequeue(struct Queue* queue)
{
    if(isEmpty(queue))
    {
        return;
    }
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    printf("%d removed from the queue\n", item);
}

int main()
{
    struct Queue* queue = createQueue(2);

    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);
    enqueue(queue, 40);
    enqueue(queue, 50);

    dequeue(queue);

    printf("Front: %d\n", queue->array[queue->front]);
    printf("Rear: %d\n", queue->array[queue->rear]);

    return 0;
}