#include "tok_vec.h"

struct tok_vec *tv_init()
{
    // allocate space for struct
    struct tok_vec *tv = malloc(sizeof(struct tok_vec));
    if (!tv) // En C tu ferais plutot if (!tv), tout le monde connait et comprend
        errx(EXIT_FAILURE, "tv_init: could not malloc tv");

    // Pas besoin d'accolades pour un if a une seule ligne mais c'est tres bien
    // de les avoir aussi :)

    // set default values
    tv->capacity = TV_DEFAULT_CAPACITY;
    tv->size = 0;

    // allocate space for tokens array
    tv->data = malloc(sizeof(tv->capacity)*sizeof(struct token)); // FIXME: Il y a un bug ici

    /**
     * Quand tu ecris sizeof(tv->capacity), ce que tu fais c'est sizeof du type
     * de tv->capacity. Donc c'est faux, ce que tu veux c'est la capacite.
     *
     * La ce que tu as fait c'est pareil qu'ecrire
     *
     * tv->data = malloc(sizeof(size_t) * sizeof(struct token))
     *
     * Ce qui fait 8 * sizeof(struct token). Donc tu n'as pas la capacite a laquelle tu
     * t'attendais.
     *
     * Pour t'en convaincre, compile et run:
     *
     * ```c
#include <stdio.h>

int main(void) {
    size_t capacity = 3;

    printf("%ld\n%ld", sizeof(size_t), sizeof(capacity));
}
     * ```
     *
     */

    if (!tv->data)
        errx(EXIT_FAILURE, "tv_init: could not malloc tv->data");

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
    // Tu peux directement return ici, mais pas de soucis
    return vec->data[0].type;

    // Fais attention, il y a un bug ici. Tu as malloc vec->data, donc tu ne sais pas
    // quelle tete a la memoire (elle est uniinitialized).
    // Si tu as de la chance, il y a des zeros partout et tu vas retourner TOK_ERROR
    // si ton vecteur est vide. Mais si tu n'as pas de chance tu vas retourner un token
    // valide...
    //
    // Soit tu initialize ton vecteur avec calloc (tv->data = calloc(...))
    // soit tu check la taille de vec pour retourner un token
    //
    // C'est la qu'un truc comme ASAN (-fsanitize=address) est tres pratique, car
    // il te l'aurait dit
}

struct token tv_pop_front(struct tok_vec *vec)
{
    // error if empty array
    if (vec->size == 0)
    {
        // Initialization a la C99, c'est un peu plus propre :)
        struct token tok = {
            .type = TOK_ERROR,
            .arg = NULL,
        };

        return tok;
    }

    // save first tok and shift left
    struct token tok = vec->data[0];
    for (size_t i = 0; i < vec->size-1; i++)
        vec->data[i] = vec->data[i+1];

    vec->size--; // Pas d'espace avec l'operateur -- ou ++

    return tok;
}

int double_capacity(struct tok_vec *vec)
{
    // double allocated memory space
    // Met bien des espaces entre tes opeateurs (cap * 2) est mieux que (cap*2)
    vec->data = realloc(vec->data, (vec->capacity * 2) * sizeof(struct token));
    if (vec->data == NULL)
        return 0;

    vec->capacity *= 2;
    return 1;
}

int tv_push_back(struct tok_vec *vec, struct token token)
{
    // if array if full then double the capacity
    if (vec->size == vec->capacity)
        if (!double_capacity(vec))
            return 0;

    // Ca prend un peu moins de place comme ca mais ce que tu as fait est tres bien
    // aussi

    // push token and update size
    vec->data[vec->size] = token;
    vec->size++;

    // Super. Ne fait pas vec->data[vec->size++] = token
    // car c'est tres peu clair et que tu ne peux pas etre *sur* de l'ordre dans lequel
    // ca va s'executer. ++ d'abord? [] d'abord?
    // Donc ce que tu as fait est tres bien

    return 1;
}
