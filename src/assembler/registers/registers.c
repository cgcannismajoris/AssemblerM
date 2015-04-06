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

REGISTERS *registers_new()
{
	REGISTERS *novo;

    if((novo = (REGISTERS*)malloc(sizeof(REGISTERS))) == NULL)
	{
		asmError_setDesc(REGISTERS_EALLOC_MSG);
		return (REGISTERS_EALLOC);
	}

	//Aloca a lista de registradores
	if((novo->regs = lista_new()) == NULL)
	{
		free(novo);
		asmError_setDesc(REGISTERS_EALLOC_MSG);
		return (REGISTERS_EALLOC);
	}
	
	return novo;
}

void registers_free(REGISTERS *regs)
{
	lista_free(regs->regs);	
	free(regs);
}

long int registers_addReg(REGISTERS *regs, char *regName, uint8_t type)
{
	NODE *regNode;
	REG *novo;

	if((novo = reg_new(regName, type)) == REG_EALLOC)
	{
		//Erro de alocação
		asmError_setDesc(REGISTERS_EALLOC_MSG);
		return(-1);
	}

	regNode = lista_node_new(novo);
	lista_insertLastNode(regs->regs, regNode);
 
	return (lista_getQuant(regs->regs) - 1);
}

long int registers_regSearch(REGISTERS *regs, char *name)
{
	return (lista_search_getPos(regs->regs, name, reg_compar));
}

uint32_t registers_getQtdRegs(REGISTERS *regs)
{
	return (lista_getQuant(regs->regs));
}

REG *registers_getReg(REGISTERS *regs, uint32_t pos)
{
	NODE *tmp;

	if(pos > lista_getQuant(regs->regs))
		return (NULL);

	tmp = lista_getNode(regs->regs, pos);

	if(tmp != NULL)
	{
		return (node_getData(tmp));
	}

	return (NULL);
}

uint32_t registers_getQtdInput(REGISTERS *regs)
{
	uint64_t i; 
	uint32_t qtd = 0;
	NODE *tmpNode = lista_getRaiz(regs->regs);
	
	REG *tmpReg;
 
	for(i = 0; i < lista_getQuant(regs->regs); i++)
	{
		tmpReg = node_getData(tmpNode);
		
		if(tmpReg->type == REG_TYPE_INPUT)
			 qtd++;
		
		tmpNode = node_getProx(tmpNode);
	}
 
	return qtd;
}
