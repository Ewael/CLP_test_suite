#include "tok_vec.h"

struct tok_vec *tv_init()
{
    struct tok_vec *tv = malloc(sizeof(struct tok_vec));
    tv->capacity = TV_DEFAULT_CAPACITY;
    tv->size = 0;
    tv->data = malloc(sizeof(tv->capacity)*sizeof(struct token));
    return tv;
}

void tv_destroy(struct tok_vec *vec)
{
    for (size_t i = 0; i < vec->size; i++)
    {
        if (vec->data[i].type == TOK_STRING)
        {
            free(vec->data[i].arg);
        }
    }
    free(vec->data);
    free(vec);
}

enum token_type tv_peek(struct tok_vec *vec)
{
    enum token_type tt = vec->data[0].type;
    return tt;
}

struct token tv_pop_front(struct tok_vec *vec)
{
    if (vec->size == 0)
    {
        struct token tok;
        tok.type = TOK_ERROR;
        tok.arg = NULL;
        return tok;
    }

    struct token tok = vec->data[0];
    for (size_t i = 0; i < vec->size-1; i++)
    {
        vec->data[i] = vec->data[i+1];
    }
    vec->size --;
    return tok;
}

int double_capacity(struct tok_vec *vec)
{
    vec->data = realloc(vec->data, (vec->capacity*2)*sizeof(struct token));
    if (vec->data == NULL)
    {
        return 0;
    }
    vec->capacity *= 2;
    return 1;
}

int tv_push_back(struct tok_vec *vec, struct token token)
{
    if (vec->size == vec->capacity)
    {
        if (double_capacity(vec) == 0)
        {
            return 0;
        }
    }

    vec->data[vec->size] = token;
    vec->size ++;
    return 1;
}
