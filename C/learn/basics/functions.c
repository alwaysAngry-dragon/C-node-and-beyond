#include <stdio.h>
#include <stdlib.h>

void foo(char name[])
{
    name[0] = 'K';
}

int *bar(int size)
{

    int *arr = (int *)malloc(size * sizeof(int));

    for (int i = 0; i < size; i++)
    {
        arr[i] = i;
    }

    printf("location of arr: %p\n", arr);

    return arr;
}

int main()
{
    char myName[] = "World";

    int y = 5;
    int *p = (int *)&y;

    printf("location of x: %p\n", &y);
    printf("value of p: %p\n", p);

    foo(myName);

    int *x = bar(4);

    printf("location of x: %p\n", x);

    return 0; // Return 0 to indicate that the program executed successfully.
}