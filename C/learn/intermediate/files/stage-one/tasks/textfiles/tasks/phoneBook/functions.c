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

int searchStudentRecord(FILE *fptr, char *name)
{
    if (fptr == NULL)
    {
        printf("Error opeining file. \n");
        return 0;
    }

    STUDENT student;
    printf("Student Records: \n");

    while (fscanf(fptr, "%49s %d %f", student.name, &student.rollNo, &student.marks) != EOF)
    {
        if (strcmp(student.name, name) == 0)
        {
            printf("Name: %s, Roll No: %d, Marks: %.2f\n", student.name, student.rollNo, student.marks);
            return 1;
        }
    }

    printf("Student with name %s not found. \n", name);

    return 0;
}

FILE *removeStudentRecord(FILE *fptr, char *name)
{
    if (fptr == NULL)
    {
        printf("Error opeining file. \n");
        return NULL;
    }

    if (!searchStudentRecord(fptr, name))
    {

        return NULL;
    }

    rewind(fptr); // Reset the file pointer

    STUDENT student;

    // create a temporary file in append mode
    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL)
    {
        printf("Error opening tempory file. \n");
        return NULL;
    }

    while (fscanf(fptr, "%49s %d %f", student.name, &student.rollNo, &student.marks) != EOF)
    {
        if (strcmp(student.name, name) == 0)
        {
            // Do not append the student record to the temp file
            printf("Removing studen record: %s \n", student.name);
            continue;
        }

        // append the student record to the temp file
        fprintf(tempFile, "%s %d %.2f\n", student.name, student.rollNo, student.marks);
    }

    fclose(fptr);
    fflush(tempFile); // flush the temp FILE buffer to ensure all data is written
    fclose(tempFile);
    // Replace the original file with the temporary file
    if (remove("students.txt") != 0)
    {
        printf("Error deleting original file.\n");
        return NULL;
    }
    if (rename("temp.txt", "students.txt") != 0)
    {
        printf("Error renaming temporary file.\n");
        return NULL;
    }

    return NULL;
}