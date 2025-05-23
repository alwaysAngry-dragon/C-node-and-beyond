#include <stdio.h>
#include <time.h>

int main()
{
    time_t now;
    struct tm *local_time;

    now = time(NULL);
    if (now == -1)
    {
        printf("Error getting current time.\n");
        return 1;
    }

    local_time = localtime(&now);
    if (local_time == NULL)
    {
        printf("Error converting time.\n");
        return 1;
    }

    printf("Current date and time: %s", asctime(local_time));

    return 0;
}