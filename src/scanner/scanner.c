/*
 * Nome do Arquivo:  scanner.c
 *       Descricao:  Implementação do método de geração de tokens do assembler.
 * 
 * Scanner for AssemblerM.
 * Copyright (C) 2015  Cristian Costa Mello and Gustavo Freitas de Amorim
 *
 * This is part of AssemblerM
 * AssemblerM is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * AssemblerM is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "scanner.h"
#include <assert.h>
// LISTA DE PALAVRAS PARA IGNORAR
// SEPARADOR DOS TOKENS
TOKENS *scanner_scan(const char *sentence, char **ignoreList, char *delims,
                     uint64_t n_ignore)
{
    TOKENS *toks;
    char *str, *ptr_str;
    char *pch;
    int cont_tokens = 0;
    uint64_t i = 0;

	if ((str = (char *)malloc((strlen(sentence) * sizeof(char)) + 1)) == NULL)
        return SCANNER_ERROR;

    /* Copio a referência inicial de str. */
    ptr_str = str;

    /* str <- sentence */
    strcpy(str, sentence);

    /* Retiram-se as palavras a serem desprezadas. */
    for (i = 0; i < n_ignore; i++)
    {
        pch = strstr(str, ignoreList[i]);

        if (pch != NULL)
           memset(pch, SCANNER_SBCLS, strlen(ignoreList[i]));
    }

    /* Contar os tokens. */
    pch = strtok(str, delims);

    while (pch != NULL)
    {
        pch = strtok(NULL, delims);
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
        if (token_addToken(toks, str) == TOKENS_ETOKOVERFLOW)
        {
            free(str);
            asmError_setDesc(SCANNER_ERROR_MSG);
            return SCANNER_ERROR;
        }

        str += strlen(str);
        while(*(++str) == SCANNER_SBCLS);

        cont_tokens--;
    }

    /* Chegado aqui, os tokens foram inseridos com sucesso. */

    /* Libere a memória de str. */
    free(ptr_str);

    return toks;
}
