#include "queue.h"

void clearInputBuffer()
{
    while (getchar() != '\n')
    {
    }
    return;
}

int takeInput()
{
    int x;
    printf("Enter element: ");
    scanf("%d", &x);
    clearInputBuffer();
    return x;
}

void start()
{

    QUEUE queue;

    printf("Enter the size of queue. \n");
    int size = takeInput();
    if (initializeQueue(&queue, size) == 0)
    {
        return;
    }

    while (1)
    {
        int choice;
        printf("Enter your choice: \n 1) Display Queue - 1 \n 2) Add to queue - 2 \n 3) De quque - 3 \n 4) More - 4 \n 5) Exit - 5 \n : ");
        scanf("%d", &choice);
        clearInputBuffer();

        if (choice < 1 || choice > 4)
        {
            printf("Exting Program...");
            return;
        }

        switch (choice)
        {
        case 1:
            displayQueue(&queue);
            break;
        case 2:
            int element = takeInput();
            enQueue(&queue, element);
            break;
        case 3:
            printf("Element %d dequedue. \n", deQueue(&queue));
            break;
        case 4:
            printf("More options on the way. \n");

            break;
        default:
            printf("Invalid Option. \n");
        }
    }
}

int main()
{
    start();
    return 0;
}