#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "mycat.h"

#define BUFFER_SIZE 4096
#define STDIN 0
#define STDOUT 1

/*
 * read stdin and write it back in stdout
 */
void cat_stdin(void)
{
    char buffer[BUFFER_SIZE] = { 0 };
    int r;
    while (1)
    {
        r = read(STDIN, buffer, BUFFER_SIZE);

        int w;
        size_t offset = 0;
        while (r > 0)
        {
            w = write(STDOUT, buffer + offset, r);
            if (w == -1)
            {
                perror("main: error when writing in stdout");
                exit(EXIT_FAILURE);
            }
            offset += w;
            r -= w;
        }
    }
}

/*
 * read file and write it in stdout
 */
void cat_file(char *filename)
{
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        perror("cat_file: could not open file");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE] = { 0 };
    while (fgets(buffer, BUFFER_SIZE, fp) != NULL)
    {
        printf(buffer);
    }

    fclose(fp);
}

int main(int argc, char **argv)
{
    // read from stdin
    if (argc == 1)
    {
        cat_stdin();
    }

    // usage if -h or --help
    else if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))
    {
        printf("Usage: ./mycat filename\n");
    }

    // read specified file(s)
    else
    {
        for (int i=1; i < argc; i++)
        {
            cat_file(argv[i]);
        }
    }

    return EXIT_SUCCESS;
}
