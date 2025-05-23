#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 10

typedef struct
{
    int arr[STACK_SIZE];
    int top;
    int size;
} STACK;

int initializeStack(STACK *stack, int size);
void pushToStack(STACK *stack, int element);

int popStack(STACK *stack);

void displayStack(STACK *stack);

#endif