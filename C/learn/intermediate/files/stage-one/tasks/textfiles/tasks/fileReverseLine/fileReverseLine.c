#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct stat
{
    int lineCount;
    char *line[100];
};
// write to a file using fprintf

void writeToFile(FILE *fptr, struct stat fileStat)
{
    for (int i = fileStat.lineCount - 1; i >= 0; i--)
    {
        fprintf(fptr, "%s", fileStat.line[i]);
    }
}

// read the file line by line using fgets

struct stat readFileLineByLine(FILE *fptr)
{

    struct stat fileStat;

    fileStat.lineCount = 0;

    while (1)
    {
        fileStat.line[fileStat.lineCount] = (char *)malloc(100 * sizeof(char));
        if (fgets(fileStat.line[fileStat.lineCount], 100, fptr) == NULL)
        {
            break;
        }
        printf("Line %d: %s", fileStat.lineCount + 1, fileStat.line[fileStat.lineCount]);
        fileStat.lineCount++;
    }

    return fileStat;
}

FILE *openFile(char *filename, char *mode)
{
    FILE *fptr = fopen(filename, mode);

    if (fptr == NULL)
    {
        printf("Error opening file. \n");
        exit(1);
        return NULL;
    }

    return fptr;
}

int main()
{

    FILE *fptr = openFile("file.md", "r");
    if (fptr == NULL)
    {
        return 1;
    }

    struct stat fileStat = readFileLineByLine(fptr);
    fclose(fptr);

    fptr = openFile("file2.md", "w");
    if (fptr == NULL)
    {
        return 1;
    }
    writeToFile(fptr, fileStat);
    fclose(fptr);
    for (int i = 0; i < fileStat.lineCount; i++)
    {
        free(fileStat.line[i]);
    }

    return 0;
}
