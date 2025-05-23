#include "main.h"

void clearInputBuffer()
{
    while (getchar() != '\n')
    {
    }
    return;
}

// data will be passed to this function, it will create a student struct and return it
STUDENT createStudentRecord(char *name, int rollNo, float marks)
{

    STUDENT student;

    strcpy(student.name, name);
    student.rollNo = rollNo;
    student.marks = marks;
    return student;
}

int addStudentRecordToFile(STUDENT student, FILE *fptr)
{
    if (fptr == NULL)
    {
        printf("Error opening file. \n");
        return -1;
    }

    // append the student record to the file
    fprintf(fptr, "%s %d %.2f\n", student.name, student.rollNo, student.marks);

    return 0;
}

void readStudentRecordsFromFile(FILE *fptr)
{
    if (fptr == NULL)
    {
        printf("Error opeining file. \n");
        return;
    }

    STUDENT student;
    printf("Student Records: \n");

    while (fscanf(fptr, "%49s %d %f", student.name, &student.rollNo, &student.marks) != EOF)
    {
        printf("Name: %s, Roll No: %d, Marks: %.2f\n", student.name, student.rollNo, student.marks);
    }

    return;
}

void searchStudentRecord(FILE *fptr, char *name)
{
    if (fptr == NULL)
    {
        printf("Error opeining file. \n");
        return;
    }

    STUDENT student;
    printf("Student Records: \n");

    while (fscanf(fptr, "%49s %d %f", student.name, &student.rollNo, &student.marks) != EOF)
    {
        if (strcmp(student.name, name) == 0)
        {
            printf("Name: %s, Roll No: %d, Marks: %.2f\n", student.name, student.rollNo, student.marks);
            return;
        }
    }

    printf("Student with name %s not found. \n", name);

    return;
}
