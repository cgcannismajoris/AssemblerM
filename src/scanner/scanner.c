/* scanner.c
 * Implementação do SCANNER.
 */
#include "scanner.h"


TOKENS *scanner_scan(char *sentence)
{
    TOKENS *toks;
    char *str, *ptr_str;
    char *pch;
    char delim[] = SCANNER_DELIMS;
    int cont_tokens = 0, i = 0;

    if ((str = (char *)malloc(strlen(sentence) * sizeof(char) + 1)) == NULL)
        return SCANNER_ERROR;

    /* Copio a referência inicial de str. */
    ptr_str = str;

    /* str <- sentence */
    strcpy(str, sentence);

    /* Retiram-se as palavras a serem desprezadas. */
    pch = strstr(str, SCANNER_IGNOREFACASTR);

    /* Se pch == NULL, então a substring não foi encontrada. */
    if (pch != NULL)
        memset(pch, SCANNER_SPCLS, strlen(SCANNER_IGNOREFACASTR));

    pch = strstr(str, SCANNER_IGNOREVAPARASTR);

    if (pch != NULL)
        memset(pch, SCANNER_SPCLS, strlen(SCANNER_IGNOREVAPARASTR));

    /* Contar os tokens. */
    pch = strtok(str, delim);

    while (pch != NULL)
    {
        pch = strtok(NULL, delim);
        cont_tokens++;
    }

    /* Alocar memória para toks. */
    if ((toks = token_new(cont_tokens)) == TOKENS_EALLOC)
    {
        free(str);
        return SCANNER_ERROR;
    }

    /* Guardar os tokens. */
    /* Inserir os tokens da string str na estrutura toks. */
    while (cont_tokens)
    {
        token_addToken(toks, str);

        str += strlen(str);
        while(*(++str) == SCANNER_SPCLS);

        cont_tokens--;
    }

    /* Chegado aqui, os tokens foram inseridos com sucesso. */

    /* Libere a memória de str. */
    free(ptr_str);

    return toks;
}
