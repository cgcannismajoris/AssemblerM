/*
 * ===========================================================================
 *
 * Nome do Arquivo:  registers.h
 *
 *       Descricao:  TAD para manipulação dos registradores utilizados pela máquina.
 *
 *          Versao:  1.0
 *       Criado em:  21/03/2015 09:43:22
 *         Revisao:  none
 *      Compilador:  gcc
 *
 *           Autor:  Cristian Costa Mello, Gustavo Freitas de Amorim
 *     Organizacao:  VY Cannis Majoris
 *
 * ===========================================================================
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

#endif
