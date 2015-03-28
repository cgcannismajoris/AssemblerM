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
    LABEL *novo;

    if((novo = (LABEL*)malloc(sizeof(LABEL))) == NULL)
	{
		asmError_setDesc(LABEL_EALLOC_MSG);
		return (LABEL_EALLOC);
	}

    if((novo->name = (char*)malloc(sizeof(char)*(strlen(name) + 1))) == NULL)
	{
		asmError_setDesc(LABEL_EALLOC_MSG);
		return (LABEL_EALLOC);
	}

	strncpy(novo->name, name, strlen(name) + 1);
	novo->num = num;
    return novo;
}

void label_free(LABEL *label)
{
	free(label->name);
	free(label);
}

char *label_getName(LABEL *label)
{
	return (label->name);
}

uint64_t label_getLineNum(LABEL *label)
{
	return (label->num);
}

int label_comparName(const void *name, const void *label)
{
    return (strcmp(name, ((LABEL*)label)->name));
}

