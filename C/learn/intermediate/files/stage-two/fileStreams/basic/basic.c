#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// output stream

void outputStream(char *project)
{
    printf("\nFile read: ");

    fprintf(stdout, project);
}

// input stream

void inputStream()
{
    char project[1024];
    printf("Enter project name: ");
    fgets(project, sizeof(project), stdin);
    int i = 0;
    while (i < 5)
    {
        fprintf(stderr, "Error: Could not open file %d.\n", i);
        i++;
    }

    // printf("The file is: %s", project);
    outputStream(project);
}

void stimulateStdinFgetS()
{
    // use fgets with stdin
    char line[100];

    if (fgets(line, sizeof(line), stdin))
    {
        printf("You entered: %s", line);
    }
}

void stimulateStdinFread()
{
    char i[1024];
    while (fread(i, sizeof(char), 5, stdin) == 5)
    {
        printf("%s \t", i);
    }
}

// error stream

void read()
{
    FILE *file = fopen("input.md", "rb");

    if (file == NULL)
    {
        printf("Error reading file. \n");
        return;
    }

    int count = 0;

    char ch;

    while (fread(&ch, sizeof(char), 1, file) > 0)
    {
        if (ferror(file))
        {
            printf("Error in file operation.\n");
            exit(1);
        }
        count++;
        printf("The character read is %c \n", ch);
    }

    printf("The number of bytes read in binary is %d\n", count);
    rewind(file);

    count = 0;
    int t_ch;
    while ((t_ch = fgetc(file)) != EOF)
    {
        printf("The character read is %c \n", t_ch);
        count++;
    }
    printf("The number of bytes read in character mode is %d", count);
    fclose(file);
}

void write()
{
    FILE *file = fopen("input.md", "w");

    int count = fprintf(file, "Hello\n");

    if (ferror(file))
    {
        printf("Error while writing to disk.\n");
    }

    printf("Total data written %d", count);

    fclose(file);
}

int main()
{
    write();
    read();
    // inputStream();
    // stimulateStdinFgetS();
    // stimulateStdinFread();

    return 1;
}