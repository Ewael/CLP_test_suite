#include "tok_vec.h"

struct tok_vec *tv_init()
{
    // allocate space for struct
    struct tok_vec *tv = malloc(sizeof(struct tok_vec));
    if (tv == NULL)
    {
        errx(EXIT_FAILURE, "tv_init: could not malloc tv");
    }

    // set default values
    tv->capacity = TV_DEFAULT_CAPACITY;
    tv->size = 0;

    // allocate space for tokens array
    tv->data = malloc(tv->capacity * sizeof(struct token));
    if (tv->data == NULL)
    {
        errx(EXIT_FAILURE, "tv_init: could not malloc tv->data");
    }

    return tv;
}

void tv_destroy(struct tok_vec *vec)
{
    for (size_t i = 0; i < vec->size; i++)
    {
        // free malloced arg if token is string or integer
        if (vec->data[i].type == TOK_STRING ||
            vec->data[i].type == TOK_INTEGER)
        {
            free(vec->data[i].arg);
        }
    }
    free(vec->data);
    free(vec);
}

enum token_type tv_peek(struct tok_vec *vec)
{
    return vec->data[0].type;
}

struct token tv_pop_front(struct tok_vec *vec)
{
    // error if empty array
    if (vec->size == 0)
    {
        struct token tok =
        {
            .type = TOK_ERROR,
            .arg = NULL,
        };
        return tok;
    }

    // save first tok and shift left
    struct token tok = vec->data[0];
    for (size_t i = 0; i < vec->size-1; i++)
    {
        vec->data[i] = vec->data[i+1];
    }
    vec->size--;

    return tok;
}

int double_capacity(struct tok_vec *vec)
{
    // double allocated memory space
    vec->data = realloc(vec->data, (vec->capacity*2) * sizeof(struct token));
    if (vec->data == NULL)
    {
        return 0;
    }
    vec->capacity *= 2;
    return 1;
}

int tv_push_back(struct tok_vec *vec, struct token token)
{
    // if array if full then double the capacity
    if (vec->size == vec->capacity)
    {
        if (double_capacity(vec) == 0)
        {
            return 0;
        }
    }

    // push token and update size
    vec->data[vec->size] = token;
    vec->size ++;

    return 1;
}
