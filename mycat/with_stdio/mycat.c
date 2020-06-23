#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: ./mycat filename\n");
        return EXIT_SUCCESS;
    }

    FILE *fp;
    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        perror("main: could not open file");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, fp) != NULL)
    {
        printf(buffer);
    }

    fclose(fp);
    return EXIT_SUCCESS;
}
