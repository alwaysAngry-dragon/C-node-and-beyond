#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
    char question[256];
    char *options[4];
    char answer[256];
} Question;

// read the file
FILE *openFile(const char *filename)
{
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    return file;
}

// take input from the user

void takeInput(char *input)
{

    while (1)
    {
        printf("Enter your option A B C or D : ");
        scanf("%s", input);

        while (getchar() != '\n')
        {
            // clear the input buffer
        }

        // check if the input is valid
        if (strcmp(input, "A") == 0 || strcmp(input, "B") == 0 || strcmp(input, "C") == 0 || strcmp(input, "D") == 0)
        {
            return;
        }
        else
        {
            printf("Invalid input. Please enter A, B, C or D.\n");
        }
    }
}

void start(FILE *fptr)
{
    int i = 0;
    int totalQuestions = 0;

    Question q;

    q.options[0] = (char *)malloc(256 * sizeof(char));
    q.options[1] = (char *)malloc(256 * sizeof(char));
    q.options[2] = (char *)malloc(256 * sizeof(char));
    q.options[3] = (char *)malloc(256 * sizeof(char));

    // skip the header line
    char header[256];
    if (fgets(header, sizeof(header), fptr) == NULL)
    {
        printf("Error: File is empty or could not read data.\n");
        fclose(fptr);
        return;
    }

    // read the question, options and answer from the csv file
    while (fscanf(fptr, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", q.question, q.options[0], q.options[1], q.options[2], q.options[3], q.answer) == 6)
    {
        printf("Question: %s \n", q.question);
        printf("A: %s \n", q.options[0]);
        printf("B: %s \n", q.options[1]);
        printf("C: %s \n", q.options[2]);
        printf("D: %s \n", q.options[3]);

        char input[10];
        takeInput(input);

        // check if the correnct answer is given
        if (strcmp(input, q.answer) == 0)
        {
            printf("Correct answer! \n");
            i++;
        }
        else
        {
            printf("Wrong answer! \n");
            printf("Correct answer is option: %s.\n", q.answer);
        }
        totalQuestions++;
    }

    printf("Total Questions: %d \n", totalQuestions);
    printf("Correct Answers: %d \n", i);

    free(q.options[0]);
    free(q.options[1]);
    free(q.options[2]);
    free(q.options[3]);
}

int main()
{
    FILE *file = openFile("quiz.csv");
    if (file == NULL)
    {
        return 1;
    }

    start(file);
    fclose(file);

    return 0;
}