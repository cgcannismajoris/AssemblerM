/*
 * ==========================================================================
 *
 * Nome do Arquivo:  instruction.c
 *
 *       Descricao:  Implementação do TAD instruction.
 *
 *          Versao:  1.0
 *       Criado em:  05/03/2015 18:06:48
 *         Revisao:  none
 *      Compilador:  gcc
 *
 *           Autor:  Cristian Costa Mello, Gustavo Freitas de Amorim
 *     Organizacao:  VY Cannis Majoris
 *
 * =========================================================================
 */

#include "instruction.h"


INSTRUCTION *inst_new(uint32_t inst)
{
    INSTRUCTION *novo;

    if ((novo = (INSTRUCTION *)malloc(sizeof(INSTRUCTION))) == NULL)
        return INSTRUCTION_EALLOC;

    novo->inst = inst;

    return novo;
}

void inst_free(INSTRUCTION *instruction)
{
    if (instruction == NULL)
        return;

    free(instruction);
}

uint32_t inst_getInst(INSTRUCTION *instruction)
{
    if (instruction == NULL)
        return INSTRUCTION_EGETINST;

    return (instruction->inst);
}

void inst_setInst(INSTRUCTION *instruction, uint32_t inst)
{
    instruction->inst = inst;
}
