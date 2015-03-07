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

ENTRY *entry_new(const char *pattern, uint8_t opcode)
{
	
	ENTRY *new = NULL;
	char *new_rot = NULL;

	if(pattern != NULL && strlen(pattern) < ENTRY_ROT_MAXLENGTH){

		new = (ENTRY*)malloc(sizeof(ENTRY));

		if(new != NULL) 
		{

			new_rot = (char*)malloc(ENTRY_ROT_MAXLENGTH_BYTES);
	
			if(new_rot != NULL)
			{
				new->instructionPattern = new_rot;	
				strncpy(new->instructionPattern, pattern, ENTRY_ROT_MAXLENGTH);
				new->opcode = opcode;
			}
			else
			{ //new foi alocado mas o rótulo não
				free(new);
				new = ENTRY_EALLOC;
			}
		}
	}

    return new;
}

void entry_free(ENTRY *entry)
{

	free(entry->instructionPattern);
	free(entry);	

}

const char *entry_getPattern(ENTRY *entry)
{
	if(entry != NULL)
	{
		return(entry->instructionPattern);
	}

	return(NULL);
}

uint8_t entry_getOpcode(ENTRY *entry)
{
	if(entry != NULL)
	{
		return(entry->opcode);
	}

	return(0);
}
