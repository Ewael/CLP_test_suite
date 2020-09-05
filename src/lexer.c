#include <string.h>
#include <ctype.h>
#include <stdio.h>

#include "lexer.h"

#define BUFSIZE 256

struct lexer *lx_init()
{
    // allocate space for struct
    struct lexer *lx = malloc(sizeof(struct lexer));
    if (lx == NULL)
    {
        errx(EXIT_FAILURE, "lx_init: could not malloc lx");
    }

    // init tokens struct
    lx->tokens = tv_init();

    return lx;
}

void lx_destroy(struct lexer *lx)
{
    tv_destroy(lx->tokens);
    free(lx);
}

// return 1 if string is a number, 0 otherwise
int is_number(char *string, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (!isdigit(string[i]))
        {
            return 0;
        }
    }
    return 1;
}

struct token word_to_tok(char *word)
{
    struct token tok;
    int len = strlen(word);

    // if number then set arg with the int
    if (is_number(word, len))
    {
        tok.type = TOK_INTEGER;
        int *x = malloc(sizeof(int));
        if (x == NULL)
        {
             errx(EXIT_FAILURE, "word_to_tok: could not malloc x");
        }
        *x = atoi(word);
        tok.arg = x;
        return tok;
    }

    if (!strncmp(word, ";", len))
        tok.type = TOK_SEMICOLON;
    else if (!strncmp(word, "greet", len))
        tok.type = TOK_GREET;
    else if (!strncmp(word, "exit", len))
        tok.type = TOK_EXIT;
    else if (!strncmp(word, "print", len))
    {
        tok.type = TOK_PRINT;
        tok.arg = NULL;
    }
    else if (!strncmp(word, "add", len))
    {
        tok.type = TOK_ADD;
        tok.arg = NULL;
    }
    else
    {
        // if string then set arg with the string
        tok.type = TOK_STRING;
        tok.arg = malloc(sizeof(char)*len);
        if (tok.arg == NULL)
        {
             errx(EXIT_FAILURE, "work_to_tok: could not malloc tok.arg");
        }
        strncpy(tok.arg, word, len);
    }

    return tok;
}

int lx_fill(struct lexer *lx, FILE *input)
{
    char buf[BUFSIZE];
    char *word;
    int err = 0;

    // read input and write it to buf
    while (fgets(buf, BUFSIZE, input) != NULL)
    {
        word = strtok(buf, " ");
        while (word != NULL)
        {
            // get token and insert it to lexer
            struct token tok = word_to_tok(word);
            err = tv_push_back(lx->tokens, tok);
            word = strtok(NULL, " ");
        }
    }

    return err;
}

struct token lx_pop(struct lexer *lx)
{
    struct token tok = tv_pop_front(lx->tokens);
    return tok;
}
