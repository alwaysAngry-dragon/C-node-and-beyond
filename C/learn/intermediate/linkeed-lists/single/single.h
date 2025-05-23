#ifndef POINTERS_H
#define POINTERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node
{
    int data;
    struct Node *next; // Pointer to the same struct type
} NODE;

void initializeNode(int data);

void insertNodeEnd(NODE *node);

void insertNodeBeginning(int data);

void insertAtPosition(int data, int position);

void deleteFirstNode();

void deleteLastNode();

void deleteNodeAtPosition(int position);

int searchList(int value);

void removeDuplicates();

void reverseList();

void findMiddle();

bool checkLoop();

bool checkListEmpty();

int getListCount();

void printList();

#endif
