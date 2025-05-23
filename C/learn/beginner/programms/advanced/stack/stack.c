#include "stack.h"

int initializeStack(STACK *stack, int size)
{
    if (size > STACK_SIZE)
    {
        printf("The size cannot be greater than %d\n", STACK_SIZE);
        return 0;
    }
    stack->size = size;
    stack->top = -1;
    return 1;
}

void pushToStack(STACK *stack, int element)
{
    if (stack->top == (stack->size - 1))
    {
        printf("The stack is full!\n");
        return;
    }

    stack->top = stack->top + 1;
    stack->arr[stack->top] = element;
    printf("Element %d added to position %d \n", element, stack->top);
}

int popStack(STACK *stack)
{
    if (stack->top < 0)
    {
        printf("The stack is empty!\n");
        return -1;
    }
    int element = stack->arr[stack->top];
    stack->top = stack->top - 1;
    return element;
}

void displayStack(STACK *stack)
{
    if (stack->top < 0)
    {
        printf("The stack is empty!\n");
        return;
    }

    int tempTop = stack->top;
    printf("The Stack!\n");
    while (tempTop >= 0)
    {
        printf("%d \t", stack->arr[tempTop]);
        tempTop--;
    }
    printf("\n");
}
