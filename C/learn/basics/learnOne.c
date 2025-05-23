#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main()
{

    // int 2-4, float 4, double 8, char 1, string is a character array %s, pointer adderss print %p
    // %lu for size

    int myArr[] = {1, 2, 3, 4};
    int myArr2[] = {1, 2, 3, 4};

    int dArr[2][3] = {{1, 2}, {3, 4}};

    char greetings[20] = "Hello World!";
    char greetings2[22] = "Hell World!";

    int x;
    printf("Enter a number: ");
    scanf("%d", &x);
    printf("You entered: %d\n", x);
    printf("Size of the element %lu bytes\n", sizeof(x));

    // printf("%d\n", strcmp(greetings, greetings2));

    // printf("%s\n", greetings);

    // printf("%d", greetings[15]);

    // printf("Size of int: %lu bytes\n", sizeof(greetings));
    // printf("Address of 4 element: %p \n", (void *)&myArr[4]);
    // printf("Address of x : %p \n", (void *)&x);
    // printf("Size of element in int array: %lu bytes\n", sizeof(myArr[0]));
    // printf("Element at index 33: %d\n", myArr[33]);

    // length of array

    // pointer

    int foo = 34;
    int *p = &foo;

    printf("Address of foo: %p\n", &foo);
    printf("Value of p: %p\n", p);
    printf("Value at p: %d\n", *p);

    *p = 33;

    printf("Value of foo: %d\n", foo);

    return 0; // Return 0 to indicate that the program executed successfully.
}