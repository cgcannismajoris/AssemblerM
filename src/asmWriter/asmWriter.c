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

void asmWriter_writeInt(ASMWRITER *asmWriter, uint32_t num)
{
	fwrite(&(num), sizeof(uint32_t), 1, asmWriter->file);
}

