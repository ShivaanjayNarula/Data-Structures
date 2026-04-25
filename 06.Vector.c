#include <stdio.h>
#include <stdlib.h>

struct Vector 
{
    int size;
    unsigned capacity;
    int* array;
};

struct Vector* createVector(unsigned capacity) 
{
    struct Vector* vector = (struct Vector*)malloc(sizeof(struct Vector));
    
    vector->capacity = capacity;
    vector->size = 0;
    vector->array = (int*)malloc(vector->capacity * sizeof(int));
    
    return vector;
}

int isFull(struct Vector* vector) 
{
    return (vector->size == vector->capacity);
}

int isEmpty(struct Vector* vector) 
{
    return (vector->size == 0);
}

void resizeVector(struct Vector* vector) 
{
    unsigned oldCapacity = vector->capacity;
    unsigned newCapacity = oldCapacity + 1;
    
    int* newArray = (int*)realloc(vector->array, newCapacity * sizeof(int));
    
    if(newArray == NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }

    vector->array = newArray;
    vector->capacity = newCapacity;

    // printf("Vector resized to capacity %u\n", newCapacity);
}

void pushBack(struct Vector* vector, int item) 
{
    if(isFull(vector)) 
    {
        resizeVector(vector);
    }
    vector->array[vector->size] = item;
    vector->size = vector->size + 1;
    printf("%d added to the vector\n", item);
}

void popBack(struct Vector* vector) 
{
    if(isEmpty(vector)) 
    {
        return;
    }
    int item = vector->array[vector->size - 1];
    vector->size = vector->size - 1;
    vector->capacity = vector->capacity - 1;
    printf("%d removed from the vector\n", item);
}

int getAt(struct Vector* vector, int index) 
{
    if(index < 0 || index >= vector->size) 
    {
        printf("Index out of bounds\n");
        return -1;
    }
    return vector->array[index];
}

void destroyVector(struct Vector* vector) 
{
    free(vector->array);
    free(vector);
}

int main() 
{
    struct Vector* vector = createVector(0);

    pushBack(vector, 10);
    pushBack(vector, 20);
    pushBack(vector, 30);
    pushBack(vector, 40);
    pushBack(vector, 50);

    popBack(vector);

    printf("Element at index 0: %d\n", getAt(vector, 0));
    printf("Current Size: %d\n", vector->size);
    printf("Current Capacity: %u\n", vector->capacity);

    destroyVector(vector);

    return 0;
}