#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

long getFileSize(FILE *fptr)
{
    fseek(fptr, 0L, SEEK_END);   // go to end of file
    long fileSize = ftell(fptr); // get current file position (should be size)
    rewind(fptr);                // go back to beginning of file

    return fileSize; // this will be number of bytes
}

void clearInputBuffer()
{
    while (getchar() != '\n')
    {
        // clear the input buffer
    }
}

char *removePunctuations(char *input)
{
    int i = 0;
    int j = strlen(input);

    if (j <= 0)
    {
        return strdup(""); // return a new empty string
    }

    // Remove leading punctuation
    while (i < j && ispunct((unsigned char)input[i]))
    {
        i++;
    }

    if (i == j)
    {
        return strdup(""); // string is all punctuation
    }

    // Remove trailing punctuation
    while (j > i && ispunct((unsigned char)input[j - 1]))
    {
        j--;
    }

    // Allocate exact size needed
    int newLen = j - i;
    char *temp = malloc(newLen + 1); // +1 for null terminator
    if (!temp)
    {
        printf("Error! Memory allocation failed.\n");
        exit(1);
    }

    // Copy substring
    strncpy(temp, input + i, newLen); // dest,scr,no_of_characters
    temp[newLen] = '\0';              // Null-terminate

    return temp;
}

// open  file

FILE *openFile(const char *fileName, const char *mode)
{

    FILE *file = fopen(fileName, mode);

    if (file == NULL)
    {
        printf("Error accessing file. \n");
        exit(1);
    }

    return file;
}

// take an input string

char *takeInput()
{

    char *input = (char *)malloc(20);

    if (input == NULL)
    {
        printf("Error allocating memory.\n");
        exit(1);
    }

    printf("Enter the text to search: ");
    scanf("%s", input);
    clearInputBuffer();
    return input;
}

// search the file until EOF

int searchStringInFile(FILE *fptr, const char *input)
{
    // if found will return the offset position in the file
    // use fscanf to read a string at a time

    char data[100];
    int offSetPosition = 0;
    int currentPointerPosition = -1;
    fseek(fptr, 0, SEEK_SET); // reset the file pointer to the starting

    while (fscanf(fptr, "%s", data) == 1)
    {

        char *copy;
        // sanitise the data
        copy = removePunctuations(data);

        if (strcasecmp(copy, input) == 0)
        {
            printf("String found at position: %d\n\n", offSetPosition);
            free(copy);
            return offSetPosition;
        }
        currentPointerPosition = ftell(fptr);
        offSetPosition = currentPointerPosition + 1;
        free(copy);
    }

    if (feof(fptr))
    {
        printf("End of file reached.\n");
    }

    if (ferror(fptr))
    {
        printf("Error reading file.\n");
    }

    printf("String not found.\n\n");
    return -1;
}

void start()
{

    FILE *fptr = NULL;
    fptr = openFile("file.md", "r");

    printf("The file size if %zu \n", getFileSize(fptr));

    if (fptr == NULL)
    {
        printf("Error opening file.");
        return;
    }

    while (1)
    {
        printf("Enter your choice:\n1. Search String:\n2. Exit:\n");
        int choice;

        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice)
        {
        case 1:
            /* code */
            printf("Enter string to search: ");
            char *input;
            input = takeInput();

            int postition = -1;
            postition = searchStringInFile(fptr, input);

            free(input);
            break;

        case 2:
            printf("Exiting...");
            fclose(fptr);
            return;

        default:
            printf("Invalid option. \n");
            break;
        }
    }
}

int main()
{
    start();
    return 0;
}
