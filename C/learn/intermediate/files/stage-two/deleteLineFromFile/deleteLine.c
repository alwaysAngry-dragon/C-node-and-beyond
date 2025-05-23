#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include <io.h>    // For _chsize_s, _fileno
#include <fcntl.h> // For _fileno

void resizeFile(FILE *fptr, long newSize)
{
    int fd = _fileno(fptr);
    if (fd == -1)
    {
        printf("Error getting file descriptor.\n");
        return;
    }

    int result = _chsize_s(fd, newSize); // if newsize if less than before the file is reduced, if more than increased and null values added to the increased size
    if (result != 0)
    {
        perror("Error resizing file");
        return;
    }

    printf("File resized successfully to %ld bytes.\n", newSize);
}

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

// open  file

FILE *openFile(const char *fileName, const char *mode)
{

    FILE *file = fopen(fileName, mode);

    if (file == NULL)
    {
        perror("Error accessing file. \n");
        exit(1);
    }

    return file;
}

int countLines(FILE *fptr)
{
    rewind(fptr);
    int lineCount = 0;
    char temp[200];

    while (fgets(temp, 199, fptr) != NULL)
    {
        lineCount++;
    }

    if (feof(fptr))
    {

        printf("Number of lines %d \n", lineCount);
    }
    else
    {
        printf("Error in reading file.\n");
        exit(1);
    }
    if (ferror(fptr))
    {
        printf("Error in file reading.");
        exit(1);
    }

    rewind(fptr); // rewind the file pointer offset to the start
    return lineCount;
}

void leftShift(FILE *fptr, int lineStartOffset, int lineEndOffset, int nextLineOffset, int lineSize, int fileSize)
{
    // left shift by the lineSize starting from the nextLineOffset to the EOF i.e fileSize

    int currentOffset = nextLineOffset;

    char temp;

    while (currentOffset <= fileSize)
    {
        fseek(fptr, currentOffset, SEEK_SET);            // go the the next line offset position
        fread(&temp, sizeof(char), 1, fptr);             // read from the offset position
        fseek(fptr, currentOffset - lineSize, SEEK_SET); // go to the previous position
        fwrite(&temp, sizeof(char), 1, fptr);
        currentOffset++;
    }

    if (ferror(fptr))
    {
        printf("Error writing to disk.\n");
        exit(1);
    }

    printf("Line removed successfully\n");

    rewind(fptr);

    resizeFile(fptr, fileSize - lineSize);
}

void removeLine(FILE *fptr, const int linePosition, const int fileSize)
{
    // get the starting offset of the line
    int lineCount = 0;
    char temp[200];

    int startOffset = 0;
    int endOffset = 0;
    int nextLineStartOffset = 0;
    int lineSize = 0;

    while (fgets(temp, 199, fptr) != NULL)
    {
        lineCount++;
        if (lineCount == linePosition)
        {
            // next line starting offset
            nextLineStartOffset = ftell(fptr);
            // get the ending offset of the line to to removed
            endOffset = nextLineStartOffset - 1;
            // get the size of the line getting removed
            lineSize = nextLineStartOffset - startOffset;

            printf("Starting offset: %d \n", startOffset);
            printf("End Offset: %d \n", endOffset);
            printf("Line size: %zu \n", lineSize);
            printf("Next line start offset: %d \n", nextLineStartOffset);
            leftShift(fptr, startOffset, endOffset, nextLineStartOffset, lineSize, fileSize);

            break;
        }
        startOffset = ftell(fptr);
    }
}

void start()
{

    FILE *fptr = NULL;
    fptr = openFile("file.md", "r+b");

    const long fileSize = getFileSize(fptr);

    printf("The size of file is %zu. \n", fileSize);

    if (fptr == NULL)
    {
        printf("Error opening file.");
        return;
    }

    while (1)
    {
        printf("Enter your choice:\n1.Count Lines:\n2. Exit:\n:");
        int choice;

        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice)
        {
        case 1:

            const int lineCount = countLines(fptr);

            if (lineCount <= 0)
            {
                printf("The file is empty.\n");
                break;
            }

            printf("Enter line position to delete ( range 1 to %d)\n", lineCount);
            int position;

            scanf("%d", &position);
            clearInputBuffer();

            if (position > lineCount || position < 1)
            {
                printf("Invalid position.\n");
                break;
            }
            removeLine(fptr, position, fileSize);

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