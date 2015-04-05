/*
 * Nome do Arquivo:  instruction.h
 *       Descricao:  TAD para manipulação de instruções binárias.
 *
 * Exported functions from instruction.c.
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

#ifndef INSTRUCTION_HEADER
#define INSTRUCTION_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "../asmError.h"


#define INSTRUCTION_EALLOC                  NULL
#define INSTRUCTION_EALLOC_MSG              "Falha ao alocar memória para INSTRUCTION."


#define INSTRUCTION_INSTLENGTH				(12)
#define INSTRUCTION_INSTLENGTH_BYTES		(sizeof(uint8_t) * 12)

#define INSTRUCTION_SETINST(inst, type)     memcpy(&inst, &type, INSTRUCTION_INSTLENGTH_BYTES)


//Tipos de Instruções aceitos
typedef struct _inst_r
{
    uint8_t         opcode;
    uint32_t        reg;
    signed int      address;
} TIPO_R, TYPE_R;

typedef struct _esp_beqz
{
    uint8_t         opcode;
    uint32_t        reg;
    signed int      address_t: 16;
    signed int      address_f: 16;
} TYPE_ESP_BEQZ;

//Estrutura para armazenamento da instrução binária
typedef struct _instruction
{
    uint8_t        inst[INSTRUCTION_INSTLENGTH];
} INSTRUCTION;


/* -> INSTRUCTION *inst_new(uint8_t *inst)
 * 
 * - DESCRIÇÃO: Instancia uma nova estrutura que armazena uma instrução
 *   binária.
 *
 * - PARÂMETROS: 
 *      -> uint8_t *inst: Instrução a ser salva na estrutura.
 *
 * - RETORNO: Estrutura do tipo INSTRUCTION instanciada.
 *   	-> Se NULL    - Erro na operação.
 *   	-> Se != NULL - Sucesso na operação.
 */
INSTRUCTION *   inst_new(uint8_t *inst);

/* -> void inst_free(INSTRUCTION *instruction)
 *
 * - DESCRIÇÃO: Destrói uma estrutura existente em memória.
 *
 * - PARÂMETROS: 
 *      -> INSTRUCTION *inst: Estrutura a ser destruída.
 *
 * - RETORNO: void.
 */
void            inst_free(INSTRUCTION *instruction);


/* -> uint8_t *inst_getInst(INSTRUCTION *inst)
 * 
 * - DESCRIÇÃO: Retorna a instrução armazenada na estrutura recebida como
 *   parâmetro.
 *
 * - PARÂMETROS: 
 *      -> INSTRUCTION *inst: Estrutura a ser utilizada na operação. 
 *
 * - RETORNO: Instrução armazenada na estrutura.
 *   	-> Se NULL       - Erro na operação.
 *   	-> Se != NULL    - Sucesso na operação.
 */
uint8_t *      inst_getInst(INSTRUCTION *instruction);


/* -> void inst_setInst(INSTRUCTION *instruction, uint8_t *inst)
 * 
 * - DESCRIÇÃO: Seta uma instrução na estrutura recebida.
 *
 * - PARÂMETROS: 
 *      -> INSTRUCTION *instruction: Estrutura a ser utilizada na operação.
 *      -> uint8_t *inst: Instrução a ser salva na estrutura.
 *
 * - RETORNO: void.
 */
void            inst_setInst(INSTRUCTION *instruction, uint8_t *inst);

#endif /* INSTRUCTION_HEADER */

