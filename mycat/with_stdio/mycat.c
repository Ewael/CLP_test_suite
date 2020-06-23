#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mycat.h"

void cat(FILE *fp)
{
    char buffer[CAT_BUFFER_SIZE] = { 0 };
    while (fgets(buffer, CAT_BUFFER_SIZE, fp) != NULL)
    {
        printf("%s", buffer);
    }
}

int main(int argc, char **argv)
{
    // read from stdin
    if (argc == 1)
    {
        cat(stdin);
    }

    // usage if -h or --help
    else if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))
    {
        printf("Usage: ./mycat filename\n");
    }

    // read specified file(s)
    else
    {
        for (int i = 1; i < argc; i++)
        {
            FILE *fp = fopen(argv[i], "r");
            if (!fp)
            {
                perror("main: could not open file");
                exit(EXIT_FAILURE);
            }

            cat(fp);

            fclose(fp);
        }
    }

    return EXIT_SUCCESS;
}
