#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void clearInputBuffer()
{
    while (getchar() != '\n')
    {
    }
    return;
}

void checkEvenOdd()
{
    int x;
    bool exit = false;

    while (exit == false)
    {
        printf("Enter a number: ");
        scanf("%d", &x);
        clearInputBuffer();

        if (x % 2 == 0)
        {
            printf("%d is an even number.\n", x);
        }
        else
        {
            printf("%d is an odd number.\n", x);
        }
        printf("Do you want to continue? (y/n): ");
        exit = (getchar() == 'n');
        clearInputBuffer();

        printf("%d \n", exit);
    }
}

void largestThreeNumbers()
{
    int x, y, z, largest;
    printf("Enter three numbers: ");
    scanf("%d %d %d", &x, &y, &z);
    clearInputBuffer();
    largest = (x > y) ? ((x > z) ? x : z) : ((y > z) ? y : z);

    printf("The largest number is: %d\n", largest);
}

void gradeCalculator()
{
    float grade;
    printf("Enter your grade: ");
    scanf("%f", &grade);
    clearInputBuffer();

    if (grade >= 90)
    {
        printf("Your grade is A.\n");
        return;
    }
    else if (grade >= 80)
    {
        printf("Your grade is B.\n");
        return;
    }
    else if (grade >= 70)
    {
        printf("Your grade is C.\n");
        return;
    }
    else
    {
        printf("Your grade is F.\n");
        return;
    }
}

void vowelOrConsonant()
{
    char c;
    printf("Enter a character: ");
    scanf("%c", &c);
    clearInputBuffer();

    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
        c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
    {
        printf("%c is a vowel.\n", c);
    }
    else
    {
        printf("%c is a consonant.\n", c);
    }
}

void readStr()
{
    char name[5];
    printf("Enter your name: ");
    // fgets(name, sizeof(name), stdin);
    scanf("%s", name);
    printf("Your name is: %s\n", name);
}

void multiPlicationTable()
{
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    clearInputBuffer();

    for (int i = 1; i <= 10; i++)
    {
        printf("%d x %d = %d\n", num, i, num * i);
    }
}

void factorialNormal()
{
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    clearInputBuffer();

    unsigned long long fact = 1;

    if (num < 0)
    {
        printf("Invalid input. Please enter a positive integer.\n");
        return;
    }
    for (int i = num; i >= 1; i--)
    {
        fact = fact * i;
    }
    printf("Factorial of %llu is: %llu\n", num, fact);
}

void checkPrime()
{
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    clearInputBuffer();

    // a number is prime if it is greater than 1 and has no divisors other than 1 and itself

    if (num <= 1)
    {
        printf("%d is not a prime number.\n", num);
        return;
    }

    for (int i = 2; i < num; i++)
    {
        if (num % i == 0)
        {
            printf("%d is not a prime number.\n", num);
            return;
        }
    }

    printf("%d is a prime number.\n", num);
}

void fibonacciSequence()
{
    // 0 1 1 2 3 5 8 13 21 34...

    int num;
    printf("Enter the number of terms (greater than 2): ");
    scanf("%d", &num);
    clearInputBuffer();

    int first = 0, second = 1, nextTerm;

    if (num <= 3)
    {
        printf("Enter a number greater than 2 \n");
        return;
    }

    printf("Fibonacci Sequence: %d, %d, ", first, second);
    do
    {
        nextTerm = first + second;
        printf("%d, ", nextTerm);
        first = second;
        second = nextTerm;
        num--;

    } while (num > 2);
}

void sumDigits()
{
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    clearInputBuffer();

    int sum = 0;
    while (num > 0)
    {
        sum = sum + num % 10;
        num = num / 10;
    }

    printf("Sum of digits: %d\n", sum);
}

int reverseNumber()
{
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    clearInputBuffer();

    if (num < 0)
    {
        printf("Reversing a negative number is not possible.\n");
        return 1;
    }

    int original = num;
    int reversed = 0;
    int digit = 0;
    while (num > 0)
    {
        digit = num % 10;
        reversed = reversed * 10 + digit;
        num = num / 10;
    }

    printf("Reverse of %d = %d\n", original, reversed);
    return reversed;
}

int factorialRecursive(int n)
{
    if (n <= 0 || n == 1)
    {
        return 1;
    }
    return n * factorialRecursive(n - 1);
}

int checkGCDHelper(int a, int b)
{
    if (a % b == 0)
    {
        return b;
    }
    return checkGCDHelper(b, a % b);
}

void checkGCD(int a, int b)
{

    int gcd;
    if (a < b)
    {
        gcd = checkGCDHelper(b, a);
    }
    else
    {

        gcd = checkGCDHelper(a, b);
    }

    printf("GCD of %d and %d is: %d\n", a, b, gcd);
}

void arraySum()
{
    int size;
    printf("Enter the size of the array: ");
    scanf("%d", &size);
    clearInputBuffer();

    int arr[size];
    int sum = 0;

    for (int i = 0; i < size; i++)
    {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &arr[i]);
        sum += arr[i];
        clearInputBuffer();
    }

    printf("Sum of all elements in the array is: %d\n", sum);
}

void arrayLargest()
{
    int size;
    printf("Enter the size of the array: ");
    scanf("%d", &size);
    clearInputBuffer();

    int arr[size];
    int largets = 0;

    for (int i = 0; i < size; i++)
    {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &arr[i]);
        if (arr[i] > largets)
        {
            largets = arr[i];
        }
        clearInputBuffer();
    }

    printf("Size of array: %d\n", sizeof(arr));
    printf("Largest element is : %d\n", largets);
}

void stringLength()
{
    char str[100];
    printf("Enter a string: ");

    fgets(str, sizeof(str), stdin);
    // Check if the input exceeded the buffer size
    if (str[strlen(str) - 1] != '\n')
    {
        printf("Input too long! Clearing buffer...\n");
        clearInputBuffer();
    }

    int len = 0;
    for (int i = 0; *(str + i) != '\n'; i++)
    {
        len++;
    }

    printf("length of the string is: %d\n", strlen(str));
    printf("length of the string native: %d\n", len);
}

void stringReverse()
{
    char str[100];

    printf("Enter a string: ");

    fgets(str, sizeof(str), stdin);
    // Check if the input exceeded the buffer size
    if (str[strlen(str) - 1] != '\n')
    {
        printf("Input too long! Clearing buffer...\n");
        clearInputBuffer();
    }

    int len = 0;
    for (int i = 0; *(str + i) != '\n'; i++)
    {
        len++;
    }

    for (int i = 0; i < len / 2; i++)
    {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }

    printf("Reversed string: %s\n", str);
}

int main()
{
    // checkEvenOdd();
    // largestThreeNumbers();
    // gradeCalculator();
    // vowelOrConsonant();
    // factorialNormal();
    // checkPrime();
    // fibonacciSequence();
    // sumDigits();
    // reverseNumber();
    // checkGCD(23, 10);
    // arraySum();
    // arrayLargest();
    // stringLength();
    stringReverse();
    printf("Program exiting.\n");

    return 0;
}
