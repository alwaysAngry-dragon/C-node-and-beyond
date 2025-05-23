#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

FILE *openFileBinary(const char *filename, const char *mode)
{

    FILE *fptr = fopen(filename, mode);
    if (fptr == NULL)
    {
        printf("Error opening file %s\n", filename);
        return NULL;
    }

    return fptr;
}

void readBinary(FILE *fptr)
{

    char data[256];
    int elementsRead = 0;

    elementsRead = fread(data, sizeof(char), sizeof(data), fptr);

    data[elementsRead] = '\0';

    if (elementsRead > 0)
    {
        printf("The nubmber of elements read is %d \n", elementsRead); // this is 14 as the \n is counted as two bytes on windows
        // print the binary data read

        printf("The data read is %s \n", data);
    }
    else
    {
        printf("No data read from the file.\n");
    }

    printf("Hex dump:\n");

    for (int i = 0; i <= elementsRead; i++)
    {
        printf("%02X ", data[i]);
        if ((i + 1) % 16 == 0)
            printf("\n"); // this will show 15 bytes as '\0' is added to the end of the string
    }
    printf("\n");
}

int main()
{

    FILE *fptr;

    fptr = openFileBinary("test.md", "rb");

    if (fptr == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    readBinary(fptr);
    fclose(fptr);

    return 0;
}