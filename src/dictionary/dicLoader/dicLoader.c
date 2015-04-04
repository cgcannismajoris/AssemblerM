/*
 * Nome do Arquivo:  dicLoader.c
 *       Descricao:  Implementação do TAD DICLOADER.
 * 
 * DicLoader for AssemblerM.
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

#include "dicLoader.h"

DICLOADER *dicLoader_new(const char *filename)
{
    DICLOADER *novo;

    if ((novo = (DICLOADER*)malloc(sizeof(DICLOADER))) == NULL)
    {
        asmError_setDesc(DICLOADER_EALLOC_MSG);
        return DICLOADER_EALLOC;
    }

    if ((novo->file = fopen(filename, "rb+")) == NULL)
    {
        asmError_setDesc(DICLOADER_EFOPEN_MSG);

        free(novo);
        return DICLOADER_EFOPEN;
    }

    return novo;
}

void dicLoader_free(DICLOADER *dicLoader)
{
	fclose(dicLoader->file);
	free(dicLoader);
}

uint64_t dicLoader_getQtdInst(DICLOADER *dicLoader)
{
	uint64_t qtdInst = 0;
	
	fread(&qtdInst, sizeof(uint64_t), 1, dicLoader->file);
	
    return qtdInst;
}

char *dicLoader_getNextInst(DICLOADER *dicLoader)
{
	long int i = -1;
	char *verbete;

	if(feof(dicLoader->file)){
		return (NULL);
	}

    if ((verbete = (char *)malloc(sizeof(char) * DICLOADER_MAX_INST_LENGTH)) == NULL)
    {
        asmError_setDesc(DICLOADER_EALLOC_MSG);
        return DICLOADER_EALLOC;
    }

    do
    {
		i++;
		fread(&(verbete[i]), sizeof(char), 1, dicLoader->file);
    } while(i < DICLOADER_MAX_INST_LENGTH && verbete[i] != '\0');

    return verbete;
}
