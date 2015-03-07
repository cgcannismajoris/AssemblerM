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
 *           Autor:  Gustavo Freitas de Amorim (), gustavofreitasamorim@gmail.com
 *     Organizacao:  VY Cannis Majoris
 *
 * ===========================================================================
 */

#ifndef INSTRUCTION_HEADER
#define INSTRUCTION_HEADER

#include <stdint.h>

//Tipos de Instruções aceitos
typedef union _inst_r{
    unsigned int opcode:6;
    unsigned int dest:5;
    unsigned int orig1:5;
    unsigned int orig2:5;
    unsigned int address:11;
} TIPO_R, TYPE_R;

typedef union _inst_j{
    unsigned int opcode:6;
    unsigned int address:24;
} TIPO_J, TYPE_J;

typedef union _inst_b{
    unsigned int opcode:6;
    unsigned int reg1:5;
    unsigned int reg2:5;
    unsigned int address:16;
} TIPO_B, TYPE_B;


//Estrutura para armazenamento da instrução binária
typedef struct _instruction{
    uint32_t isnt;
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
 *   	-> Se NULL    - Erro na operação.
 *   	-> Se != NULL - Sucesso na operação.
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
 *   	-> Se 0       - Erro na operação.
 *   	-> Se != 0    - Sucesso na operação.
 */
uint32_t      inst_getInst(INSTRUCTION *instruction);


/* -> uint32_t inst_setInst(INSTRUCTION *inst)
 * 
 * - DESCRIÇÃO: Seta a instrução armazenada em uma estrutura pré-alocada
 *   em memória.
 *
 * - PARÂMETROS: 
 *      -> INSTRUCTION *inst: Estrutura a ser utilizada na operação. 
 *
 * - RETORNO: void.
 */
void          inst_setInst(INSTRUCTION *instruction);

#endif /* INSTRUCTION_HEADER */

