#ifndef MYCAT_H
#define MYCAT_H

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
