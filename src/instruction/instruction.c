/*
 * Nome do Arquivo:  instruction.c
 *       Descricao:  Implementação do TAD instruction.
 *
 * Instruction for AssemblerM.
 * Copyright (C) 2015  Cristian Costa Mello and Gustavo Freitas de Amorim
 *
 * This is part of AssemblerM
 * AssemblerM is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * AssemblerM is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "instruction.h"


INSTRUCTION *inst_new(uint8_t *inst)
{
    INSTRUCTION *novo;

    if ((novo = (INSTRUCTION *)malloc(sizeof(INSTRUCTION))) == NULL)
	{
		//Caso esteja compilando para a ferramenta INSTDEBUG, não insere o código 
		//entre ifndef e endif.
		#ifndef COMPILING_INSTDEBUG
		asmError_setDesc(INSTRUCTION_EALLOC_MSG);
		#endif
        return INSTRUCTION_EALLOC;
	}

	memcpy(novo->inst, inst, INSTRUCTION_INSTLENGTH);
//    novo->inst = inst;

    return novo;
}

void inst_free(INSTRUCTION *instruction)
{
    free(instruction);
}

uint8_t *inst_getInst(INSTRUCTION *instruction)
{
    return (instruction->inst);
}

void inst_setInst(INSTRUCTION *instruction, uint8_t *inst)
{
//    instruction->inst = inst;
	memcpy(instruction->inst, inst, INSTRUCTION_INSTLENGTH);
}
