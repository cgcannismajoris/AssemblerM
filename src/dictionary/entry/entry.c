/*
 * Nome do Arquivo:  entry.c
 *       Descricao:  Implementação do TAD ENTRY.
 * 
 * Entry for AssemblerM.
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
