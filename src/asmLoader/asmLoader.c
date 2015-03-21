/*
 * ==========================================================================
 *
 * Nome do Arquivo:  asmLoader.c
 *
 *       Descricao:  Implementação do TAD ASMLOADER.
 *
 *          Versao:  1.0
 *       Criado em:  05/03/2015 16:57:11
 *         Revisao:  none
 *      Compilador:  gcc
 *
 *           Autor:  Cristian Costa Mello, Gustavo Freitas de Amorim
 *     Organizacao:  VY Cannis Majoris
 *
 * =========================================================================
 */


#include "asmLoader.h"


ASMLOADER *asmLoader_new(const char *filename)
{
    ASMLOADER *novo;

    if ((novo = (ASMLOADER *)malloc(sizeof(ASMLOADER))) == ASMLOADER_EALLOC)
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
