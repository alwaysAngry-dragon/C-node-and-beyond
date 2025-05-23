#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void basicStdinStdout()
{
    char buffer[1024];

    printf("Enter the project: ");

    if (fgets(buffer, 1024, stdin))
    {
        fputs("You entered:", stdout);
        fputs(buffer, stdout);
    }
}

void readNumbers()
{
    int i;

    while (fscanf(stdin, "%d", &i) == 1)
    {
        fprintf(stdout, "Read number: %d\n", i);
    }
}

void likeCat()
{
    int c;

    while (fgetc(stdin) != 'EOF')
    {
        putc(c, stdout);
    }
}

int main()
{
    // basicStdinStdout();

    // readNumbers();
    likeCat();

    return 1;
}