/*
 * Nome do Arquivo:  label.c
 *       Descricao:  Implementação do TAD LABEL.
 * 
 * Label for AssemblerM.
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

