/*
 * ==========================================================================
 *
 * Nome do Arquivo:  reg.c
 *
 *       Descricao:  Implementação do TAD REG.
 *
 *          Versao:  1.0
 *       Criado em:  20/03/2015 22:37:23
 *         Revisao:  none
 *      Compilador:  gcc
 *
 *           Autor:  Cristian Costa Mello, Gustavo Freitas de Amorim
 *     Organizacao:  VY Cannis Majoris
 *
 * =========================================================================
 */


#include "reg.h"

REG *reg_new(const char *name)
{
    REG *novo;
    int c;

    if ((novo = (REG *)malloc(sizeof(REG))) == NULL)
	{
		asmError_setDesc(REG_EALLOC_MSG);
        return REG_EALLOC;
	}

    c = strlen(name);

    if ((novo->name = (char *)malloc(c)) == NULL)
	{
		asmError_setDesc(REG_EALLOC_MSG);
        return REG_EALLOC;
	}

    strcpy(novo->name, name);

    return novo;
}

void reg_free(REG *reg)
{
	free(reg->name);
    free(reg);
}

char *reg_getName(REG *reg)
{
    return reg->name;
}

