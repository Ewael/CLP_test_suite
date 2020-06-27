#ifndef TOKENS_H
#define TOKENS_H

/**
 * @brief The different types in our syntax
 */
enum token_type
{
    TOK_ERROR = 0,
    TOK_SEMICOLON,
    TOK_INTEGER,
    TOK_STRING,
    TOK_GREET,
    TOK_EXIT,
    TOK_PRINT,
    TOK_ADD,
};

/**
 * @brief Base token struct, composed of the type of token, as well as an
 * additional_argument when necessary. (Strings, Integers, etc)
 *
 * The additional argument is allocated on the heap via malloc() and can be free()'d
 */
struct token
{
    enum token_type type;
    void* arg;
};

#endif // TOKENS_H
