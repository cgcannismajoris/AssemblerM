/*
 * Nome do Arquivo:  reg.c
 *       Descricao:  Implementação do TAD REG.
 * 
 * Register for AssemblerM.
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

#include "reg.h"

REG *reg_new(const char *name, uint8_t type)
{
    REG *novo;
    int c;

    if ((novo = (REG *)malloc(sizeof(REG))) == NULL)
	{
		asmError_setDesc(REG_EALLOC_MSG);
        return REG_EALLOC;
	}

    c = strlen(name);

    if ((novo->name = (char *)malloc(c)) == NULL)
	{
		asmError_setDesc(REG_EALLOC_MSG);
        return REG_EALLOC;
	}

    strcpy(novo->name, name);
	
	novo->type = type;
    
	return novo;
}

void reg_free(REG *reg)
{
	free(reg->name);
    free(reg);
}

char *reg_getName(REG *reg)
{
    return reg->name;
}

uint8_t reg_getType(REG *reg)
{
	return reg->type;
}

int reg_compar(const void *name, const void *reg)
{
	return (strcmp(name, ((REG*)reg)->name));
}

