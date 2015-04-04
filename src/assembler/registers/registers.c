/*
 * Nome do Arquivo:  registers.c
 *       Descricao:  Implementação do TAD REGISTERS.
 * 
 * Registers for AssemblerM.
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

#include "registers.h"

REGISTERS *registers_new(long int maxQtd)
{
	REGISTERS *novo;

    if((novo = (REGISTERS*)malloc(sizeof(REGISTERS))) == NULL)
	{
		asmError_setDesc(REGISTERS_EALLOC_MSG);
		return (REGISTERS_EALLOC);
	}

    if((novo->regs = (REG**)malloc(sizeof(REG*) * maxQtd)) == NULL)
	{
		free(novo);
		asmError_setDesc(REGISTERS_EALLOC_MSG);
		return (REGISTERS_EALLOC);
	}
	
	novo->qtdRegs = 0;
	novo->maxQtd = maxQtd;

	return novo;
}

void registers_free(REGISTERS *regs)
{

	if(regs->qtdRegs > 0)
	{
		for(--regs->qtdRegs; regs->qtdRegs > 0; regs->qtdRegs--)
		{
			reg_free(regs->regs[regs->qtdRegs]);
		}
	}
	
	free(regs);
}

long int registers_addReg(REGISTERS *regs, char *regName, uint8_t type)
{
	REG *novo;

	if(regs->qtdRegs >= (regs->maxQtd - 1)){
		asmError_setDesc(REGISTERS_EDECOVERFLOW_MSG);
		return (REGISTERS_EDECOVERFLOW);
	}

	if((novo = reg_new(regName, type)) == REG_EALLOC)
	{
		//Erro de alocação
		asmError_setDesc(REGISTERS_EALLOC_MSG);
		return(-1);
	}

	regs->regs[regs->qtdRegs] = novo;
	regs->qtdRegs++;
	return (regs->qtdRegs - 1); //Retorna a posição onde foi adicionado
}

long int registers_regSearch(REGISTERS *regs, char *name)
{
	
	long int i;
	for(i = 0; i < regs->qtdRegs; i++){
		if(strcmp(reg_getName(regs->regs[i]), name) == 0){
			return (i);
		}
	}
	
	return (-1);
}

uint32_t registers_getQtdRegs(REGISTERS *regs)
{
	return (regs->qtdRegs);
}

REG *registers_getReg(REGISTERS *regs, uint32_t pos)
{
	if(pos > regs->qtdRegs)
		return (NULL);

	return (regs->regs[pos]);
}

uint32_t registers_getQtdInput(REGISTERS *regs)
{
	uint32_t i;
	uint32_t qtd = 0;

	for(i = 0; i < regs->qtdRegs; i++)
	{
		if(regs->regs[i]->type == REG_TYPE_INPUT)
			 qtd++;
	}

	return qtd;
}
