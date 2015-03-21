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

    if ((novo = (INSTRUCTION *)malloc(sizeof(INSTRUCTION))) == INSTRUCTION_EALLOC)
	{
		//Caso esteja compilando para a ferramenta INSTDEBUG, não insere o código 
		//entre ifndef e endif.
		#ifndef COMPILING_INSTDEBUG
		asmError_setDesc(INSTRUCTION_EALLOC_MSG);
		#endif
        return INSTRUCTION_EALLOC;
	}

    novo->inst = inst;

    return novo;
}

void inst_free(INSTRUCTION *instruction)
{
    free(instruction);
}

uint32_t inst_getInst(INSTRUCTION *instruction)
{
    return (instruction->inst);
}

void inst_setInst(INSTRUCTION *instruction, uint32_t inst)
{
    instruction->inst = inst;
}
