#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node
{
    int data;
    struct Node *next; // Pointer to the same struct type
} NODE;

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

void printList(struct Node **head)
{
    struct Node *temp = *head;

    if (temp == NULL)
    {
        printf("The list is empty. \n");
        return;
    }

    printf("The list is: \n");
    while (temp != NULL)
    {
        printf("%d", temp->data);
        if (temp->next != NULL)
        {
            printf("-> ");
        }
        temp = temp->next;
    }
    printf("\n");
}

void insertNodeStart(int data, struct Node **head)
{
    // insert node at the start

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    newNode->data = data;
    newNode->next = NULL;

    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        newNode->next = *head;
        *head = newNode;
    }

    printf("New node is inserted. \n");
}

void createList(struct Node **head)
{
    while (1)
    {
        int choice;
        printf("Enter your choice : \n 1) Insert New Node - 1 \n 2) Exit - 2 \n :");
        scanf("%d", &choice);
        if (choice < 1 || choice >= 2)
        {
            printf("");
            printList(head);

            return;
        }

        switch (choice)
        {
        case 1:
            int element = takeInput();
            insertNodeStart(element, head);
            break;

        default:
            break;
        }
    }
}

void mergeSortedLists(struct Node **head1, struct Node **head2)
{

    struct Node *temp1 = *head1;
    struct Node *temp2 = *head2;
    struct Node *mergedNode = NULL;

    while (temp1 != NULL && temp2 != NULL)
    {
        if (temp1->data <= temp2->data)
        {
            insertNodeStart(temp1->data, &mergedNode);
            temp1 = temp1->next;
        }
        else
        {
            insertNodeStart(temp2->data, &mergedNode);
            temp2 = temp2->next;
        }
    }

    while (temp1 != NULL)
    {
        insertNodeStart(temp1->data, &mergedNode);
        temp1 = temp1->next;
    }

    while (temp2 != NULL)
    {
        insertNodeStart(temp2->data, &mergedNode);
        temp2 = temp2->next;
    }

    printf("The lists are merged \n");
    printList(&mergedNode);
}

void start()
{
    struct Node *head1 = NULL;
    struct Node *head2 = NULL;

    createList(&head1);
    createList(&head2);
    printf("Merging List...\n");

    mergeSortedLists(&head1, &head2);

    free(head1); // only the head is freed, not the entire list
    free(head2);
}

int main()
{
    start();
    return 0;
}