#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    int data;
    struct Node *node;
};

void foo(int **p)
{

    *p = (int *)malloc(sizeof(int));
    if (*p == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    **p = 10;
    return;
}

int main()
{

    int *p = NULL;

    // foo(&p);

    // printf("Address pointed by p: %p\n", p);
    // printf("Value at address pointed by p: %d\n", *p);

    char *line;
    line = "Hello";
    printf("The value of line %p\n", (void *)line);
    printf("The value of line + 1 %p\n", (void *)line + 1);
    printf("The size of pointer is %zu\n", sizeof(line));

    free(p);

    return 0;
}
