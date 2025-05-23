#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>

#define QUEUE_SIZE 5

typedef struct
{

    int arr[QUEUE_SIZE];
    int first;
    int last;
    int size;

} QUEUE;

// in initialize queue the size of the queue is set, the position of first and last is set
int initializeQueue();

// in enqueue an element is added to the end of the queue
void enQueue(QUEUE *queue, int element);

// in dequeu the element at the first position of queue is fetched
int deQueue(QUEUE *queue);

// show the queue
void displayQueue(QUEUE *queue);

#endif