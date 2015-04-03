/*
 * ==========================================================================
 *
 * Nome do Arquivo:  asmWriter.c
 *
 *       Descricao:  Implementação do TAD ASMWRITER.
 *
 *          Versao:  1.0
 *       Criado em:  05/03/2015 17:11:43
 *         Revisao:  none
 *      Compilador:  gcc
 *
 *           Autor:  Cristian Costa Mello, Gustavo Freitas de Amorim
 *     Organizacao:  VY Cannis Majoris
 *
 * =========================================================================
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
 	size_t j;
	

//	fwrite(num, length, 1, asmWriter->file);
// 	printf("ftell = %lu\n\n", ftell(asmWriter->file));

	fwrite(&(((uint32_t*)header)[0]), sizeof(uint32_t), 1, asmWriter->file);
	for(j = sizeof(uint32_t); j < length; j)
	{
//		printf("TYPE  = %s\n", ((uint8_t*)num)[j] == 0 ? "IN" : "OUT");
		fwrite(&(((uint8_t*)header)[j]), sizeof(uint8_t), 1, asmWriter->file);
		j += sizeof(uint8_t);

//		printf("VALUE = %i\n\n", ((int*)num)[j]); 
		fwrite(&(((int*)header)[j]), sizeof(int), 1, asmWriter->file);
		j += sizeof(int);
	}
}

