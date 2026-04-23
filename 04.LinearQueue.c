#include <stdio.h>
#include <stdlib.h>

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
    queue->rear = -1; 
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

void resizeQueue(struct Queue* queue)
{
    unsigned oldCapacity = queue->capacity;
    queue->capacity *= 2;

    int* temp = (int*)realloc(queue->array, queue->capacity * sizeof(int));
    if(temp == NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }
    queue->array = temp;
    printf("Queue resized to capacity %u\n", queue->capacity);
}

int isFull(struct Queue* queue)
{
    return (queue->rear == (int)queue->capacity - 1);
}

int isEmpty(struct Queue* queue)
{
    return (queue->size == 0);
}

void enqueue(struct Queue* queue, int item)
{
    if (isFull(queue))
    {
        resizeQueue(queue);
    }
    queue->rear++; 
    queue->array[queue->rear] = item;
    queue->size++;
    printf("%d enqueued to queue\n", item);
}

void dequeue(struct Queue* queue)
{
    if (isEmpty(queue))
    {
        printf("Queue is empty\n");
        return;
    }
    int item = queue->array[queue->front];
    queue->front++;
    queue->size--;
    printf("%d dequeued from queue\n", item);
}

int main()
{
    struct Queue* queue = createQueue(2);

    enqueue(queue, 10);
    enqueue(queue, 20);
    
    enqueue(queue, 30); 
    enqueue(queue, 40);

    dequeue(queue);
    
    printf("Front item index is %d (Value: %d)\n", queue->front, queue->array[queue->front]);
    printf("Rear item index is %d (Value: %d)\n", queue->rear, queue->array[queue->rear]);
    printf("Current size: %d, Capacity: %u\n", queue->size, queue->capacity);

    free(queue->array);
    free(queue);
    return 0;
}
