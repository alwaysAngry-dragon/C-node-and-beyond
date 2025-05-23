#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void count(FILE *fptr)
{

    int lineCount = 0;
    int wordCount = 0;
    int charCount = 0;
    char ch;
    while ((ch = fgetc(fptr)) != EOF)
    {
        if (ch == '\n')
        {
            lineCount++;
        }
        if (ch == ' ' || ch == '\n')
        {
            wordCount++;
        }
        if (ch != ' ' && ch != '\n')
        {
            charCount++;
        }
    }

    printf("Lines :%d\n", lineCount);
    printf("Words :%d\n", wordCount);
    printf("Characters :%d\n", charCount);
}

int main()
{

    FILE *fptr = fopen("file.md", "r");

    if (fptr == NULL)
    {
        printf("Error opening file. \n");
        exit(1);
    }

    count(fptr);
    fclose(fptr);

    return 0;
}
