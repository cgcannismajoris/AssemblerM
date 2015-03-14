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
	
	TOKENS *new = NULL;
	
	new = (TOKENS*)malloc(sizeof(TOKENS));
	
	if(new != NULL){

		new->tokens = (char**)malloc(sizeof(char*) * qtd);
		
		if(new->tokens != NULL){
            //memset(new->tokens, 0, qtd);
			new->qtdUsed = 0;
			new->qtdMax = qtd;
		}
		else{
			free(new);
			new = TOKENS_EALLOC;
		}
	}

	return new;
}

void token_free(TOKENS *token)
{
	
	uint8_t qtd;

	if(token != NULL){
		
        //Destrói as strings
		for(qtd = 0; qtd < token->qtdMax; qtd++){
			free(token->tokens[qtd]);
		}

		free(token->tokens);
		free(token);

	}
}

uint8_t token_getQtd(TOKENS *token)
{

	if(token != NULL){
		return (token->qtdUsed);
	}

    return 0;
}

char *token_getToken(TOKENS *token, uint8_t pos)
{

	if(token != NULL && pos < token->qtdMax){
		return (token->tokens[pos]);
	}

    return NULL;
}

void token_addToken(TOKENS *token, char *t){
	
	if(token != NULL && t != NULL && token->qtdUsed < token->qtdMax){
        token->tokens[token->qtdUsed] = (char*)malloc(sizeof(char) * strlen(t) + 1);
        strncpy(token->tokens[token->qtdUsed], t, strlen(t));
		
		token->qtdUsed++;
	}
}


