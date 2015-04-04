/*
 * Nome do Arquivo:  asmLoader.c
 *       Descricao:  Implementação do TAD ASMLOADER.
 * 
 * AsmLoader for AssemblerM.
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


#include "asmLoader.h"


ASMLOADER *asmLoader_new(const char *filename)
{
    ASMLOADER *novo;

    if ((novo = (ASMLOADER *)malloc(sizeof(ASMLOADER))) == NULL)
    {
        asmError_setDesc(ASMLOADER_EALLOC_MSG);
        return ASMLOADER_EALLOC; /* stderr => ASMLOADER_EALLOC_MSG */
    }


    if ((novo->inst_atual = (char *)malloc(ASMLOADER_INST_MAXCHARLENGTH)) == NULL)
    {
        asmError_setDesc(ASMLOADER_EALLOC_MSG);
        free(novo);
        return ASMLOADER_EALLOC;
    }

    if ((novo->file = fopen(filename, "rb+")) == NULL)
    {
        free(novo->inst_atual);
        free(novo);

        asmError_setDesc(ASMLOADER_EFOPEN_MSG);
        return ASMLOADER_EALLOC;
    }

    return novo;
}

void asmLoader_free(ASMLOADER *asmLoader)
{
    fclose(asmLoader->file);
    free(asmLoader);
}

char *asmLoader_getNextInst(ASMLOADER *asmLoader)
{
    if (feof(asmLoader->file))
        return NULL;

    fscanf(asmLoader->file, "%[^\n]\n", asmLoader->inst_atual);

    return asmLoader->inst_atual;
}

void asmLoader_rewind(ASMLOADER *asmLoader)
{
    rewind(asmLoader->file);
}
