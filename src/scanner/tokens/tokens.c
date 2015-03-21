/*
 * ==========================================================================
 *
 * Nome do Arquivo:  tokens.c
 *
 *       Descricao:  Implementação do TAD TOKENS.
 *
 *          Versao:  1.0
 *       Criado em:  11/03/2015 14:55:56
 *         Revisao:  none
 *      Compilador:  gcc
 *
 *           Autor:  Cristian Costa Mello, Gustavo Freitas de Amorim
 *     Organizacao:  VY Cannis Majoris
 *
 * =========================================================================
 */


#include "tokens.h"

TOKENS *token_new(uint8_t qtd)
{
	
	TOKENS *novo = NULL;
	
	if((novo = (TOKENS*)malloc(sizeof(TOKENS))) == TOKENS_EALLOC)
	{
		asmError_setDesc(TOKENS_EALLOC_MSG);
		return (TOKENS_EALLOC);
	}
	
	if((novo->tokens = (char**)malloc(sizeof(char*) * qtd)) == TOKENS_EALLOC)
	{
		free(novo);
		asmError_setDesc(TOKENS_EALLOC_MSG);
		return (TOKENS_EALLOC);
	}
	
	novo->qtdUsed = 0;
	novo->qtdMax = qtd;

	return novo;
}

void token_free(TOKENS *token)
{
	
	uint8_t qtd;

    //Destrói as strings
	for(qtd = 0; qtd < token->qtdMax; qtd++)
	{
		free(token->tokens[qtd]);
	}

	free(token->tokens);
	free(token);
}

uint8_t token_getQtd(TOKENS *token)
{
	return (token->qtdUsed);
}

char *token_getToken(TOKENS *token, uint8_t pos)
{
	return (token->tokens[pos]);
}

void token_addToken(TOKENS *token, char *t){
	
	if(token->qtdUsed < token->qtdMax)
	{
        token->tokens[token->qtdUsed] = (char*)malloc(sizeof(char) * strlen(t) + 1);
        strncpy(token->tokens[token->qtdUsed], t, strlen(t) + 1);

		token->qtdUsed++;
	}
}

int token_search(TOKENS *token, const char *search)
{
    uint8_t i;

    for (i = 0; i < token->qtdUsed; i++)
    {
        if (!strcmp(token->tokens[i], search))
            return i;
    }

    return -1;
}
