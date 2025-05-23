#include "matrix.h"

void initializeMatrix(MATRIX *matrix, int rows, int columns)
{
    if (rows > MAX_ROWS || columns > MAX_COLS)
    {
        printf("Invalid amount of rows or columns!");
        exit;
    }

    matrix->rows = rows;
    matrix->cols = columns;
}

void addMatrix(MATRIX *matrix1, MATRIX *matrix2)
{
    MATRIX tempMatrix;

    tempMatrix.rows = matrix1->rows;
    tempMatrix.cols = matrix1->cols;

        for (int i = 0; i < tempMatrix.rows; i++)
    {
        for (int j = 0; j < tempMatrix.cols; j++)
        {

            tempMatrix.arr[i][j] = matrix1->arr[i][j] + matrix2->arr[i][j];
            printf("%d \t", tempMatrix.arr[i][j]);
        }
        printf("\n");
    }
}
