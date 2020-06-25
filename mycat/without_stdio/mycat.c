#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <err.h>
#include <string.h>

#include "mycat.h"

int read_to_buffer(int fdin, char *buffer, size_t len)
{
    int r;
    char *rptr = buffer; // read ptr to move in buffer
    do
    {
        r = read(fdin, rptr, len);
        if (r == -1)
        {
            err(EXIT_FAILURE, "cat: could not read fdin");
        }

        if (!r)
        {
            return 1;
        }

        len -= r;
        rptr += r;
    } while (len > 0);

    return 0;
}

void write_buffer(char *buffer, size_t len)
{
    int w;
    char *wptr = buffer; // write ptr to move in buffer
    do
    {
        w = write(CAT_STDOUT, wptr, len);
        if (w == -1)
        {
             err(EXIT_FAILURE, "cat: could not write in stdout");
        }

        if (!w)
        {
            break;
        }

        len -= w;
        wptr += w;
    } while (len > 0);
}

void read_and_write_stdin(int fdin, char *buffer, size_t len)
{
    int r;
    char *rptr = buffer; // read ptr to move in buffer
    do
    {
        r = read(fdin, rptr, len);
        if (r == -1)
        {
            err(EXIT_FAILURE, "cat: could not read fdin");
        }

        write_buffer(rptr, r);

        len -= r;
        rptr += r;
    } while (len > 0);
}

void cat_file(int fdin)
{
    int status;
    while (1)
    {
        char buffer[CAT_BUFFER_SIZE] = { 0 };
        status = read_to_buffer(fdin, buffer, CAT_BUFFER_SIZE);
        write_buffer(buffer, CAT_BUFFER_SIZE);
        if (status)
            break;
    }
}

void cat_stdin(int fdin)
{
    while (1)
    {
        char buffer[CAT_BUFFER_SIZE] = { 0 };
        read_and_write_stdin(fdin, buffer, CAT_BUFFER_SIZE);
    }
}

int main(int argc, char **argv)
{
    // read from stdin
    if (argc == 1)
    {
        cat_stdin(CAT_STDIN);
    }

    // usage if -h or --help
    else if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))
    {
        write(CAT_STDOUT, "Usage: ./mycat filename\n", 24);
    }

    // read specified file(s)
    else
    {
        for (int i = 1; i < argc; i++)
        {
            int fp = open(argv[i], O_RDONLY);
            if (fp == -1)
            {
                err(EXIT_FAILURE, "main: could not open file");
            }

            cat_file(fp);

            close(fp);
        }
    }

    return EXIT_SUCCESS;
}
