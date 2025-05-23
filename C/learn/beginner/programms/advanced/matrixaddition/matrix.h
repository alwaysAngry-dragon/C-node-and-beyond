#ifndef MATRIX_X
#define MATRIX_X

#include <stdio.h>
#include <stdlib.h>

#define MAX_ROWS 5
#define MAX_COLS 5

typedef struct
{
    int arr[MAX_ROWS][MAX_COLS];
    int rows;
    int cols;

} MATRIX;

void initializeMatrix(MATRIX *matrix, int rows, int columns);
void addMatrix(MATRIX *matrix1, MATRIX *matrix2);

#endif