/*
 * ===========================================================================
 *
 * Nome do Arquivo:  instruction.h
 *
 *       Descricao:  TAD para manipulação de instruções binárias.
 *
 *          Versao:  1.0
 *       Criado em:  05/03/2015 18:07:18
 *         Revisao:  none
 *      Compilador:  gcc
 *
 *           Autor:  Cristian Costa Mello, Gustavo Freitas de Amorim
 *     Organizacao:  VY Cannis Majoris
 *
 * ===========================================================================
 */

#ifndef INSTRUCTION_HEADER
#define INSTRUCTION_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


#define INSTRUCTION_EALLOC                  NULL
#define INSTRUCTION_EALLOC_MSG              "Falha ao alocar memória para INSTRUCTION."

#define INSTRUCTION_EGETINST                0
#define INSTRUCTION_EGETINST_MSG            "Falha ao se obter instrução."

#define INSTRUCTION_SETINST(inst, type)     memcpy(&inst, &type, sizeof(uint32_t))


//Tipos de Instruções aceitos
typedef struct _inst_r
{
    unsigned int opcode:    6;
    unsigned int dest:      5;
    unsigned int orig1:     5;
    unsigned int orig2:     5;
    signed int address:     11;
} TIPO_R, TYPE_R;

typedef struct _inst_j
{
    unsigned int opcode:    6;
    signed int address:     26;
} TIPO_J, TYPE_J; 

typedef struct _inst_b
{
    unsigned int opcode:    6;
    unsigned int reg1:      5;
    unsigned int reg2:      5;
    signed int address:     16;
} TIPO_B, TYPE_B;

typedef struct _esp_beqz
{
    unsigned int opcode:    6;
    unsigned int reg:       5;
    signed int address_t:   10;
    signed int address_f:   11;
} TYPE_ESP_BEQZ;

//Estrutura para armazenamento da instrução binária
typedef struct _instruction
{
    uint32_t inst;
} INSTRUCTION;


/* -> INSTRUCTION * inst_new(uint32_t inst)
 * 
 * - DESCRIÇÃO: Instancia uma nova estrutura que armazena uma instrução
 *   binária.
 *
 * - PARÂMETROS: 
 *      -> uint32_t inst: Instrução a ser salva na estrutura.
 *
 * - RETORNO: Estrutura do tipo INSTRUCTION instanciada.
 *   	-> Se INSTRUCTION_EALLOC    - Erro na operação.
 *   	-> Se != INSTRUCTION_EALLOC - Sucesso na operação.
 */
INSTRUCTION * inst_new(uint32_t inst);

/* -> uint32_t inst_free(INSTRUCTION *inst)
 *
 * - DESCRIÇÃO: Destrói uma estrutura do tipo INSTRUCTION existente 
 *   em memória.
 *
 * - PARÂMETROS: 
 *      -> INSTRUCTION *inst: Estrutura a ser destruída.
 *
 * - RETORNO: void.
 */
void          inst_free(INSTRUCTION *instruction);


/* -> uint32_t inst_getInst(INSTRUCTION *inst)
 * 
 * - DESCRIÇÃO: Retorna a instrução armazenada na estrutura recebida como
 *   parâmetro.
 *
 * - PARÂMETROS: 
 *      -> INSTRUCTION *inst: Estrutura a ser utilizada na operação. 
 *
 * - RETORNO: Instrução armazenada na estrutura.
 *   	-> Se INSTRUCTION_EGETINST       - Erro na operação.
 *   	-> Se != INSTRUCTION_EGETINST    - Sucesso na operação.
 */
uint32_t      inst_getInst(INSTRUCTION *instruction);


/* -> void inst_setInst(INSTRUCTION *instruction, uint32_t inst)
 * 
 * - DESCRIÇÃO: Seta uma instrução em uma estrutura pré-alocada
 *   em memória.
 *
 * - PARÂMETROS: 
 *      -> INSTRUCTION *instruction: Estrutura a ser utilizada na operação.
 *      -> uint32_t inst: Instrução a ser salva na estrutura.
 *
 * - RETORNO: void.
 */
void          inst_setInst(INSTRUCTION *instruction, uint32_t inst);

#endif /* INSTRUCTION_HEADER */

