#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <err.h>
#include <fcntl.h>

#include "mycat.h"

void cat(char *filename)
{
    int fd = open(filename, 'r');

    struct stat fs;
    if (fstat(fd, &fs) == -1)
    {
        err(EXIT_FAILURE, "cat: could not stat fd in fs");
    }

    char *file_mem_addr = mmap(NULL, fs.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (file_mem_addr == MAP_FAILED)
    {
        err(EXIT_FAILURE, "cat: could not mmap");
    }

    for (int i = 0; i < fs.st_size; i++)
    {
        printf("%c", file_mem_addr[i]);
    }

    if (munmap(file_mem_addr, fs.st_size) == -1)
    {
        err(EXIT_FAILURE, "cat: could not unmap fs");
    }

    close(fd);
}

int main(int argc, char **argv)
{
    // usage if no file specified or -h || --help
    if (argc == 1 || !strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))
    {
        write(CAT_STDOUT, "Usage: ./mycat filename\n", 24);
    }

    // read specified file(s)
    else
    {
        for (int i = 1; i < argc; i++)
        {
            cat(argv[i]);
        }
    }

    return EXIT_SUCCESS;
}
