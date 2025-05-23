#include "single.h"

NODE *HEAD = NULL;

void insertNodeEnd(NODE *node)
{
    NODE *temp = HEAD;

    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = node;
}

void initializeNode(int val)
{
    NODE *newNode = (NODE *)malloc(sizeof(NODE));
    if (newNode == NULL)
    {
        printf("Failed to allocate memory for new node.\n");
        return;
    }

    if (HEAD == NULL)
    {
        // the list is empty, so the new node becomes the head

        HEAD = newNode;
        newNode->data = val;
        newNode->next = NULL;
    }
    else
    {
        // this is not empty so the new node is addeded at the end
        newNode->data = val;
        newNode->next = NULL;
        insertNodeEnd(newNode);
    }

    printf("New node is inserted. \n");
}

void insertNodeBeginning(int val)
{
    NODE *newNode = (NODE *)malloc(sizeof(NODE));
    if (newNode == NULL)
    {
        printf("Failed to allocate memory for new node.\n");
        return;
    }

    if (HEAD == NULL)
    {
        // the list is empty, so the new node becomes the head

        HEAD = newNode;
        newNode->data = val;
        newNode->next = NULL;
    }
    else
    {
        // this is not empty so the new node is addeded to the beginning
        newNode->data = val;
        newNode->next = HEAD;
        HEAD = newNode;
    }
    printf("New node inserted at the start. \n");
}

void insertAtPosition(int data, int position)
{
    // 1) check if the list is empty, if yes then do not proceed

    if (checkListEmpty())
    {
        printf("The list is empty. \n");
        return;
    }

    // 2) check if the position is a valid position

    int count = getListCount();

    if (position < 1 || position > count + 1)
    {
        printf("Invalid position. \n");
        return;
    }

    // case 1: if the postion is 1, then insert at the beginning

    if (position == 1)
    {
        insertNodeBeginning(data);
        printList();
        return;
    }

    // case 2: if the position is equal to count+1, then insert at the end of the list

    if (position == count + 1)
    {
        initializeNode(data);
        printList();
        return;
    }

    // case 3: insert in the specified position

    NODE *newNode = (NODE *)malloc(sizeof(NODE));
    if (newNode == NULL)
    {
        printf("Failed to allocate memory for new node. \n");
        return;
    }
    newNode->data = data;
    newNode->next = NULL;

    int previousPosition = 1;

    NODE *previousNode = HEAD;

    while (previousPosition < position - 1)
    {
        previousPosition++;
        previousNode = previousNode->next;
    }
    newNode->next = previousNode->next;
    previousNode->next = newNode;
    printf("New node is inserted at position %d. \n", position);
    printList();
}

void deleteFirstNode()
{
    // 1) check if the list is empty, if yes then do not proceed

    if (checkListEmpty())
    {
        printf("The list is empty. \n");
        return;
    }

    NODE *temp = HEAD;
    HEAD = HEAD->next;

    free(temp);
    printf("First node deleted. \n");
    printList();
}

void deleteLastNode()
{
    // 1) check if the list is empty, if yes then do not proceed

    if (checkListEmpty())
    {
        printf("The list is empty. \n");
        return;
    }

    NODE *temp = HEAD;
    NODE *previousNode = NULL;

    // case 1 : only one node in the list
    if (getListCount() == 1)
    {
        HEAD = NULL;
        free(temp);
        printf("Last node deleted. \n");
        return;
    }

    // case 2: more than one node in the list
    while (temp->next != NULL)
    {
        previousNode = temp;
        temp = temp->next;
    }

    previousNode->next = NULL;
    free(temp);
    printf("Last node deleted. \n");
    printList();
}

void deleteNodeAtPosition(int position)
{

    // 1) check if the list is empty, if yes then do not proceed

    if (checkListEmpty())
    {
        printf("The list is empty. \n");
        return;
    }

    // 2) check if the position is a valid position

    int count = getListCount();

    if (position < 1 || position > count)
    {
        printf("Invalid position. \n");
        return;
    }

    // 2) if the postion is a valid position
    // case 1) if the position is 1, then delete the first node
    if (position == 1)
    {
        deleteFirstNode();
        return;
    }
    // case 2) if the position is equal to count, then delete the last node

    if (position == count)
    {
        deleteLastNode();
        return;
    }

    // case 3) delete the node at the specified position

    NODE *temp = HEAD;
    NODE *previousNode = NULL;
    int previousPosition = 0;

    while (previousPosition < position - 1)
    {
        previousPosition++;
        previousNode = temp;
        temp = temp->next;
    }

    // Ensure temp is valid
    if (temp == NULL)
    {
        printf("Error: Unexpected NULL encountered while traversing the list.\n");
        return;
    }

    previousNode->next = temp->next;
    free(temp);
    printf("Node as position %d deleted. \n", position);
    printList();
    return;
}

int searchList(int value)
{

    if (HEAD == NULL)
    {
        printf("The list is empty. \n");
        return -1;
    }

    int position = 0;
    NODE *temp = HEAD;

    while (temp != NULL)
    {
        position++;
        if (temp->data == value)
        {
            printf("Value %d found at position %d. \n", value, position);
            return position;
        }
        temp = temp->next;
    }

    printf("value %d not found in the list. \n", value);
    return -1;
}

void reverseList()
{
    if (HEAD == NULL)
    {
        printf("The list is empty. \n");
        return;
    }

    NODE *prev = NULL;
    NODE *current = HEAD;
    NODE *next = NULL;

    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    HEAD = prev;

    printf("The list is reversed. \n");
}

bool checkLoop()
{
    // use slow and fast pointer to check for a loop

    if (HEAD == NULL)
    {
        printf("The list is empty.\n");
        return false;
    }

    NODE *slow = HEAD;
    NODE *fast = HEAD;

    while (fast != NULL && fast->next != NULL)
    {
        fast = fast->next->next;

        if (slow == fast)
        {
            printf("Loop detected in the list. \n");
            return true;
        }

        slow = slow->next;
    }

    printf("No loop detected in the list. \n");
    return false;
}

void findMiddle()
{
    // use slow and fast pointer to find the middle of the list

    if (HEAD == NULL)
    {
        printf("The list is empty.\n");
        return;
    }

    NODE *slow = HEAD;
    NODE *fast = HEAD;

    while (fast != NULL && fast->next != NULL)
    {
        fast = fast->next->next;
        slow = slow->next;
    }

    printf("The middle node is %d. \n", slow->data);
    return;
}

void removeDuplicates()
{

    if (checkListEmpty())
    {
        printf("The list is empty. \n");
        return;
    }

    NODE *current = HEAD;
    NODE *temp = NULL;

    while (current->next != NULL)
    {
        if (current->data == current->next->data)
        {
            temp = current->next;
            current->next = current->next->next;
            free(temp);
        }
        else
        {
            current = current->next;
        }
    }

    printf("Duplicates removed. \n");
    printList();
    return;
}

bool checkListEmpty()
{
    if (HEAD == NULL)
    {
        return true;
    }

    return false;
}

int getListCount()
{
    NODE *temp = HEAD;
    int count = 0;

    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }
    return count;
}

void printList()
{
    NODE *temp = HEAD;

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
            printf(" -> ");
        }
        temp = temp->next;
    }
    printf("\n");
}