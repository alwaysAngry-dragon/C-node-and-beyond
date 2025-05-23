#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// write to a text file

void writeToFile(FILE *fptr)
{
    fprintf(fptr, "Design   Smith \n19trail");
    return;
}

// show the contents
void readFile(FILE *fptr)
{
    char first[100];
    char second[100];
    char fourth[100];
    int third;

    fscanf(fptr, "%s", first);  // reads until a white space,\t,\n is encoutered, skips leading spaces,\n,\t
    fscanf(fptr, "%s", second); // reads until a white space is encoutered, skips leading spaces,\n,\t
    fscanf(fptr, "%d", &third); // reads until a non integer character is encoutered, skips leading spaces,\n,\t
    fscanf(fptr, "%s", fourth); // reads until a white space,\t,\n is encoutered, skips leading spaces,\n,\t
    printf("The contents of the file are: %s %s: %d - %s\n", first, second, third, fourth);
    return;
}

// open a file in specified mode

FILE *openFile(FILE *fptr, char *fileName, char *mode)
{
    fptr = fopen(fileName, mode);

    if (fptr == NULL)
    {
        printf("Error opening the file %s.\n", fileName);
        return NULL;
    }

    return fptr;
}

int main()
{

    FILE *fptr;
    fptr = openFile(fptr, "file.md", "w");
    if (fptr == NULL)
    {
        return 1;
    }
    writeToFile(fptr);
    fclose(fptr);
    fptr = openFile(fptr, "file.md", "r");
    if (fptr == NULL)
    {
        return 1;
    }

    readFile(fptr);
    fclose(fptr);

    return 0;
}