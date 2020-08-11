#include "tok_vec.h"

struct tok_vec *tv_init()
{
    struct tok_vec *tv = malloc(sizeof(struct tok_vec));
    tv->capacity = TV_DEFAULT_CAPACITY;
    tv->size = 0;
    return tv;
}

void tv_destroy(struct tok_vec *vec)
{
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
    struct token tok = vec->data[0];
    for (size_t i = 0; i < vec->size-1; i++)
    {
        vec->data[i] = vec->data[i+1];
    }
    vec->size --;
    return tok;
}

int tv_push_back(struct tok_vec *vec, struct token token)
{
    int error=0;
    return error;
}
