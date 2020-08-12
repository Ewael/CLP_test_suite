#include "parser.h"

struct parser *pr_init(struct lexer *lx)
{
    struct parser *pr = malloc(sizeof(struct parser));
    pr->lexer = lx;
    return pr;
}

void pr_destroy(struct parser *pr)
{
    lx_destroy(pr->lexer);
    free(pr);
}

int pr_parse(struct parser *pr)
{
    struct token *data = pr->lexer->tokens->data;
    int curr_size = pr->lexer->tokens->size;
    int i = 0;
    int size = pr->lexer->tokens->size;
    while (i < pr->lexer->tokens->size)
    {
        if (data[i].type == TOK_SEMICOLON)
        {
            i ++;
            continue;
        }

        else if (data[i].type == TOK_INTEGER ||
                 data[i].type == TOK_STRING)
        {
            return 0;
        }

        else if (data[i].type == TOK_GREET)
        {
            if (i != size-1 && data[i+1].type != TOK_SEMICOLON)
            {
                return 0;
            }
            i ++;
            continue;
        }
    }
    return 1;
}
