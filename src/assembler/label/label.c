/*
 * ==========================================================================
 *
 * Nome do Arquivo:  label.c
 *
 *       Descricao:  Implementação do TAD LABEL.
 *
 *          Versao:  1.0
 *       Criado em:  09/03/2015 18:37:48
 *         Revisao:  none
 *      Compilador:  gcc
 *
 *           Autor:  Gustavo Freitas de Amorim (), gustavofreitasamorim@gmail.com
 *     Organizacao:  VY Cannis Majoris
 *
 * =========================================================================
 */


#include "label.h"

LABEL *label_new(const char *name, uint64_t num)
{
	LABEL *new;

	if(name != NULL){
		return (NULL);
	}

	new = (LABEL*)malloc(sizeof(LABEL));

	if(new != NULL){
		
		new->labelName = (char*)malloc(sizeof(char)*(strlen(name) + 1));

		if(new->labelName != NULL){
			strncpy(new->labelName, name, strlen(name));
			new->labelLineNum = num;
			new->next = NULL;
		}
		else{
			free(new);
			new = LABEL_EALLOC;
		}
	}

    return new;
}

void label_free(LABEL *label)
{
	if(label != NULL){
		free(label->labelName);
		free(label);
	}
}

char *label_getName(LABEL *label)
{
	if(label != NULL){
		return (label->labelName);
	}
	return (NULL);
}

uint64_t label_getLineNum(LABEL *label)
{
    if(label != NULL){
		return (label->labelLineNum);
	}

	return (0);
}

void label_setNext(LABEL *label, LABEL *next){
	if(label != NULL){
		label->next = next;
	}
}
