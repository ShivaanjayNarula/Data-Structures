#include <stdio.h>
#include <stdlib.h>

struct Stack
{
    int top;
    unsigned capacity;
    int* array;
};

struct Stack* createStack(unsigned capacity)
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

void resizeStack(struct Stack* stack)
{
    unsigned oldCapacity = stack->capacity;
    stack->capacity *= 2;
    
    int* temp = (int*)realloc(stack->array, stack->capacity * sizeof(int));
    
    if(temp == NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }
    
    stack->array = temp;
    printf("Queue resized to capacity %u\n", stack->capacity);
}

int isFull(struct Stack* stack)
{
    return stack->top == stack->capacity - 1;
}

int isEmpty(struct Stack* stack)
{
    return stack->top == -1;
}

void push(struct Stack* stack, int item)
{
    if(isFull(stack))
    {
        resizeStack(stack);
    }
    stack->array[++stack->top] = item;
    printf("%d pushed to stack\n", item);
}

int pop(struct Stack* stack)
{
    if(isEmpty(stack))
    {
        printf("Stack Underflow\n");
        return -1;
    }
    return stack->array[stack->top--];
}

void peek(struct Stack* stack)
{
    if(isEmpty(stack))
    {
        return;
    }
    printf("Top element is %d\n", stack->array[stack->top]);
}

int main() {
    struct Stack* stack = createStack(2);

    push(stack, 10);
    push(stack, 20);
    push(stack, 30);
    push(stack, 40);
    push(stack, 50);

    peek(stack);

    printf("%d popped from stack\n", pop(stack));
    printf("%d popped from stack\n", pop(stack));

    peek(stack);

    free(stack->array);
    free(stack);

    return 0;
}
