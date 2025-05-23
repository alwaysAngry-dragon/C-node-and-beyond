#include <stdio.h>
#include <stdlib.h>
struct myStruct
{
    int myNum;
    char myLetter;
};

int main()
{
    printf("Structures in C\n");

    struct myStruct s1;
    struct myStruct s2;

    struct myStruct *pStruct1 = &s1; // pStruct1 points to s1

    s1.myNum = 10;

    printf("Size of s1: %lu bytes\n", sizeof(s1));
    printf("Address of s1 = %p\n", &s1);
    printf("Address of s1 int element = %p\n", &s1.myNum);
    printf("Address of s1 int charelement = %p\n", &s1.myLetter);
    printf("Address of s2 = %p\n", &s2);

    printf("Size of sturcture: %lu bytes\n", sizeof(struct myStruct));
    // address of myStruct in stack

    // dynamic structures

    // this pStruct is a pointer in stack, the acutal structure is allocated on heap
    struct myStruct *pStruct = (struct myStruct *)malloc(sizeof(struct myStruct));

    return 0; // Return 0 to indicate that the program executed successfully.
}