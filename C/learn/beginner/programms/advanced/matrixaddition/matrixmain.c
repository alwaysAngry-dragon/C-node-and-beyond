#include "matrix.h"

void clearInputBuffer()
{
    while (getchar() != '\n')
    {
    }
    return;
}

int takeInput()
{
    int x;
    printf("Enter element: ");
    scanf("%d", &x);
    clearInputBuffer();
    return x;
}

void displayMatrix(MATRIX *matrix)
{

    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->cols; j++)
        {

            printf("%d \t", matrix->arr[i][j]);
        }
        printf("\n");
    }
}

void enterMatrixDate(MATRIX *matrix, int rows, int columns)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {

            matrix->arr[i][j] = takeInput();
        }
    }
    displayMatrix(matrix);
}

void start()
{
    int rows, columns;
    printf("Enter the number of rows: \n");
    scanf("%d", &rows);
    clearInputBuffer();

    printf("Enter the number of columns: \n");
    scanf("%d", &columns);
    clearInputBuffer();

    // initialize the matrix
    MATRIX matrix1, matrix2;
    initializeMatrix(&matrix1, rows, columns);
    initializeMatrix(&matrix2, rows, columns);

    // enter the numbers
    enterMatrixDate(&matrix1, rows, columns);
    enterMatrixDate(&matrix2, rows, columns);

    // add the matrix, output will be a new matrix

    printf("The result is.\n");
    addMatrix(&matrix1, &matrix2);
}

int main()
{
    start();

    return 0;
}