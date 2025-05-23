#include <stdio.h>
#include <io.h> // _fileno, _chsize_s
#include <errno.h>

void resizeFile(FILE *fptr, long newSize)
{
    int fd = _fileno(fptr);
    if (fd == -1)
    {
        printf("Error getting file descriptor.\n");
        return;
    }

    int result = _chsize_s(fd, newSize);
    if (result != 0)
    {
        perror("Error resizing file");
        return;
    }

    printf("File resized successfully to %ld bytes.\n", newSize);
}

int main()
{
    // lets assume the original file is 10bytes
    // Original 10 bytes: untouched after resize
    // New 4 bytes: filled with zeros i.e '\o' in ascii
    FILE *fptr = fopen("data.bin", "ab+");
    if (!fptr)
    {
        perror("Failed to open file");
        return 1;
    }

    // Resize file from current size to 14 bytes
    resizeFile(fptr, 14);

    fclose(fptr);
    return 0;
}