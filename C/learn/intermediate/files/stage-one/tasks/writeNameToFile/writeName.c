#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// create a new file and write some content to it

char *takeInput()
{
    char *content = (char *)malloc(100 * sizeof(char));

    printf("Enter the content  to write to the file: ");

    // scanf("%s", content);

    fgets(content, 100, stdin);

    int i = 0;

    while (content[i] != '\0')
    {
        i++;
    }

    // remove the new line character form the string
    content[i - 1] = '\0';

    return content;
}

void writeFile(FILE *fptr, char *content)
{
    const int WRITE_LENGTH = 1;
    int bytesWritten = 0;
    int totalBytesWritten = 0;

    int count = 0;

    int i = 0;
    while (1)
    {
        if (content[i] == '\0')
        {
            // the null terminator is not written to the file
            break;
        }
        bytesWritten = fwrite(content + i, sizeof(char), WRITE_LENGTH, fptr);
        totalBytesWritten = totalBytesWritten + bytesWritten;
        i++;
    }

    if (ferror(fptr))
    {
        printf("Error in writing to file. \n");
        return;
    }

    fclose(fptr);
    printf("File is written successfully. Total bytes written %d. \n", i);
}

void readFile()
{

    FILE *fptr = fopen("writeName.md", "r");

    char data[100]; // Buffer to store data
    int i = 0;

    // Read one character at a time until EOF or buffer is full
    while (i < 99 && fread(data + i, sizeof(char), 1, fptr) > 0)
    {
        i++;
    }

    // Null-terminate the string
    data[i] = '\0';

    // Check for errors
    if (ferror(fptr))
    {
        perror("Error reading file");
        return;
    }

    printf("The total bytes read %d. \n", i);

    // Print the data
    printf("The data is:\n%s\n", data);
}

FILE *openFile()
{
    FILE *fptr = fopen("writeName.md", "w");

    if (fptr == NULL)
    {
        printf("Error opening file. \n");
        return NULL;
    }

    return fptr;
}

void appendToFile(char *content)
{

    FILE *fptr = fopen("writeName.md", "a");

    if (fptr == NULL)
    {
        perror("Error opening file");
        return;
    }

    // Write content and also add a newline after each append
    fwrite(content, sizeof(char), strlen(content), fptr);
    fwrite("\n", sizeof(char), 1, fptr); // Optional: adds a newline

    fclose(fptr);
    printf("File is appended successfully.\n");
}

int main()
{
    char *content = takeInput();

    // FILE *fptr = openFile();

    // if (fptr == NULL)
    // {
    //     return 1;
    // }

    // writeFile(fptr, content);

    // free(content);

    // fclose(fptr);
    // readFile();

    appendToFile(content);

    free(content);
    content = takeInput();

    appendToFile(content);

    free(content);

    return 0;
}