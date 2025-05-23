#ifndef STUDENT_RECORD_H
#define STUDENT_RECORD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
    char name[50];
    int rollNo;
    float marks;
} STUDENT;

// Function prototypes

void clearInputBuffer();

STUDENT createStudentRecord(char *name, int rollNo, float marks);
int addStudentRecordToFile(STUDENT student, FILE *fptr);
void readStudentRecordsFromFile(FILE *fptr);
void searchStudentRecord(FILE *fptr, char *name);

#endif