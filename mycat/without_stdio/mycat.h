#ifndef MYCAT_H
#define MYCAT_H

/**
 * define fd for visibility
 */
#define CAT_STDIN 0
#define CAT_STDOUT 1
#define CAT_STDERR 2

/**
 * block size for writing / reading
 */
#define CAT_BUFFER_SIZE 8

/**
 * read from given fd and write it in stdout
 */
void cat(int fdin);

#endif
