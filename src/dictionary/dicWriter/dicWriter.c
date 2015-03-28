/*
 * ==========================================================================
 *
 * Nome do Arquivo:  dicWriter.c
 *
 *       Descricao:  Implementação do TAD DICWRITER.
 *
 *          Versao:  1.0
 *       Criado em:  07/03/2015 17:52:42
 *         Revisao:  none
 *      Compilador:  gcc
 *
 *           Autor:  Cristian Costa Mello, Gustavo Freitas de Amorim
 *     Organizacao:  VY Cannis Majoris
 *
 * =========================================================================
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
