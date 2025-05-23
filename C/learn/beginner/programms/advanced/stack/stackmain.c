
#include "stack.h"

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

    STACK stack;

    printf("Enter the size of stack. \n");
    int size = takeInput();
    if (initializeStack(&stack, size) == 0)
    {
        return;
    }

    while (1)
    {
        int choice;
        printf("Enter your choice: \n 1) Display Stack - 1 \n 2) Push - 2 \n 3) Pop - 3 \n 4) More - 4 \n 5) Exit - 5 \n : ");
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
            displayStack(&stack);
            break;
        case 2:
            int element = takeInput();
            pushToStack(&stack, element);
            break;
        case 3:
            printf("Element %d popped. \n", popStack(&stack));
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