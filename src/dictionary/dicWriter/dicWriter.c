/*
 * Nome do Arquivo:  dicWriter.c
 *       Descricao:  Implementação do TAD DICWRITER.
 * 
 * DicWriter for AssemblerM.
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

#include "dicWriter.h"

DICWRITER *dicWriter_new(const char *filename)
{
    DICWRITER *novo;
	FILE *file;

    if((file = fopen(filename, "wb+")) == NULL)
	{
		asmError_setDesc(DICWRITER_EALLOC_MSG);
		return DICWRITER_EALLOC;
	}

    if ((novo = (DICWRITER*)malloc(sizeof(DICWRITER))) == NULL)
    {
        fclose(file);

        asmError_setDesc(DICWRITER_EFOPEN_MSG);
        return DICWRITER_EFOPEN;
    }

	novo->file = file;

    return novo;
}

void dicWriter_free(DICWRITER *dicWriter)
{
	fclose(dicWriter->file);
	free(dicWriter);
}

void dicWriter_writeQtdInst(DICWRITER *dicWriter, uint64_t num)
{
	//Grava a quantidade de instruções armazenadas no arquivo
	fwrite(&num, sizeof(uint64_t), 1, dicWriter->file);
}

void dicWriter_writeInst(DICWRITER *dicWriter, 
							const char *instPattern,
                          		const char *instTranslation)
{
	//Grava o padrão da instrução
	fwrite(instPattern, sizeof(char), strlen(instPattern), 
					dicWriter->file);

	//Insere uma separação
	fwrite(DICWRITER_SEPARATOR, sizeof(char), 1, dicWriter->file);

	//Grava o opcode correspondente à instrução
	fwrite(instTranslation, sizeof(char), strlen(instTranslation), 
					dicWriter->file);

	//Grava o terminador de instrução
	fwrite(DICWRITER_TERMINATOR, sizeof(char), 1, dicWriter->file);

}
