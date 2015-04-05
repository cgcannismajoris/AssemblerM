/*
 * Nome do Arquivo:  entry.h
 *       Descricao:  TAD para armazenamento da tradução de um rótulo de
 *                   instrução para um opcode reconhecido pela máquina.
 *
 * Exported functions from entry.c.
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

#ifndef ENTRY_HEADER
#define ENTRY_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
 
#include "../../asmError.h"

#define ENTRY_EALLOC		NULL
#define ENTRY_EALLOC_MSG 	"Falha na alocação da estrutura ENTRY."

#define ENTRY_STRCOD_ASCII 	1


typedef struct _entry
{
    char *  instPattern; //Padrão da instrução
	char *	instTranslation; //Tradução do padrão
} ENTRY;


/* -> ENTRY *entry_new(const char *instPattern, const char *instTranslation)
 * 
 * - DESCRIÇÃO: Instancia uma nova entrada do dicionário que será utilizada na
 *              tradução dos identificadores em operações reconhecidos pela máquina.
 *   
 * - PARÂMETROS: 
 *      -> const char *instPattern: Padrão da instrução a ser armazenado.
 *      -> const char *instTranslation: Tradução do padrão a ser armazenado.
 *
 * - RETORNO: Estrutura do tipo ENTRY instanciada.
 *   	-> Se NULL    - Erro na operação.
 *   	-> Se != NULL - Sucesso na operação.
 */
ENTRY *         entry_new(const char *instPattern, const char *instTranslation);


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
 * - DESCRIÇÃO: Retorna o padrão armazenado na estrutura recebida.
 *
 * - PARÂMETROS: 
 *      -> ENTRY *entry: Estrutura a ser utilizada na operação.
 *
 * - RETORNO: Ponteiro para o padrão armazenado.
 */
const char *    entry_getPattern(ENTRY *entry);


/* -> char *entry_getTranslation(ENTRY *entry)
 * 
 * - DESCRIÇÃO: Retorna a tradução armazenada na estrutura recebida.
 *
 * - PARÂMETROS: 
 *      -> ENTRY *entry: Estrutura a ser utilizada na operação.
 *
 * - RETORNO: Ponteiro para a tradução armazenada.
 */
char *          entry_getTranslation(ENTRY *entry);

#endif /* ENTRY_HEADER */
