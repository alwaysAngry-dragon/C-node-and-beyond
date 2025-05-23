#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sumTwo(int a, int b)
{
    return (a + b);
}

void functionCallbackPtr(int (*funcPtr)(int a, int b))
{
    printf("The sum is %d", funcPtr(2, 3));
}

void pointerStrConcat()
{
    char first[20] = "Hello";
    char second[] = "World";

    char *firstPtr;
    char *secondPtr;

    firstPtr = first;
    secondPtr = second;

    while (*firstPtr != '\0')
    {
        firstPtr++;
    }

    while (*secondPtr != '\0')
    {
        *firstPtr = *secondPtr;
        firstPtr++;
        secondPtr++;
    }

    *firstPtr = '\0';

    printf("The concatenated string is %s \n", first);

    printf("Length is %d", strlen(first));
}

void dynamicArray()
{
    const int SIZE = 4;

    int *dArray = (int *)malloc(SIZE * sizeof(int));

    for (int i = 0; i < SIZE; i++)
    {
        dArray[i] = i * 3;
        printf("%d \t", *(dArray + i));
    }

    free(dArray);
}

int *largestPointer()
{
    int arr[] = {11, 232, 35, 4};
    int i = 0;

    int *largestPtr = (int *)malloc(sizeof(int));

    int size = sizeof(arr) / sizeof(int);

    *largestPtr = 0;

    while (i < size)
    {
        if (*(arr + i) > *largestPtr)
        {
            *largestPtr = *(arr + i);
        }
        i++;
    }

    return largestPtr;
}

int main()
{
    // int *x = largestPointer();
    // free(x);
    // dynamicArray();
    // pointerStrConcat();

    functionCallbackPtr(sumTwo);

    return 0;
}