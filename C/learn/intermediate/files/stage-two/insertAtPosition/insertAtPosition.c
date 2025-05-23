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

    int result = _chsize_s(fd, newSize);
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

// take an input string

char *takeInput()
{

    char *input = (char *)malloc(20);

    if (input == NULL)
    {
        printf("Error allocating memory.\n");
        exit(1);
    }

    printf("Enter text: ");
    scanf("%s", input);
    clearInputBuffer();
    return input;
}

void insertToPositionAppend(FILE *fptr, const long fileSize, const char *data, const int position)
{
    // check if the position is valid, i.e not longer than the file and the size does not exceed the file
    int dataLength = strlen(data);

    // max postion the data can be inserted is after the last character

    if (position > fileSize - 2)
    {
        printf("Invalid insert position. \n");
        return;
    }

    // increase the file size by the length of the new data i.e newFileSize = oldFileSize + dataLength

    rewind(fptr); // reset the filepointer to the start

    long newFileSize = fileSize + dataLength;

    resizeFile(fptr, newFileSize);

    // right shift from the position by the size of the new data file[newFileSize-1] = file[oldFileSize-1] repeat upto position

    char temp;
    int end = 1;
    int tracker = fileSize - 1;

    rewind(fptr); // reset the filepointer to the start
    while (tracker >= position)
    {
        fseek(fptr, tracker, SEEK_SET);
        fread(&temp, sizeof(char), 1, fptr);
        fseek(fptr, newFileSize - end, SEEK_SET);
        fwrite(&temp, sizeof(char), 1, fptr);
        tracker--;
        end++;
        if (ferror(fptr))
        {
            printf("Error writing to disk - right shift.\n");
            return;
        }
    }

    // insert the new data to the position
    // set the file pointer position to the insert position

    fseek(fptr, position, SEEK_SET);
    fwrite(data, sizeof(char), dataLength, fptr);

    if (ferror(fptr))
    {
        printf("Error writing to disk - right shift.\n");
        rewind(fptr); // reset the filepointer to the start
        return;
    }
    else
    {
        printf("Data appended to file");
        rewind(fptr); // reset the filepointer to the start
    }
}

void insertToPositionOverwrite(FILE *fptr, const long fileSize, const char *data, const int position)
{

    // check if the position is valid, i.e not longer than the file and the size does not exceed the file
    int dataLength = strlen(data);

    if ((position + dataLength) > fileSize)
    {
        printf("Invalid insert position. \n");
        return;
    }

    // set the file pointer position to the insert position
    fseek(fptr, position, SEEK_SET);

    // if position is valid then insert to position and overwrite
    fwrite(data, sizeof(char), dataLength, fptr);

    if (ferror(fptr))
    {
        perror("Error writnig to disk.\n");
    }
    else
    {
        printf("String inserted successfully\n");
    }
    rewind(fptr); // reset the filepointer to the start
}

void start()
{

    FILE *fptr = NULL;
    fptr = openFile("file.md", "r+b");

    // FILE *fptr1 = NULL;
    // fptr1 = openFile("file.md", "r");

    const long fileSize = getFileSize(fptr) - 1; // 1 is subscracted because \n is translated as \r\n, i.e 2 bytes

    printf("The size of file is %zu. \n", fileSize);

    if (fptr == NULL)
    {
        printf("Error opening file.");
        return;
    }

    while (1)
    {
        printf("Enter your choice:\n1. Insert String Overwrite:\n2. Insert String Append:\n3. Exit:\n:");
        int choice;

        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice)
        {
        case 1:
            printf("Enter string to insert: ");
            char *input;
            input = takeInput();

            printf("Enter position to insert into: ");
            int position;

            scanf("%d", &position);

            clearInputBuffer();

            insertToPositionOverwrite(fptr, fileSize, input, position);

            free(input);
            break;

        case 2:
            printf("Enter string to insert: ");
            char *input2;
            input2 = takeInput();

            const long fileSize2 = getFileSize(fptr);

            printf("Enter position to append into: ");
            int positionAppend;
            scanf("%d", &positionAppend);

            if (positionAppend > fileSize2 - 2)
            {
                printf("Invalid position, cannot be greater than %d\n", fileSize2 - 2);

                break;
            }

            clearInputBuffer();

            insertToPositionAppend(fptr, fileSize2, input2, positionAppend);

            free(input2);
            break;

        case 3:
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
