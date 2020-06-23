#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <err.h>
#include <string.h>

#include "mycat.h"

void cat(int fdin)
{
    char buffer[CAT_BUFFER_SIZE] = { 0 };
    int r;

    while (1)
    {
        while ((r = read(fdin, buffer, CAT_BUFFER_SIZE)) > 0)
        {
            if (write(CAT_STDOUT, buffer, r) != r)
            {
                errx(EXIT_FAILURE, "cat: could not write buf to stdout");
            }
        }

        if (r == -1)
        {
            errx(EXIT_FAILURE, "cat: could not read fdin");
        }

        else
            break;
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
            if (!fp)
            {
                errx(EXIT_FAILURE, "main: could not open file");
            }

            cat(fp);

            close(fp);
        }
    }

    return EXIT_SUCCESS;
}
