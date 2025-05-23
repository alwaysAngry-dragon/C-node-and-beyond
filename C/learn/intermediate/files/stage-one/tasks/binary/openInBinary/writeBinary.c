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

    // read one element

    int data;

    int elementsRead = 0;
    int i = 0;

    while ((elementsRead = fread(&data, sizeof(int), 1, fptr)) > 0)
    {
        i++;
        printf("%d ", data);
        printf(" HeX : 0X%02X, \t", data);
    }

    printf("\nThe number of elements read is %d \n", i);
}

void writeBinary(FILE *fptr)
{

    int data[] = {10, 20, 3, 4, 255};

    int elementsWritten = 0;

    printf("The size of the data is %zu bytes \n", sizeof(data));

    elementsWritten = fwrite(data, sizeof(int), sizeof(data) / sizeof(int), fptr);

    if (elementsWritten > 0)
    {
        printf("The number of elements written is %d \n", elementsWritten);
    }
}

int main()
{

    FILE *fptr;

    fptr = openFileBinary("binary.bin", "wb");

    if (fptr == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    writeBinary(fptr);
    fclose(fptr);

    fptr = openFileBinary("binary.bin", "rb");
    if (fptr == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    readBinary(fptr);
    fclose(fptr);

    return 0;
}