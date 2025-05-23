#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
    int id;
    char name[20];
} MyStruct;

void clearInputBuffer()
{
    while (getchar() != '\n')
    {
        // clear the input buffer
    }
}

void createFile(const char *filename, FILE **file)
{
    *file = fopen(filename, "rb");
    if (*file == NULL)
    {
        // file does no exists, create it
        *file = fopen(filename, "wb");
        if (*file == NULL)
        {
            printf("Error creating file\n");
            exit(1);
        }
    }
}

void openFile(const char *filename, FILE **file, const char *mode)
{
    *file = fopen(filename, mode);
    if (*file == NULL)
    {
        printf("Error opening file \n");
        exit(1);
    }
}

void appendToFile(FILE *file, MyStruct myStruct)
{
    // write the struct to the file
    size_t result = fwrite(&myStruct, sizeof(MyStruct), 1, file);
    if (result != 1)
    {
        printf("Error writing to file\n");
        exit(1);
    }
}

void readDataFromFile(FILE *file)
{
    MyStruct *myStruct = malloc(sizeof(MyStruct));

    while (1)
    {
        size_t result = fread(myStruct, sizeof(MyStruct), 1, file);

        if (result == 0) // EOF reached as no data read
        {
            free(myStruct);
            break;
        }

        if (result != 1)
        {
            printf("Error reading from file\n");
            exit(1);
        }

        // read the struct from the the file

        printf("The id is %d\n", myStruct->id);
        printf("The name is %s\n", myStruct->name);
        printf("-- \n");
    }
}

// create a struct member
MyStruct createStructMember()
{
    // take user input for the struct member
    MyStruct myStruct;
    printf("Enter the id: ");
    scanf("%d", &myStruct.id);
    clearInputBuffer();
    printf("Enter the name: ");
    scanf("%s", myStruct.name);
    clearInputBuffer();
    return myStruct;
}

void start()
{

    FILE *fptr = NULL;
    const char *filename = "myStruct.bin";
    createFile(filename, &fptr);
    fclose(fptr);

    while (1)
    {
        printf("Enter your choice:\n1. Create member:\n2. Show members:\n3. Search member:\n4. Delete member:\n5. Exit:\n");
        int choice;

        scanf("%d", &choice);
        clearInputBuffer();
        switch (choice)
        {
        case 1:
            MyStruct str = createStructMember();
            openFile(filename, &fptr, "ab");
            appendToFile(fptr, str);
            fclose(fptr);
            break;
        case 2:
            // show members

            printf("The members are: \n");
            openFile(filename, &fptr, "rb");
            readDataFromFile(fptr);
            fclose(fptr);

            break;
        case 3:
            // search member
            break;
        case 4:
            // delete member
            break;
        case 5:
            printf("Exiting... \n");
            fclose(fptr);
            exit(0);
        default:
            printf("Invalid choice\n");
        }
    }
}

// write to file

int main()
{
    start();

    return 0;
}
