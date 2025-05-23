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

int searchRecord(FILE *file, const char *name)
{
    if (name == NULL)
    {
        printf("Invalid Name!\n");
        return -1;
    }

    MyStruct *myStruct = malloc(sizeof(MyStruct));

    int position = 0;

    while (1)
    {
        size_t result = fread(myStruct, sizeof(MyStruct), 1, file);

        if (result == 0) // EOF reached as no data read
        {
            free(myStruct);
            printf("Record not found!\n");

            return -1;
        }

        if (result != 1)
        {
            printf("Error reading from file\n");
            free(myStruct);
            exit(1);
        }

        if (strcmp(myStruct->name, name) == 0) // record found
        {
            printf("Record Found. at %d \n", position);
            printf("The id is %d\n", myStruct->id);
            printf("The name is %s\n", myStruct->name);

            return position;
        }
        position++;
    }
}

// updating record in file in-place
void updateRecord(FILE *fptr, const char *newName, const int positionOffset)
{

    // 1) find the offset of the record
    if (positionOffset < 0)
    {
        printf("Invalid Operation. Offset %d is not valid", positionOffset);
        return;
    }

    MyStruct *myStruct = malloc(sizeof(MyStruct));

    // 1.2) move the offset position to the correct location and get the struct id from the file, i.e fread

    // move the file pointer to the particular location
    int status = fseek(fptr, positionOffset * sizeof(MyStruct), SEEK_SET);

    if (status == 0) // 0 means no error while moving the file pointer
    {
        // 2) create the new struct record, with same ID and newName
        int result = fread(myStruct, sizeof(MyStruct), 1, fptr);
        if (result == 1)
        {
            printf("Record found.\n");
            printf("The id is: %d\n", myStruct->id);
            printf("The Old name is: %s\n", myStruct->name);
            printf("The new name is set to : %s\n", newName);

            strcpy(myStruct->name, newName);

            // 3) replace the old binary data with the binary data of the new struct at the offset position

            fseek(fptr, positionOffset * sizeof(MyStruct), SEEK_SET); // again move filepointer to correct location
            int elementsWritten = fwrite(myStruct, sizeof(MyStruct), 1, fptr);
            if (elementsWritten == 1)
            {
                printf("Record updated Successfully.\n");
            }
        }
    }

    // 4) done

    free(myStruct);
    return;
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
        printf("Enter your choice:\n1. Create member:\n2. Show members:\n3. Search member:\n4. Update member:\n5. Delete member:\n6. Exit:\n");
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
            // search member record
            char name[100];
            printf("Enter the name to search: ");
            scanf("%s", name);
            clearInputBuffer();
            openFile(filename, &fptr, "rb");

            searchRecord(fptr, name);
            fclose(fptr);
            break;
        case 4:
            // update member

            char nameOld[100];

            int positionOffset = -1;
            printf("Enter the name to update: ");
            scanf("%s", nameOld);
            clearInputBuffer();
            openFile(filename, &fptr, "rb");

            positionOffset = searchRecord(fptr, nameOld);
            fclose(fptr);

            if (positionOffset < 0)
            {
                break;
            }

            // open the file in reab+b mode, so we can write at any position withoud truncating.
            char newName[100];
            printf("Enter the new name: ");
            scanf("%s", newName);

            openFile(filename, &fptr, "r+b");
            updateRecord(fptr, newName, positionOffset);
            fclose(fptr);

            break;

        case 5:
            // delete member
            break;
        case 6:
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
