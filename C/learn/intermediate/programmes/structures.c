#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Info
{
    int roll;
};

struct myStructure
{
    char name[10];
    int id;
    struct Info info;
};

struct myStructure *arrayStructs()
{
    struct myStructure *sk = malloc(5 * sizeof(struct myStructure));

    sk[0].id = 11;
    sk[1].id = 22;
    sk[2].id = 33;
    sk[3].id = 44;
    sk[4].id = 55;

    return sk;
}

// Inner structure
struct myStructure *generateStruct()
{

    struct myStructure *sk = malloc(sizeof(struct myStructure));
    printf("The size of the structure is %d \n", sizeof(struct myStructure));
    strcpy(sk->name, "DS");
    sk->info.roll = 22;
    printf("The address of sk is %p \n", sk);
    return sk;
}

int *testArrayReturn()
{
    int a[] = {1, 2, 3};

    return a;
}

int main(int argc, char const *argv[])
{
    /* code */

    struct myStructure *skArray = arrayStructs();

    printf("The structure array elements: \n");
    for (int i = 0; i < 5; i++)
    {
        printf("The id of %d struture %d \n", i + 1, skArray[i].id);
    }

    free(skArray);

    int *myArray = testArrayReturn();

    arrayStructs();
}
