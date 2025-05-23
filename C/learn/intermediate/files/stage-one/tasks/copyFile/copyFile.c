#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Function to copy a file

void copyFile()
{
    FILE *sourceFile, *destFile;
    int ch;

    // Open the source file in read mode
    sourceFile = fopen("main.md", "r");
    if (sourceFile == NULL)
    {
        printf("Error opening source file.\n");
        return;
    }

    // Open the destination file in write mode
    destFile = fopen("copy.md", "w");
    if (destFile == NULL)
    {
        printf("Error opening the destinatin file.\n");
        fclose(sourceFile);
        return;
    }

    // copy the contents of the source file to the destination file, characer by character

    int lines = 0;

    int i = 0;

    while ((ch = fgetc(sourceFile)) != EOF)
    {

        fputc(ch, destFile);
        if (ch == '\n')
        {
            lines++;
        }
        i++;
    }

    // Close the open files
    fclose(sourceFile);
    fclose(destFile);

    printf("File copied successfully.\n");
    printf("The total bytes copied %d.\n", i);
    printf("The total lines copied %d.\n", lines);
}

int main()
{

    copyFile();
    return 0;
}