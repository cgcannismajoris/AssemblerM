/*
 * Nome do Arquivo:  asmError.c
 *       Descricao:  Implementação do módulo asmError.
 * 
 * AsmError for AssemblerM.
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

#include "asmError.h"

//Armazena a string do erro gerado.
static char *__failureDescription;


char *asmError_new(uint32_t desc_length)
{
    if ((__failureDescription = (char *)malloc(sizeof(char) * desc_length)) == NULL)
        return NULL;

    return __failureDescription;
}

void asmError_free()
{
    free(__failureDescription);
}

char *asmError_getDesc()
{
    return __failureDescription;
}

void asmError_setDesc(const char *failureDesc)
{
    sprintf(__failureDescription, "%s", failureDesc);
}
