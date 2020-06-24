#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <err.h>
#include <string.h>

#include "mycat.h"

int read_to_buffer(int fdin, char *buffer, size_t len)
{
    int r;
    char *tmp = buffer; // reset at start of buffer
    do
    {
        r = read(fdin, tmp, len);
        if (r == -1)
        {
            err(EXIT_FAILURE, "cat: could not read fdin");
        }

        if (!r)
        {
            return 1;
        }

        len -= r;
        tmp += r;
    } while (len > 0);

    return 0;
}

void write_buffer(char *buffer, size_t len)
{
    int w;
    char *tmp = buffer; // reset at start of buffer
    do
    {
        w = write(CAT_STDOUT, tmp, len);
        if (w == -1)
        {
             err(EXIT_FAILURE, "cat: could not write in stdout");
        }

        if (!w)
        {
            break;
        }

        len -= w;
        tmp += w;
    } while (len > 0);
}

void cat(int fdin)
{
    char buffer[CAT_BUFFER_SIZE] = { 0 };
    int len = CAT_BUFFER_SIZE;

    while (1)
    {
        if (read_to_buffer(fdin, buffer, len));
            break;
        write_buffer(buffer, len);
    }
}

int main(int argc, char **argv)
{
    // read from stdin
    if (argc == 1)
    {
        cat(CAT_STDIN);
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

            cat(fp);

            close(fp);
        }
    }

    return EXIT_SUCCESS;
}
