/*
 * ==========================================================================
 *
 * Nome do Arquivo:  entry.c
 *
 *       Descricao:  Implementação do TAD ENTRY.
 *
 *          Versao:  1.0
 *       Criado em:  06/03/2015 21:25:50
 *         Revisao:  none
 *      Compilador:  gcc
 *
 *           Autor:  Cristian Costa Mello, Gustavo Freitas de Amorim
 *     Organizacao:  VY Cannis Majoris
 *
 * =========================================================================
 */

#include "entry.h"

ENTRY *entry_new(const char *instPattern, const char *instTranslation)
{
    ENTRY *novo;
    char *novo_pat;
    char *novo_tra;
	
    if((novo = (ENTRY*)malloc(sizeof(ENTRY))) == NULL)
	{
		asmError_setDesc(ENTRY_EALLOC_MSG);
		return ENTRY_EALLOC;
	}

    if((novo_pat = (char*)malloc(strlen(instPattern) * ENTRY_STRCOD_ASCII)) == NULL)
	{
		free(novo);
		asmError_setDesc(ENTRY_EALLOC_MSG);
		return ENTRY_EALLOC;
	}
	
    if((novo_tra = (char*)malloc(strlen(instTranslation) * ENTRY_STRCOD_ASCII)) == NULL)
	{
		free(novo_pat);
		free(novo);
		asmError_setDesc(ENTRY_EALLOC_MSG);
		return ENTRY_EALLOC;
	}

	novo->instPattern = novo_pat;	
	strncpy(novo->instPattern, instPattern, strlen(instPattern) * 
					ENTRY_STRCOD_ASCII);

	novo->instTranslation = novo_tra;
	strncpy(novo->instTranslation, instTranslation, strlen(instTranslation) * 
					ENTRY_STRCOD_ASCII);

    return novo;
}

void entry_free(ENTRY *entry)
{
    free(entry->instTranslation);
	free(entry->instPattern);
    free(entry);
}

const char *entry_getPattern(ENTRY *entry)
{
	return(entry->instPattern);
}

char *entry_getTranslation(ENTRY *entry)
{
	return(entry->instTranslation);
}
