#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

/**
 * @brief Basic parser structure
 */
struct parser {
    struct lexer *lexer;
};

/**
 * @brief Create a new parser
 *
 * @return NULL on error, the parser otherwise
 */
struct parser *pr_init(struct lexer *lx);

/**
 * @brief Free the memory associated with a parser
 */
void pr_destroy(struct parser *pr);

/**
 * @brief Parse the lexer input
 *
 * @return 0 on error, 1 otherwise
 */
int pr_parse(struct parser *pr);

#endif // PARSER_H
