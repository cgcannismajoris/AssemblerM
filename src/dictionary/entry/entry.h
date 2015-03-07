/*
 * ==========================================================================
 *
 * Nome do Arquivo:  entry.h
 *
 *       Descricao:  TAD para armazenamento da tradução de um rótulo de
 *       			 instrução para um opcode reconhecido pela máquina.
 *
 *          Versao:  1.0
 *       Criado em:  06/03/2015 21:24:04
 *         Revisao:  none
 *      Compilador:  gcc
 *
 *           Autor:  Cristian Costa Mello, Gustavo Freitas de Amorim
 *     Organizacao:  VY Cannis Majoris
 *
 * =========================================================================
 */

#ifndef ENTRY_HEADER
#define ENTRY_HEADER

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
 
#define ENTRY_EALLOC		NULL

#define ENTRY_EALLOC_MSG 	"Falha na alocação da estrutura ENTRY."


#define ENTRY_ROTCOD_ASCII 				1
#define ENTRY_ROT_MAXLENGTH				11
#define ENTRY_ROT_MAXLENGTH_BYTES		(11 * ENTRY_ROTCOD_ASCII)


typedef struct _entry
{
    char *  instructionPattern;
    uint8_t opcode;
} ENTRY;


/* -> ENTRY *entry_new(char *rotulo, int opcode)
 * 
 * - DESCRIÇÃO: Instancia uma nova entrada do dicionário que será utilizada na
 *              tradução dos identificadores em opcodes reconhecidos pela máquina.
 *   
 * - PARÂMETROS: 
 *      -> char *pattern: Rótulo a ser inserido na estrutura.
 *      -> int opcode: Opcode correspondente ao rótulo recebido.
 *
 * - RETORNO: Estrutura do tipo ENTRY instanciada.
 *   	-> Se NULL    - Erro na operação.
 *   	-> Se != NULL - Sucesso na operação.
 */
ENTRY *         entry_new(const char *pattern, uint8_t opcode);


/* -> void entry_free(ENTRY *entry)
 *
 * - DESCRIÇÃO: Destrói uma estrutura existente em memória.
 *
 * - PARÂMETROS: 
 *      -> ENTRY *entry: Estrutura a ser destruída.
 *
 * - RETORNO: void.
 */
void            entry_free(ENTRY *entry);


/* -> const char *entry_getPattern(ENTRY *entry)
 * 
 * - DESCRIÇÃO: Retorna o rótulo armazenado na estrutura recebida.
 *
 * - PARÂMETROS: 
 *      -> ENTRY *entry: Estrutura a ser utilizada na operação.
 *
 * - RETORNO: Ponteiro para o rótulo armazenado.
 *   	-> Se NULL    - Erro na operação.
 *   	-> Se != NULL - Sucesso na operação. 
 */
const char *    entry_getPattern(ENTRY *entry);


/* -> uint8_t entry_getOpcode(ENTRY *entry)
 * 
 * - DESCRIÇÃO: Retorna o opcode armazenado na estrutura recebida.
 *
 * - PARÂMETROS: 
 *      -> ENTRY *entry: Estrutura a ser utilizada na operação.
 *
 * - RETORNO: Ponteiro para o rótulo armazenado.
 *   	-> Se 0	      - Erro na operação.
 *   	-> Se != 0    - Sucesso na operação. 
 */
uint8_t         entry_getOpcode(ENTRY *entry);

#endif /* ENTRY_HEADER */
