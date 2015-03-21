/*
 * ==========================================================================
 *
 * Nome do Arquivo:  asmError.c
 *
 *       Descricao:  Implementação do módulo asmError.
 *
 *          Versao:  1.0
 *       Criado em:  21/03/2015 08:46:18
 *         Revisao:  none
 *      Compilador:  gcc
 *
 *           Autor:  Cristian Costa Mello, Gustavo Freitas de Amorim
 *     Organizacao:  VY Cannis Majoris
 *
 * =========================================================================
 */

#include "asmError.h"

//Armazena a string do erro gerado.
static char *__failureDescription;


char *asmError_new(uint32_t desc)
{
    if ((__failureDescription = (char *)malloc(sizeof(char) * desc)) == NULL)
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
