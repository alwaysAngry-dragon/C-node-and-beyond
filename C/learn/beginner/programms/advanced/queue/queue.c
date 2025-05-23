#include "queue.h"

// in initialize queue the size of the queue is set, the position of first and last is set

int initializeQueue(QUEUE *queue, int size)
{
    if (size > QUEUE_SIZE)
    {
        printf("The size cannot be greated that %d.\n", QUEUE_SIZE);
        return 0;
    }

    queue->size = size;
    queue->first = 0;
    queue->last = 0;
    return 1;
}

// in enqueue an element is added to the end of the queue
void enQueue(QUEUE *queue, int element)
{
    if (queue->last == queue->size)
    {
        printf("The queue is full.\n");
        return;
    }

    queue->arr[queue->last] = element;
    queue->last = queue->last + 1;
}

// in dequeu the element at the first position of queue is fetched
int deQueue(QUEUE *queue)
{
    if (queue->first == queue->last)
    {
        printf("The queue is empty!.\n");
        queue->first = queue->last = 0;
        return -1;
    }

    int element = queue->arr[queue->first];
    queue->first = queue->first + 1;
    return element;
}

// show the queue
void displayQueue(QUEUE *queue)
{

    if (queue->first == queue->last)
    {
        printf("The queue is empty!.\n");
        return;
    }

    int tempPosition = queue->first;
    printf("The quque is: ");
    while (tempPosition != queue->last)
    {
        printf("%d \t", queue->arr[tempPosition]);
        tempPosition++;
    }
    printf("\n");
}
