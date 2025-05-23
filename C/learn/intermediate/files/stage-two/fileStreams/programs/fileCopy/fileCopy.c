#include <stdio.h>
#include <stdlib.h>

void copyChracter(const int argc, char *argv[])
{

    FILE *src = fopen(argv[1], "rb");
    FILE *dst = fopen(argv[2], "wb");

    if (!src || !dst)
    {
        perror("File error");
        exit(EXIT_FAILURE);
    }

    int c;
    while ((c = fgetc(src)) != EOF)
    {
        fputc(c, dst);
    }

    fclose(src);
    fclose(dst);
}

void copyBinary(const int argc, char *argv[])
{

    const int BUF_SIZE = 1024;

    FILE *src = fopen(argv[1], "rb");
    FILE *dst = fopen(argv[2], "wb");

    if (!src || !dst)
    {
        perror("File error");
        exit(EXIT_FAILURE);
    }

    char buffer[BUF_SIZE];
    size_t bytes;

    while ((bytes = fread(buffer, sizeof(char), BUF_SIZE, src)) > 0)
    {
        printf("Number of elements read %zu.", bytes);

        fwrite(buffer, sizeof(char), bytes, dst);
    }

    fclose(src);
    fclose(dst);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s source dest\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    copyBinary(argc, argv);
    return 0;
}