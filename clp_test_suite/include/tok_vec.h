#ifndef TOK_VEC_H
#define TOK_VEC_H

#include <stdlib.h>

#include "token.h"

/**
 * @brief Default capacity of the vector
 */
#define TV_DEFAULT_CAPACITY 256

/**
 * @brief Vector of tokens that automatically resizes
 */
struct tok_vec
{
    size_t capacity;
    size_t size;

    struct token *data;
};

/**
 * @brief Create a new vector of tokens
 */
struct tok_vec *tv_init();

/**
 * @brief Destroy a vector of tokens
 */
void tv_destroy(struct tok_vec *vec);

/**
 * @brief Look at the first element of the vector
 */
enum token_type tv_peek(struct tok_vec *vec);

/**
 * @brief Remove the first element from the vector
 */
struct token tv_pop_front(struct tok_vec *vec);

/**
 * @brief Insert a new token in the vector
 *
 * @return 0 on error, 1 otherwise
 */
int tv_push_back(struct tok_vec *vec, struct token token);

#endif // TOK_VEC_H
