#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void clearInputBuffer()
{
    while (getchar() != '\n')
    {
    }
    return;
}

char *takeInput()
{
    char *temp = (char *)malloc(20 * sizeof(char));

    printf("Enter a string: ");
    scanf("%s", temp);
    clearInputBuffer();
    return temp;
}

char *takeInputFgets()
{
    char *temp = (char *)malloc(20 * sizeof(char));
    printf("Enter text: ");
    fgets(temp, 20, stdin); // since a character is 1 btye so 20 is same as 20*sizeof(char)

    // remvove the \n from the string since fgets adds it to the end if before \0 if there is space
    size_t len = strlen(temp);
    if (len > 0 && temp[len - 1] == '\n')
    {
        temp[len - 1] = '\0';
    }
    return temp;
}

int stringLen()
{
    char *str = takeInput();

    int len = 0;

    while (*(str + len) != '\0')
    {

        len++;
    }

    free(str);
    printf("The length is %d \n", len);
    return len;
}

void stringCopy()
{
    char *str1 = takeInput();
    char *str2 = malloc(strlen(str1) + 1); // Allocate enough memory for str2

    int i = 0;

    while (str1[i] != '\0')
    {
        str2[i] = str1[i];
        i++;
    }

    str2[i] = str1[i];

    printf("The copied string is %s \n", str2);

    free(str1);
    free(str2);
}

void stringConcat()
{
    char *str1 = takeInput();
    char *str2 = takeInput();

    int i = 0;

    while (str1[i] != '\0')
    {
        i++;
    }

    int j = 0;
    while (str2[j] != '\0')
    {
        str1[i] = str2[j];
        i++;
        j++;
    }
    str1[i] = str2[j];
    printf("The new string is %s\n", str1);
}

void countVowConst()
{
    char *str = takeInput();
    int vowelsCount = 0;
    int constCount = 0;

    for (int i = 0; str[i] != '\0'; i++)
    {

        if (str[i] >= 'a' && str[i] <= 'z')
        {
            if (str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u')
            {
                vowelsCount++;
            }
            else
            {
                constCount++;
            }
        }
    }

    printf("The number of vowels is %s = %d.\n. The numer of constants = %d", str, vowelsCount, constCount);
}

void stringCountSpace()
{
    char *str = takeInputFgets();
    if (strlen(str) == 0)
    {
        printf("Please enter a word.\n");
        return;
    }
    int wordCount = 1;

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == 32)
        {
            wordCount++;
        }
    }

    printf("The number of words %d.", wordCount);
    free(str);
}

void stringRemoveDuplicates()
{
    char *str = takeInput();
    if (str == NULL)
    {
        printf("Failed to take input.\n");
        return;
    }
    char *newStr = (char *)malloc(strlen(str) + 1);
    if (newStr == NULL)
    {
        printf("Memory allocation failed.\n");
        free(str);
        return;
    }

    int insertPosition = 0;
    bool insert;
    for (int i = 0; str[i] != '\0'; i++)
    {
        insert = true;
        for (int j = 0; j < insertPosition; j++)
        {
            if (newStr[j] == str[i])
            {
                insert = false;
                break;
            }
        }

        if (insert)
        {
            newStr[insertPosition] = str[i];
            insertPosition++;
        }
    }
    newStr[insertPosition] = '\0';

    printf("The corrected string is %s \n", newStr);
    free(str);
    free(newStr);
}

void stringRemoveDuplicatesBetter()
{
    // removing duplicate in place
    char *str = takeInput();
    bool seen[256] = {false};

    int insertPosition = 0;

    for (int i = 0; str[i] != '\0'; i++)
    {
        unsigned char val = (unsigned char)str[i];
        if (!seen[val])
        {
            seen[val] = true;
            str[insertPosition] = str[i];
            insertPosition++;
        }
    }

    str[insertPosition] = '\0';

    printf("The modified string %s \n", str);
    free(str);
}

void stringCompare()
{

    char *str1 = takeInput();
    char *str2 = takeInput();

    // Check if memory allocation failed
    if (str1 == NULL || str2 == NULL)
    {
        printf("Memory allocation failed.\n");
        if (str1)
            free(str1);
        if (str2)
            free(str2);
        return;
    }

    int i = 0;

    // Compare characters until one string ends
    while (str1[i] != '\0' && str2[i] != '\0')
    {
        if (str1[i] != str2[i])
        {
            printf("The strings are not equal!\n");
            free(str1);
            free(str2);
            return;
        }
        i++;
    }

    // Check if both strings ended at the same point
    if (str1[i] == '\0' && str2[i] == '\0')
    {
        printf("The strings are equal!\n");
    }
    else
    {
        printf("The strings are not equal!\n");
    }

    // Free allocated memory
    free(str1);
    free(str2);
}

void stringSearchSubStr()
{
    // Take input strings
    char *str = takeInput();
    char *subStr = takeInput();

    int strLen = strlen(str);
    int subStrLen = strlen(subStr);

    bool found = false;
    int matchIndex = -1;

    // Iterate through the main string to find the substring
    for (int i = 0; i <= strLen - subStrLen; i++)
    {
        bool match = true;

        // Check if substring matches starting at position i
        for (int j = 0; j < subStrLen; j++)
        {
            if (str[i + j] != subStr[j])
            {
                match = false;
                break;
            }
        }

        if (match)
        {
            found = true;
            matchIndex = i;
            break;
        }
    }

    // Print the result
    if (found)
    {
        printf("Substring found at index %d.\n", matchIndex);
    }
    else
    {
        printf("Substring not found!\n");
    }

    // Free allocated memory
    free(str);
    free(subStr);
}

int main()
{

    // stringLen();
    // stringCopy();
    stringCompare();
    // countVowConst();
    // stringCountSpace();
    // stringRemoveDuplicates();
    // stringRemoveDuplicatesBetter();
    stringSearchSubStr();

    return 0;
}