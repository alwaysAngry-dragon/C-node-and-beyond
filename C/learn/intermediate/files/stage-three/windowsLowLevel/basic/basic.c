#include <stdio.h>
#include <windows.h> // Main Windows API header (includes functions like CreateFile, ReadFile, his header defines all Windows API functions, macros, and data types.)
#include <direct.h>  // For _getcwd

/*
        Every HANDLE returned by CreateFile points to a kernel-managed file object that contains:
        The offset is tracked by the kernel

        Component	            Description
        Current Offset	        Tracks read/write position
        File Size	            Maximum accessible position
        Sharing Mode	        Controls concurrent access
        Flags	                FILE_FLAG_OVERLAPPED, etc.

*/

int createLowLevelFile()
{

    /*
        CreateFileA is the ANSI version of the Windows API function
        for opening/creating files, devices, pipes, and other I/O resources.

        CreateFile returns a valid value of invalid value it it faile

        HANDLE CreateFileA(
                    LPCSTR                lpFileName,
                    DWORD                 dwDesiredAccess,
                    DWORD                 dwShareMode,
                    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
                    DWORD                 dwCreationDisposition,
                    DWORD                 dwFlagsAndAttributes,
                    HANDLE                hTemplateFile
                    );


        A HANDLE is an opaque pointer type that represents a system resource.
            - it is unique identifier assigned by the Windows kernel
            - Handle points to kernel object metadata if CreateFile is successful

            Opaque:
                    Only comparable.
                    You cannot dereference or interpret it directly.
                    You can't inspect its internals
                    You can only use it with Windows API functions


            typedef void *HANDLE;  // Essentially a pointer


            Common HANDLE Types:
                        HANDLE hFile;       // File handle
                        HANDLE hProcess;    // Process handle
                        HANDLE hThread;     // Thread handle
                        HANDLE hMutex;      // Mutex handle

            DWORD is a fundamental Win32 data type:

                typedef unsigned long DWORD;  // 32-bit unsigned integer

            LPCSTR
                Type: const char*

            LPSECURITY_ATTRIBUTES
                Type: Pointer to SECURITY_ATTRIBUTES struct


    */

    printf("The current working directory: %s \n", _getcwd(NULL, 0));
    HANDLE hFile = CreateFileA(
        "file.md",             // File path
        GENERIC_READ,          // Desired access (read/write)
        FILE_SHARE_READ,       // Share mode (allow other processes to read)
        NULL,                  // Security attributes (default)
        OPEN_ALWAYS,           // Creation disposition (create new if not exists)
        FILE_ATTRIBUTE_NORMAL, // File flags
        NULL                   // Template file (not used)
    );

    //   CreateFile returns a valid value of invalid value it it fails
    if (hFile == INVALID_HANDLE_VALUE)
    {
        DWORD error = GetLastError();
        printf("Failed to open file. Error: %lu\n", error);
        return 1;
    }

    printf("Size of HANDLE %zu bytes.\n", sizeof(HANDLE));
    printf("Value of hFile is %p", hFile);

    CloseHandle(hFile);
    return 0;
}

HANDLE openWriteMode()
{
    HANDLE hFile = CreateFileA(
        "file.md",             // File path
        GENERIC_WRITE,         // Write-only access
        FILE_SHARE_READ,       // Allow other readers
        NULL,                  // Default security
        OPEN_EXISTING,         // Only open existing files
        FILE_ATTRIBUTE_NORMAL, // Normal file
        NULL                   // No template
    );

    if (hFile == INVALID_HANDLE_VALUE)
    {
        DWORD error = GetLastError();
        if (error == ERROR_FILE_NOT_FOUND)
        {
            printf("Error: File doesn't exist\n");
        }
        else
        {
            printf("Error opening file: %lu\n", error);
        }
        return NULL; // Or handle error appropriately
    }

    return hFile;
}

HANDLE openReadMode()
{
    HANDLE hFile = CreateFileA(
        "file.md",             // File path
        GENERIC_READ,          // Read-only access
        FILE_SHARE_READ,       // Allow other readers
        NULL,                  // Default security
        OPEN_EXISTING,         // Only open existing files
        FILE_ATTRIBUTE_NORMAL, // Normal file
        NULL                   // No template
    );

    if (hFile == INVALID_HANDLE_VALUE)
    {
        DWORD error = GetLastError();
        if (error == ERROR_FILE_NOT_FOUND)
        {
            printf("Error: File doesn't exist\n");
        }
        else
        {
            printf("Error opening file: %lu\n", error);
        }
        return NULL; // Or handle error appropriately
    }

    return hFile;
}

void readFile(HANDLE hFile)
{

    /*
        The ReadFile function is the core Windows API for reading data from files,
        devices, pipes, or other I/O sources.

        BOOL ReadFile(
            HANDLE       hFile,                // Handle to file/device
            LPVOID       lpBuffer,             // Buffer to store read data Type: void* (pointer to buffer)
            DWORD        nNumberOfBytesToRead, // Bytes to read
            LPDWORD      lpNumberOfBytesRead,  // Actual bytes read (output)
            LPOVERLAPPED lpOverlapped          // For asynchronous I/O (NULL for sync)
        );

        EOF can be detected if bytesRead == 0;

        Return type of ReadFile:

                TRUE	Success (even if 0 bytes read at EOF)
                FALSE	Failure (check GetLastError())


        No Buffering: Data goes DIRECTLY from disk → destination

    */

    char buffer;
    DWORD bytesRead;

    // read one byte from the  file
    WINBOOL result = ReadFile(hFile, &buffer, 1, &bytesRead, NULL);

    if (!result)
    {
        // error has occured
        DWORD error = GetLastError();
        {
            if (error != ERROR_HANDLE_EOF)
            { // EOF isn't a real error
                printf("Read error: %lu\n", error);
            }
        }
    }

    printf("\n Bytes read %lu, byte character is %c \n", bytesRead, buffer);
}

void writeToFile(HANDLE hFile)
{
    char buffer = 'B';
    DWORD bytesWritten;

    int result = WriteFile(hFile, &buffer, 1, &bytesWritten, NULL);

    if (!result)
    {
        // error has occured
        DWORD error = GetLastError();
        {
            if (error != ERROR_HANDLE_EOF)
            { // EOF isn't a real error
                printf("Write error: %lu\n", error);
            }
        }
    }

    printf("Number of bytes written %lu \n", bytesWritten);
}

int main()
{
    HANDLE file;

    // createLowLevelFile();

    // file = openReadMode();

    // if (file == NULL)
    // {
    //     perror("Error creating file.");
    //     exit(1);
    // }
    // readFile(file);
    // CloseHandle(file);

    file = openWriteMode();

    if (file == NULL)
    {
        printf("Error opening file in write mode.\n");
        return 1;
    }

    writeToFile(file);

    CloseHandle(file);

    return 0;
}