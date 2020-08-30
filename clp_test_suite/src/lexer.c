#include <string.h>
#include <ctype.h>
#include <stdio.h>

#include "lexer.h"

#define BUFSIZE 256

struct lexer *lx_init()
{
    struct lexer *lx = malloc(sizeof(struct lexer));
    lx->tokens = tv_init();
    return lx;
}

void lx_destroy(struct lexer *lx)
{
    tv_destroy(lx->tokens);
    free(lx);
}

int is_number(char *string)
{
    int len = strlen(string);
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

    if (is_number(word))
    {
        tok.type = TOK_INTEGER;
        int *x = malloc(sizeof(int));
        *x = atoi(word);
        tok.arg = x;
        return tok;
    }

    int len = strlen(word);
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
        tok.type = TOK_STRING;
        tok.arg = malloc(sizeof(char)*len);
        strncpy(tok.arg, word, len);
    }

    return tok;
}

int lx_fill(struct lexer *lx, FILE *input)
{
    char buf[BUFSIZE];
    char *word;
    int err = 0;
    while (fgets(buf, BUFSIZE, input) != NULL)
    {
        word = strtok(buf, " ");
        while (word != NULL)
        {
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
