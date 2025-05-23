#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    int fd = open("file.md", O_RDONLY); // Open for reading
    if (fd == -1)
    {
        perror("open failed");
        return 1;
    }
    printf("File opened successfully (fd = %d)\n", fd);
    close(fd); // Always close the file!
    return 0;
}