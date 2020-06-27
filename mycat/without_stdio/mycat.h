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
 * read given fd to buffer
 * returns 1 if nothing else to read
 * returns 0 else
 */
int read_to_buffer(int fdin, char *buffer, size_t len);

/**
 * write buffer to stdout
 */
void write_buffer(char *buffer, size_t len);

/**
 * read given fd to buffer
 * write buffer to stdout
 * optimised for stdin reading
 */
void read_and_write_stdin(int fdin, char *buffer, size_t len);

/**
 * read from given fd and write in stdout
 * optimised for file reading
 */
void cat_file(int fdin);

/**
 * read from given fd and write in stdout
 * optimised for stdin reading
 */
void cat_stdin(int fdin);

#endif
