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

	DICWRITER *new = NULL;
	FILE *file;

	file = fopen(filename, "wb+");

	if(file != NULL)
	{
		new = (DICWRITER*)malloc(sizeof(DICWRITER));
		new->file = file;
	}

    return new;
}

void dicWriter_free(DICWRITER *dicWriter)
{
	if(dicWriter != NULL)
	{
		fclose(dicWriter->file);
		free(dicWriter);
	}
}

int dicWriter_writeQtdInst(DICWRITER *dicWriter, uint64_t num)
{
	
	if(dicWriter != NULL)
	{
		//Grava a quantidade de instruções armazenadas no arquivo
		fwrite(&num, sizeof(uint64_t), 1, dicWriter->file);

		return(0);
	}
	
	return(DICWRITER_ENULLPOINTER);
}

int dicWriter_writeInst(DICWRITER *dicWriter, 
							const char *instPattern,
                          		const char *instTranslation)
{

	if(dicWriter != NULL && instPattern != NULL)
	{
		//Grava o padrão da instrução
		fwrite(instPattern, sizeof(char), strlen(instPattern), 
						dicWriter->file);

		//Insere uma separação
		fwrite("&", sizeof(char), 1, dicWriter->file);

		//Grava o opcode correspondente à instrução
		fwrite(instTranslation, sizeof(char), strlen(instTranslation), 
						dicWriter->file);

		//Grava o terminador de instrução
		fwrite("\0", sizeof(char), 1, dicWriter->file);

		return(0);
	}
	
	return(DICWRITER_ENULLPOINTER);
}
