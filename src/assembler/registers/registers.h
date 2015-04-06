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
#include "../../linkedList/linkedList.h"

#define REGISTERS_EALLOC                    NULL
#define REGISTERS_EALLOC_MSG                "Falha na alocação da estrutura REGISTERS."

#define REGISTERS_EDECOVERFLOW              -1
#define REGISTERS_EDECOVERFLOW_MSG          "Quantidade máxima de registradores atingida."

#define ASSEMBLER_EUSER_ADDRESSOVERFLOW     -1
#define ASSEMBLER_EUSER_ADDRESSOVERFLOW_MSG "Endereço muito grande."

typedef struct _registers
{
	LIST		*regs;	
} REGISTERS;


/* -> REGISTERS *registers_new(long int maxQtd)
 * 
 * - DESCRIÇÃO: Instancia um nova estrutura em memória.
 *   
 * - PARÂMETROS: void.
 *
 * - RETORNO: Estrutura do tipo REGISTERS instanciada.
 *   	-> Se NULL    - Erro na operação.
 *   	-> Se != NULL - Sucesso na operação.
 */
REGISTERS *     registers_new();


/* -> void registers_free(REGISTERS *regs)
 * 
 * - DESCRIÇÃO: Destrói uma estrutura existente em memória.
 *
 * - PARÂMETROS: 
 *      -> REGISTERS *regs: Estrutura a ser destruída.
 *
 * - RETORNO: void.
 */
void            registers_free(REGISTERS *regs);


/* -> long int registers_addReg(REGISTERS *regs, char *regName, uint8_t type)
 * 
 * - DESCRIÇÃO: Adiciona um registrador na estrutura recebida.
 *   
 * - PARÂMETROS: 
 *      -> REGISTERS *regs: Estrutura a ser utilizada na operação
 *      -> char *regName: Nome do registrador a ser adicionado.
 *      -> uint8_t type: Tipo do registrador.
 *
 * - RETORNO: Posição onde o registrador foi alocado.
 */
long int 		registers_addReg(REGISTERS *regs, char *regName, uint8_t type);


/* -> long int registers_regSearch(REGISTERS *regs, char *name)
 * 
 * - DESCRIÇÃO: Busca por um registrador na estrutura recebida.
 *   
 * - PARÂMETROS: 
 *      -> REGISTERS *regs: Estrutura a ser utilizada na operação
 *      -> char *name: Chave da busca.
 *
 * - RETORNO: Posição onde o registrador foi encontrado.
 *      -> Se >= 0 - Encontrou
 *      -> Se < 0  - Não encontrou
 */
long int        registers_regSearch(REGISTERS *regs, char *name);


/* -> uint32_t registers_getQtdRegs(REGISTERS *regs)
 * 
 * - DESCRIÇÃO: Retorna a quantidade de registradores alocados na 
 *   estrutura recebida.
 *   
 * - PARÂMETROS: 
 *      -> REGISTERS *regs: Estrutura a ser utilizada na operação
 *
 * - RETORNO: Quantidade de registradores alocados na estrutura recebida.
 */
uint32_t		registers_getQtdRegs(REGISTERS *regs);


/* -> REG *registers_getReg(REGISTERS *regs, uint32_t pos)
 * 
 * - DESCRIÇÃO: Retorna o registrador armazenado na posição requisitada.
 *   
 * - PARÂMETROS: 
 *      -> REGISTERS *regs: Estrutura a ser utilizada na operação
 *      -> uint32_t pos: Posição a ser lida.
 *
 * - RETORNO: Registrador alocado na posição recebida.
 *   	-> Se NULL    - Erro na operação.
 *   	-> Se != NULL - Sucesso na operação.
 */
REG *			registers_getReg(REGISTERS *regs, uint32_t pos);


/* -> uint32_t registers_getQtdInput(REGISTERS *regs)
 * 
 * - DESCRIÇÃO: Retorna a quantidade de registradores de entrada
 *   alocados na estrutura recebida.
 *   
 * - PARÂMETROS: 
 *      -> REGISTERS *regs: Estrutura a ser utilizada na operação
 *
 * - RETORNO: Quantidade de registradores entrada alocados na estrutura 
 *   recebida.
 */
uint32_t 		registers_getQtdInput(REGISTERS *regs);

#endif
