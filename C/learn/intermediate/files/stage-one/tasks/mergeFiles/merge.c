#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void readFileLines(char *fileName)
{
    FILE *fptr;
    fptr = fopen(fileName, "r");
    if (fptr == NULL)
    {
        printf("Error opening the file %s. \n", fileName);
        return;
    }
    int ch;
    int lines = 0;
    int i = 0;
    while ((ch = fgetc(fptr)) != EOF)
    {

        if (ch == '\n')
        {
            lines++;
        }
        i++;
    }

    fclose(fptr);
    printf("The total bytes %d. \n", i);
    printf("The total lines %d. \n", lines);
}

// read the contents of two files into two arrays

char *readFile(FILE *fptr)
{
    char *buffer = (char *)malloc(sizeof(char) * 1);

    if (buffer == NULL)
    {
        printf("Error allocation memory. \n");
        free(buffer);
        return NULL;
    }

    int ch;

    int size = 0;

    while ((ch = fgetc(fptr)) != EOF)
    {
        size++;
        char *temp = realloc(buffer, sizeof(char) * (size + 1));
        if (temp == NULL)
        {
            printf("Error allocation memory.\n");
            free(buffer);
            return NULL;
        }

        buffer = temp;

        buffer[size - 1] = ch;
    }

    buffer[size] = '\0';
    return buffer;
}

void mergeFiles(FILE *fptr1, FILE *fptr2, char *mergedFileName)
{
    FILE *fptr3;
    fptr3 = fopen(mergedFileName, "w");
    if (fptr3 == NULL)
    {
        printf("Error opening the merged file.\n");
        return;
    }
    printf("merging the files...\n");

    char *buffer1 = readFile(fptr1);
    char *buffer2 = readFile(fptr2);

    if (buffer1 == NULL || buffer2 == NULL)
    {
        printf("Error reading the files.\n");
        fclose(fptr3);
        return;
    }

    // write the contents of the two arrays into a new file
    fwrite(buffer1, sizeof(char), strlen(buffer1), fptr3);
    fwrite(buffer2, sizeof(char), strlen(buffer2), fptr3);

    printf("The contents of the files are merged successfully. \n");
    fclose(fptr3);
    free(buffer1);
    free(buffer2);
    readFileLines(mergedFileName);
}

FILE *openFile(char *fileName, char *mode)
{
    FILE *fptr = fopen(fileName, mode);
    if (fptr == NULL)
    {
        printf("Error opening the file %s.\n", fileName);
        return NULL;
    }

    return fptr;
}

// write the contents of the two arrays into a new file

int main()
{
    FILE *fptr1, *fptr2;

    fptr1 = openFile("file1.md", "r");
    fptr2 = openFile("file2.md", "r");

    if (fptr1 == NULL || fptr2 == NULL)
    {

        return 1;
    }

    char *mergedFileName = "merged.md";
    mergeFiles(fptr1, fptr2, mergedFileName);

    fclose(fptr1);
    fclose(fptr2);

    return 0;
}