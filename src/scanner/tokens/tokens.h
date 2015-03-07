/* tokens.h
 * TAD TOKENS (Conjunto de TOKENS).
 */
#ifndef TOKENS_HEADER
#define TOKENS_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define TOKENS_QTDMAX   256

typedef struct _tokens
{
    char **  tokens;
    uint8_t  qtdUsed;
} TOKENS;


TOKENS *    token_new(uint8_t qtd);
void        token_free(TOKENS *token);

uint8_t     token_getQtd(TOKENS *token);
char *      token_getToken(TOKENS *token, uint8_t pos);
void        token_setToken(TOKENS *token, char *t, uint8_t pos);


#endif /* TOKENS_HEADER */
