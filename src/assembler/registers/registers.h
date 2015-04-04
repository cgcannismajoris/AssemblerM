/*
 * Nome do Arquivo:  registers.h
 *       Descricao:  TAD para manipulação dos registradores utilizados pela máquina.
 *
 * Exported functions from registers.c.
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

#ifndef REGISTERS_H
#define REGISTERS_H

#include "reg/reg.h"

#define REGISTERS_EALLOC                    NULL
#define REGISTERS_EALLOC_MSG                "Falha ao alocar memória no TAD REGISTERS."

#define REGISTERS_EDECOVERFLOW              -1
#define REGISTERS_EDECOVERFLOW_MSG          "Quantidade máxima de registradores atingida."

#define ASSEMBLER_EUSER_ADDRESSOVERFLOW     -1
#define ASSEMBLER_EUSER_ADDRESSOVERFLOW_MSG "Endereço muito grande."


typedef struct _registers
{
    REG **      regs;
    uint32_t    qtdRegs;
    uint32_t    maxQtd;
} REGISTERS;


REGISTERS *     registers_new(long int maxQtd);
void            registers_free(REGISTERS *regs);
long int 		registers_addReg(REGISTERS *regs, char *regName, uint8_t type);
long int        registers_regSearch(REGISTERS *regs, char *name);
uint32_t		registers_getQtdRegs(REGISTERS *regs);
REG *			registers_getReg(REGISTERS *regs, uint32_t pos);
uint32_t 		registers_getQtdInput(REGISTERS *regs);

#endif
