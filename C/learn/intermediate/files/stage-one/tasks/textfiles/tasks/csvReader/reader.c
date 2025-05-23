#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void calculateAvgSalary(FILE *fptr)
{
    float salarySum = 0;
    int lineCount = 0;

    char name[100];
    int age;
    float salary;

    // skip the header line
    char header[256];
    if (fgets(header, sizeof(header), fptr) == NULL)
    {
        printf("Error: File is empty or could not read header.\n");
        fclose(fptr);
        return;
    }

    // Read each line of the CSV file
    while (fscanf(fptr, "%[^,],%d,%f", name, &age, &salary) == 3)
    {
        // printf("Name: %s, Age: %d, Salary: %.2f\n", name, age, salary);
        salarySum += salary;
        lineCount++;
    }

    printf("Total Records %d. \n", lineCount);
    printf("Total Salary: %.2f. \n", salarySum);

    if (lineCount > 0)
    {
        float avgSalary = salarySum / lineCount;
        printf("Average Salary: %.2f \n", avgSalary);
    }
    else
    {
        printf("No data found in the file.\n");
    }

    fclose(fptr);
    return;
}

FILE *openFile(char *filename, char *mode)
{
    if (fopen(filename, "r") == NULL)
    {
        printf("File not found\n");
        exit(1);
        return NULL;
    }

    FILE *fptr = fopen(filename, mode);

    if (fptr == NULL)
    {
        printf("Error opening file. \n");
        exit(1);
        return NULL;
    }

    return fptr;
}

int main()
{

    FILE *fptr = openFile("data.csv", "r");
    if (fptr == NULL)
    {
        return 1;
    }
    calculateAvgSalary(fptr);
}