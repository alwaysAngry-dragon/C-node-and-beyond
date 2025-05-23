#include "main.h"

// taking inputs is implemented here

// opening the file, check if the file exists or not, if not create it

void checkFileExists(char *filename)
{
    FILE *fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        printf("File does not exists. Creating a new file...\n");

        fptr = fopen(filename, "w");
        fclose(fptr);
        return;
    }

    fclose(fptr);
    printf("File %s already exists. \n", filename);
}

FILE *openFile(char *filename, char *mode)
{
    FILE *fptr = fopen(filename, mode);

    if (fptr == NULL)
    {
        printf("Error opening file. \n");
        exit(1);
        return NULL;
    }

    return fptr;
}

void closeFile(FILE *fptr)
{
    if (fptr != NULL)
    {
        fclose(fptr);
    }
}

void takeInput(char *name, int *rollNo, float *marks)
{
    printf("Enter student name: ");
    scanf("%s", name);
    clearInputBuffer();

    printf("Enter student roll number: ");
    scanf("%d", rollNo);
    clearInputBuffer();

    printf("Enter student marks: ");
    scanf("%f", marks);
    clearInputBuffer();
}

void takeName(char *name)
{
    printf("Enter student name: ");
    scanf("%s", name);
    clearInputBuffer();
}

void start()
{
    checkFileExists("students.txt");

    while (1)
    {
        int choice;
        printf("Enter your choice: \n 1) Add Student - 1 \n 2) Display Students - 2 \n 3) Search Student - 3 \n 4) Remove Student - 4 \n 5) Exit - 5 \n : ");
        scanf("%d", &choice);
        clearInputBuffer();

        if (choice < 1 || choice > 4)
        {
            printf("Exting Program...");
            return;
        }

        switch (choice)
        {
        case 1:
            // add a new student record
            char name[50];
            int rollNo;
            float marks;
            takeInput(name, &rollNo, &marks);
            STUDENT student = createStudentRecord(name, rollNo, marks);
            FILE *fptr = openFile("students.txt", "a");

            addStudentRecordToFile(student, fptr);
            closeFile(fptr);
            printf("Student record added successfully. \n");

            break;
        case 2:
            // display all the studen records
            FILE *fptr2 = openFile("students.txt", "r");

            readStudentRecordsFromFile(fptr2);
            closeFile(fptr2);
            break;
        case 3:
            // search for a student record
            char serchName[50];
            takeName(serchName);
            FILE *fptr3 = openFile("students.txt", "r");

            searchStudentRecord(fptr3, serchName);
            closeFile(fptr3);

            break;
        case 4:
            // search for a student record
            printf("Enter the name of the student to remove: \n");
            char serchRemoveName[50];
            takeName(serchRemoveName);
            FILE *fptr4 = openFile("students.txt", "r");
            removeStudentRecord(fptr4, serchRemoveName);
            closeFile(fptr4);

            break;
        default:
            printf("Invalid Option. \n");
        }
    }
}

int main()
{

    start();
    return 0;
}