/*
 * ==========================================================================
 *
 * Nome do Arquivo:  dicLoader.c
 *
 *       Descricao:  Implementação do TAD DICLOADER.
 *
 *          Versao:  1.0
 *       Criado em:  14/03/2015 20:20:03
 *         Revisao:  none
 *      Compilador:  gcc
 *
 *           Autor:  Cristian Costa Mello, Gustavo Freitas de Amorim
 *     Organizacao:  VY Cannis Majoris
 *
 * =========================================================================
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
