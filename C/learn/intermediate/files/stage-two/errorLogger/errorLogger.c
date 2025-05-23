#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// to run and set the stderr to a file use main.exe 2>error.log
// OR main.exe 2>>error.log

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

int main()
{
    inputStream();

    return 1;
}