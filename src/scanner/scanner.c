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

// LISTA DE PALAVRAS PARA IGNORAR
// SEPARADOR DOS TOKENS
TOKENS *scanner_scan(const char *sentence,
                     char **    ignoreList,
                     char *     delims,
                     uint64_t   n_ignore)
{
    TOKENS *toks;
    char *  str;
    char *  pch;
    int     cont_tokens = 0;
    uint64_t i = 0;
    LINKED_LIST *lista;
    NODE *aux;


    if ((lista = lista_new()) == NULL)
        return SCANNER_ERROR;

	if ((str = (char *)malloc((strlen(sentence) * sizeof(char)) + 1)) == NULL)
        return SCANNER_ERROR;

    /* str <- sentence */
    strcpy(str, sentence);

    /* Retiram-se as palavras a serem desprezadas. */
    for (i = 0; i < n_ignore; i++)
    {
		while ((pch = strstr(str, ignoreList[i])) != NULL)
			memset(pch, SCANNER_SBCLS, strlen(ignoreList[i]));
    }

    /* Contar os tokens. */
    pch = strtok(str, delims);
	
    while (pch != NULL)
    {
        char *aux_str;

        if ((aux_str = malloc(strlen(pch) + 1)) == NULL)
        {
        	free(str);
			lista_free(lista);
            return SCANNER_ERROR;
        }

        strcpy(aux_str, pch);

        if((aux = lista_node_new(aux_str)) == NULL)
		{
			free(str);
			lista_free(lista);
			return (SCANNER_ERROR);
		}

        lista_insertLastNode(lista, aux);

        pch = strtok(NULL, delims);
        cont_tokens++;
    }
	
    /* Alocar memória para toks. */
    if ((toks = token_new(cont_tokens)) == TOKENS_EALLOC)
    {
    	free(str);
		lista_free(lista);
        return SCANNER_ERROR;
    }

    aux = lista_getRaiz(lista);

    /* Guardar os tokens. */
    /* Inserir os tokens da string str na estrutura toks. */
    while (cont_tokens)
    {

        if (token_addToken(toks, (char *)node_getData(aux)) == TOKENS_ETOKOVERFLOW)
        {
			lista_free(lista);
			token_free(toks);
            asmError_setDesc(SCANNER_ERROR_MSG);
            return SCANNER_ERROR;
        }

		aux = node_getProx(aux);
        cont_tokens--;
    }

	/* Libera a memóra da lista. */
    lista_free(lista);
    
    /* Libera memória. */
	free(str);

    return toks;
}
