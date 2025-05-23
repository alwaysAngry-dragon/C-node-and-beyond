#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// function to read the contents of a file into a string
// if the file is too big, then too big memory usage

char *replaceWord(const char *data, const char *oldWord, const char *newWord)
{
    char *haystack = (char *)data;
    char *occurrence;
    int oldLen = strlen(oldWord);
    int newLen = strlen(newWord);
    int count = 0;

    // Step 1: Count number of occurrences
    while ((occurrence = strstr(haystack, oldWord)) != NULL)
    {
        count++;
        haystack = occurrence + oldLen;
    }

    printf("The word '%s' occurs %d time(s) in the file.\n", oldWord, count);

    if (count == 0)
        return NULL;

    // Step 2: Allocate memory for result
    size_t resultSize = strlen(data) + count * (newLen - oldLen) + 1;
    char *result = (char *)malloc(resultSize);
    if (!result)
    {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    char *dst = result; // Pointer to build result
    haystack = (char *)data;

    // Step 3: Build output string
    while ((occurrence = strstr(haystack, oldWord)) != NULL)
    {
        // Copy part before oldWord
        memcpy(dst, haystack, occurrence - haystack);
        dst += occurrence - haystack;

        // Copy newWord
        memcpy(dst, newWord, newLen);
        dst += newLen;

        // Move past oldWord
        haystack = occurrence + oldLen;
    }

    // Copy remaining part including the '\0' terminator
    strcpy(dst, haystack);

    printf("The new string is: \n%s\n", result);

    return result;
}

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

// function to open a file in specified mode

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

void writeToFile(FILE *fptr, char *data)
{
    if (fptr == NULL)
    {
        printf("Error opening the file. \n");
        return;
    }
    if (data == NULL)
    {
        printf("Error writing to the file. \n");
        return;
    }

    printf("Writing to the file...\n");

    printf("The length of the string is %d.\n", strlen(data));

    int bytesWritten = fwrite(data, sizeof(char), strlen(data), fptr);

    if (bytesWritten < 0)
    {
        printf("Error in writing to the file.\n");
        return;
    }

    printf("The amount of data written %d.\n", bytesWritten);

    if (ferror(fptr))
    {
        printf("Error in writing to file. \n");
    }

    fclose(fptr);
    printf("Old word is replaced");
}

int main()
{
    FILE *fptr1;

    fptr1 = openFile("file1.md", "r");

    if (fptr1 == NULL)
    {
        return 1;
    }

    char *data = readFile(fptr1);

    if (data == NULL)
    {
        fclose(fptr1);
        return 1;
    }

    printf("The contents of the file are: \n%s \n", data);

    char *oldWord = "oldWord";
    char *newWord = "foo";

    char *newString = replaceWord(data, oldWord, newWord);
    fclose(fptr1);

    fptr1 = openFile("file1.md", "w");
    if (fptr1 == NULL)
    {
        free(data);
        free(newString);
        return 1;
    }

    writeToFile(fptr1, newString);
    free(data);
    free(newString);

    return 0;
}