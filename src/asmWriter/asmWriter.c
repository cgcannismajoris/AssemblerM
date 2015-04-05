/*
 * Nome do Arquivo:  asmWriter.c
 *       Descricao:  Implementação do TAD ASMWRITER.
 * 
 * AsmWriter for AssemblerM.
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

#include "asmWriter.h"

ASMWRITER *asmWriter_new(const char *filename)
{
    ASMWRITER *novo;

    if ((novo = (ASMWRITER*)malloc(sizeof(ASMWRITER))) == NULL)
    {
        asmError_setDesc(ASMWRITER_EALLOC_MSG);
        return ASMWRITER_EALLOC;
    }

    if ((novo->file = fopen(filename, "wb+")) == NULL)
    {
        free(novo);
        asmError_setDesc(ASMWRITER_EFOPEN_MSG);

        return ASMWRITER_EALLOC;
    }
    
    return novo;
}

void asmWriter_free(ASMWRITER *asmWriter)
{
	fclose(asmWriter->file);
	free(asmWriter);
}

void asmWriter_writeInst(ASMWRITER *asmWriter, INSTRUCTION *instruction)
{
	fwrite(&(instruction->inst), INSTRUCTION_INSTLENGTH, 1, asmWriter->file);
}

void asmWriter_writeHeader(ASMWRITER *asmWriter, uint8_t *header, size_t length)
{
	fwrite(header, sizeof(uint8_t), length, asmWriter->file);
}

