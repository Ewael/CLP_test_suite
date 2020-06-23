#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 4096
#define STDIN 0
#define STDOUT 1

int main(int argc, char **argv)
{
    if (argc > 2)
    {
        printf("Usage: ./mycat filename\n");
        return EXIT_SUCCESS;
    }

    if (argc == 1)
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
                }
                offset += w;
                r -= w;
            }
        }
    }

    else if (argc == 2)
    {
        FILE *fp;
        fp = fopen(argv[1], "r");
        if (fp == NULL)
        {
            perror("main: could not open file");
            exit(EXIT_FAILURE);
        }

        char buffer[BUFFER_SIZE] = { 0 };
        while (fgets(buffer, BUFFER_SIZE, fp) != NULL)
        {
            printf(buffer);
        }

        fclose(fp);
        return EXIT_SUCCESS;
    }
}
