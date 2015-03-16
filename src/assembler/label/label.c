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
 *           Autor:  Cristian Costa Mello, Gustavo Freitas de Amorim 
 *     Organizacao:  VY Cannis Majoris
 *
 * =========================================================================
 */


#include "label.h"

LABEL *label_new(const char *name, uint64_t num)
{
	LABEL *new = NULL;

	if(name == NULL){
		return (new);
	}

	new = (LABEL*)malloc(sizeof(LABEL));

	if(new != NULL){
		
        new->name = (char*)malloc(sizeof(char)*(strlen(name) + 1));

        if(new->name != NULL){
            strncpy(new->name, name, strlen(name) + 1);
            new->num = num;
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
        free(label->name);
		free(label);
	}
}

char *label_getName(LABEL *label)
{
	if(label != NULL){
        return (label->name);
	}
	return (NULL);
}

uint64_t label_getLineNum(LABEL *label)
{
    if(label != NULL){
        return (label->num);
	}

	return (0);
}

int label_comparName(const void *name, const void *label){
	
    return (strcmp(name, ((LABEL*)label)->name));

}

