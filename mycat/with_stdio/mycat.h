#ifndef MYCAT_H
#define MYCAT_H

/**
 * block size for writing / reading
 */
#define CAT_BUFFER_SIZE 4096

/**
 * read file and write it in stdout
 */
void cat(FILE *fp);

#endif
