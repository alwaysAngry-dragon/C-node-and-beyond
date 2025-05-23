#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// crete a large file of 1204 bytes

void createFileBinary()
{
    FILE *file = fopen("file.bin", "wb");
    const int size = 1024;
    int i = 0;

    while (i < size)
    {
        // here the binary value at the memory address &i will be written to the file and not the decimal representation of i.
        fwrite(&i, sizeof(int), 1, file);
        if (ferror(file))
        {
            printf("Error writing to file.\n");
            exit(1);
        }
        i++;
    }

    fprintf(stdout, "The file is created\n");
    fclose(file);
    return;
}

// crete a large file of 1204 bytes

void createFile()
{
    FILE *file = fopen("file.md", "w");
    const int size = 1024;
    int i = 0;

    while (i < size)
    {

        fprintf(file, "%d ", i);
        if (ferror(file))
        {
            printf("Error writing to file.\n");
            exit(1);
        }
        i++;
    }

    fprintf(stdout, "The file is created\n");
    fclose(file);
    return;
}

void readBinary()
{
    FILE *file = fopen("file.bin", "rb");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        exit(1);
    }

    const int size = 1024;
    int i;

    while (fread(&i, sizeof(int), 1, file) > 0)
    {

        if (ferror(file))
        {
            printf("Error reading from disk.\n");
            exit(1);
        }
        printf("%d \t", i);
    }

    if (feof(file))
    {
        printf("\n--- The end ---\n");
    }

    fclose(file);
    return;
}

void readFile()
{

    FILE *file = fopen("file.md", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        exit(1);
    }

    const int size = 1024;
    int i;

    while (fscanf(file, "%d", &i) > 0)
    {

        if (ferror(file))
        {
            printf("Error reading from disk.\n");
            exit(1);
        }
        printf("%d \t", i);
    }

    if (feof(file))
    {
        printf("\n--- The end ---\n");
    }

    fclose(file);
    return;
}

int main()
{

    // createFile();
    // readFile();
    // createFileBinary();
    // readBinary();
    return 0;
}
