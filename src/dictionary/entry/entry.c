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
	
	ENTRY *new = NULL;
	char *new_pat = NULL;
	char *new_tra = NULL;
	
	if(instPattern == NULL || instTranslation == NULL ||
					strlen(instPattern) < ENTRY_STR_MAXLENGTH){
		return (new);
	}

	new = (ENTRY*)malloc(sizeof(ENTRY));

	if(new != NULL) 
	{
		new_pat = (char*)malloc(ENTRY_STR_MAXLENGTH_BYTES);
		new_tra = (char*)malloc(ENTRY_STR_MAXLENGTH_BYTES);

		if(new_pat != NULL && new_tra != NULL)
		{
			new->instPattern = new_pat;	
			strncpy(new->instPattern, instPattern, ENTRY_STR_MAXLENGTH);

			new->instTranslation = new_tra;
			strncpy(new->instTranslation, instTranslation, ENTRY_STR_MAXLENGTH);
		}
		else
		{ //new foi alocado mas o rótulo não
			free(new);
			free(new_pat);
			free(new_tra);
			new = ENTRY_EALLOC;
		}
	}

    return new;
}

void entry_free(ENTRY *entry)
{

	free(entry->instPattern);
	free(entry);	

}

const char *entry_getPattern(ENTRY *entry)
{
	if(entry != NULL)
	{
		return(entry->instPattern);
	}

	return(NULL);
}

char *entry_getTranslation(ENTRY *entry)
{
	if(entry != NULL)
	{
		return(entry->instTranslation);
	}

	return(0);
}
