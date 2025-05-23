#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void readFile(FILE *fptr)
{

    char data;

    // fgets(data, sizeof(data), fptr);

    int totalBytesRead = 0;

    int count = 0;

    int byteRead;

    while ((byteRead = fread(&data, 1, 1, fptr)) > 0)
    {

        printf("The character %c.\n", data);
        totalBytesRead = totalBytesRead + byteRead;
        if (feof(fptr))
        {
            printf("The end of the file is reached");
            break;
        }

        // Check for errors
        if (ferror(fptr))
        {
            perror("Error reading file");
            break;
        }

        count++;
    }

    // data[totalBytesRead - 1] = '\0';

    printf("The total count %d.\n", count);
    printf("The total bytes read %d. \n", totalBytesRead);
}

void writeFile()
{
    FILE *fptr = fopen("test.md", "w");

    if (fptr == NULL)
    {
        printf("Effor Opening file. \n");
        return;
    }

    char data[] = "Dark Tree Mode";

    // since the string has a null terminator, it is also written to the file
    int bytesWritten = 0;

    int totalBytesWritten = 0;

    while ((bytesWritten = fwrite(data + totalBytesWritten, sizeof(char), 1, fptr)) > 0)
    {
        totalBytesWritten = totalBytesWritten + bytesWritten;

        // printf("The bytes written %d.\n", bytesWritten);
        if (totalBytesWritten == sizeof(data))
        {
            printf("The end of the file is reached.\n");
            break;
        }
    }

    printf("Total bytes written %d. \n", totalBytesWritten);

    if (ferror(fptr))
    {
        printf("Error in writing to file. \n");
    }

    // fclose(fptr);
}

void openFile(char *filename, char *mode)
{

    printf("The file name  is %s.\n", filename);
    printf("The mode is %s. \n", mode);
    FILE *fptr = fopen(filename, mode);

    if (fptr == NULL)
    {
        printf("Failed to load file.\n");
        return;
    }

    printf("The file in memory %p.\n", fptr);

    readFile(fptr);

    fclose(fptr);

    writeFile();
}

int main()
{

    char fileName[] = "test.md";
    char mode[] = "r";

    openFile(fileName, mode);

    return 0;
}
