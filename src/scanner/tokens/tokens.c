/*
 * Nome do Arquivo:  tokens.c
 *       Descricao:  Implementação do TAD TOKENS.
 *
 * Tokens for AssemblerM.
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


#include "tokens.h"

TOKENS *token_new(uint32_t qtd)
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

uint32_t token_getQtd(TOKENS *token)
{
	return (token->qtdUsed);
}

char *token_getToken(TOKENS *token, uint32_t pos)
{
	if(pos >= token->qtdUsed)
		return (NULL);

	return (token->tokens[pos]);
}

int token_addToken(TOKENS *token, char *t){
	
	if(token->qtdUsed < token->qtdMax)
	{
        token->tokens[token->qtdUsed] = (char*)malloc(sizeof(char) * strlen(t) + 1);
        strncpy(token->tokens[token->qtdUsed], t, strlen(t) + 1);

		token->qtdUsed++;

        return 0;
	}

    return -1;
}

long int token_search(TOKENS *token, const char *search)
{
    uint8_t i;

    for (i = 0; i < token->qtdUsed; i++)
    {
        if (!strcmp(token->tokens[i], search))
            return i;
    }

    return -1;
}

int token_verifCommon(TOKENS *one, TOKENS *two)
{
	int i, j;

	for(i = 0; i < one->qtdUsed; i++)
	{
		for(j = 0; j < two->qtdUsed; j++)
		{
			if(strcmp(one->tokens[i], two->tokens[j]) == 0)
				return (1);
		}
	}

	return (0);
}

int token_verifRepetitions(TOKENS *one)
{
	int i, j;
 
	for(i = 0; i < one->qtdUsed; i++)
	{
		for(j = 0; j < one->qtdUsed; j++)
		{
			if(strcmp(one->tokens[i], one->tokens[j]) == 0)
			{
				if(i != j)
					return (1);
			}
		}
	}	

	return (0);
}

