#include "single.h"

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

    while (1)
    {
        int choice;
        printf("Enter your choice: \n 1) Display Linked List - 1 \n 2) Insert New Node  - 2 \n 3) Insert New Node in Beginning - 3 \n 4) Insert at Position - 4 \n 5) Delete First Node - 5 \n 6) Delete Last Node - 6 \n 7) Delete at Position - 7 \n 8) Search Element - 8 \n 9) Reverse List - 9 \n 10) Find Middle - 10 \n 11) Check Loop - 11 \n 12) Remove Duplicates - 12 \n 13) Exit - 13\n :  ");
        scanf("%d", &choice);
        clearInputBuffer();

        if (choice < 1 || choice > 12)
        {
            printf("Exting Program...");
            return;
        }

        switch (choice)
        {
        case 1:
            printList();
            break;

        case 2:
            int element = takeInput();
            initializeNode(element);
            break;

        case 3:
            int element2 = takeInput();
            insertNodeBeginning(element2);
            break;

        case 4:
            printf("Enter new node data: \n");
            int element3 = takeInput();
            printf("Enter location to push new node. \n");
            int positionNew = takeInput();
            insertAtPosition(element3, positionNew);
            break;

        case 5:
            deleteFirstNode();
            break;

        case 6:
            deleteLastNode();
            break;

        case 7:
            printf("Enter location to delete node. \n");
            int positionDelete = takeInput();
            deleteNodeAtPosition(positionDelete);
            break;

        case 8:
            printf("Enter the value to search. \n");
            int valueToSearch = takeInput();
            int position = searchList(valueToSearch);
            break;

        case 9:
            reverseList();
            break;
        case 10:
            findMiddle();
            break;

        case 11:
            checkLoop();
            break;

        case 12:
            removeDuplicates();
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
