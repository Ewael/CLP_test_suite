#ifndef MYCAT_H
#define MYCAT_H

/**
 * block size for writing / reading
 */
#define CAT_BUFFER_SIZE 4096

/**
 * define fd for visibility
 */
#define CAT_STDIN 0
#define CAT_STDOUT 1
#define CAT_STDERR 2

/**
 * read file and write it in stdout
 */
void cat(char *filename);

#endif
