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

void compareBinary(FILE *fptr1, FILE *fptr2)
{
    unsigned char byte1, byte2;

    while (1)
    {
        // Read one byte from each file
        size_t bytesRead1 = fread(&byte1, sizeof(byte1), 1, fptr1);
        size_t bytesRead2 = fread(&byte2, sizeof(byte2), 1, fptr2);

        // Check if we've reached the end of one or both files
        if (bytesRead1 != bytesRead2)
        {
            printf("The binary files are not identical (different sizes).\n");
            return;
        }

        // If both reads failed (end of file reached for both), the files are identical
        if (bytesRead1 == 0 && bytesRead2 == 0)
        {
            printf("The binary files are identical.\n");
            return;
        }

        printf("%c \t", byte1);
        // Compare the bytes read from both files
        if (byte1 != byte2)
        {
            printf("The binary files are not identical (content mismatch).\n");
            return;
        }
    }
}

int main()
{

    FILE *fptr1, *fptr2;

    fptr1 = openFileBinary("test1.bin", "rb");
    fptr2 = openFileBinary("test2.bin", "rb");

    if (fptr1 == NULL || fptr2 == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    compareBinary(fptr1, fptr2);

    fclose(fptr1);
    fclose(fptr2);

    return 0;
}