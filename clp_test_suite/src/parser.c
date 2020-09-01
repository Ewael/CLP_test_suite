#include "parser.h"

struct parser *pr_init(struct lexer *lx)
{
    // allocate space for struct
    struct parser *pr = malloc(sizeof(struct parser));
    if (!pr)
        errx(EXIT_FAILURE, "pr_init: could not malloc pr");

    pr->lexer = lx;
    return pr;
}

void pr_destroy(struct parser *pr)
{
    // Pareil que dans lexer.c, ca peut SEGV ici. Il faut checker pour NULL
    lx_destroy(pr->lexer);
    free(pr);
}

int pr_parse(struct parser *pr)
{
    struct token *data = pr->lexer->tokens->data;
    int i = 0;
    int size = pr->lexer->tokens->size;

    // iterate on the data array and check token type
    while (i < pr->lexer->tokens->size)
    {
        // FIXME: Ca fait baucoup de if else. Fait plutot une switch case avec du
        // fallthrough

        // if ';' then iterate on next token
        if (data[i].type == TOK_SEMICOLON)
        {
            i++;
            continue;
        }

        // if number or string then error
        else if (data[i].type == TOK_INTEGER ||
                 data[i].type == TOK_STRING)
        {
            return 0;
        }

        // if greet or exit then
        // error if not last element AND not ';' behind
        else if (data[i].type == TOK_GREET || data[i].type == TOK_EXIT)
        {
            if (i != size-1)
            {
                if (data[i + 1].type != TOK_SEMICOLON)
                {
                    return 0;
                    }
            }
            i++;
            continue;
        }

        // if print then error if nothing behind
        else if (data[i].type == TOK_PRINT)
        {
            if (i == size - 1)
            {
                return 0;
            }
            else if (data[i + 1].type != TOK_STRING)
            {
                return 0;
            }
            i += 2;
            continue;
        }

        // if add then error if not 2 elements behind
        else if (data[i].type == TOK_ADD)
        {
            if (i >= size - 2)
            {
                return 0;
            }
            else if (data[i + 1].type != TOK_INTEGER ||
                     data[i + 2].type != TOK_INTEGER)
            {
                return 0;
            }
            i += 3;
            continue;
        }

        // should be an impossible case
        else
            return 0;
    }

    return 1;
}
