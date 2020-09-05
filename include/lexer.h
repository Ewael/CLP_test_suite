#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>

#include "tok_vec.h"

/**
 * @brief The lexer structure
 */
struct lexer
{
    struct tok_vec *tokens;
};

/**
 * @brief Create a lexer
 *
 * @return NULL on error, the created lexer otherwise
 */
struct lexer *lx_init();

/**
 * @brief Destroy a lexer and its components
 */
void lx_destroy(struct lexer *lx);

/**
 * @brief Lex a FILE input
 *
 * @return 0 on error, 1 otherwise
 */
int lx_fill(struct lexer *lx, FILE *input);

/**
 * @brief Return the next token to parse
 *
 * @return TOK_ERROR on error, the token otherwise
 */
struct token lx_pop(struct lexer *lx);

#endif // LEXER_H
