/*
 * Nome do Arquivo:  reg.h
 *       Descricao:  TAD para armazenamento de um registrador declarado pelo
 *                   programador.
 *
 * Exported functions from reg.c.
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

#ifndef REG_HEADER
#define REG_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "../../../asmError.h"

#define REG_EALLOC          NULL
#define REG_EALLOC_MSG      "Falha ao alocar memória para REG."

#define REG_TYPE_INPUT		0
#define REG_TYPE_OUTPUT		1

typedef struct _reg
{
    char *      name; //Nome do registrador
	uint8_t		type; //Tipo do registrador (input ou output)
} REG;


/* -> REG *reg_new(const char *name, uint8_t type)
 * 
 * - DESCRIÇÃO: Instancia um novo registro de registrador declarado.
 *   
 * - PARÂMETROS: 
 *      -> const char *name: Nome do registrador.
 *      -> uint8_t type: Tipo do registrador.
 *      	- Se REG_TYPE_INPUT  - Registrador de entrada
 *      	- Se REG_TYPE_OUTPUT - Registrador de saída
 *
 * - RETORNO: Estrutura do tipo REG instanciada.
 *   	-> Se NULL    - Erro na operação.
 *   	-> Se != NULL - Sucesso na operação.
 */
REG *       reg_new(const char *name, uint8_t type);


/* -> void reg_free(REG *reg)
 * 
 * - DESCRIÇÃO: Destrói uma estrutura existente em memória.
 *
 * - PARÂMETROS: 
 *      -> REG *reg: Estrutura a ser destruída.
 *
 * - RETORNO: void.
 */
void        reg_free(REG *reg);


/* -> char *reg_getName(REG *reg)
 * 
 * - DESCRIÇÃO: Retorna o nome dado ao registrador. 
 *   
 * - PARÂMETROS: 
 *      -> REG *reg: Estrutura a ser utilizada na leitura.
 *
 * - RETORNO: String contendo o nome do registrador.
 */
char *      reg_getName(REG *reg);


/* -> uint8_t reg_getType(REG *reg)
 * 
 * - DESCRIÇÃO: Retorna o tipo do registrador. 
 *   
 * - PARÂMETROS: 
 *      -> REG *reg: Estrutura a ser utilizada na leitura.
 *
 * - RETORNO: Numero que identifica o tipo.
 */
uint8_t reg_getType(REG *reg);


/* -> int reg_compar(const void *name, const void *reg)
 * 
 * - DESCRIÇÃO: Compara uma string com o nome do reg recebido.
 *
 * - PARÂMETROS: 
 *      -> const void *name: String a ser utilizada na operação.
 *      -> const void *reg: Estrutura a ser utilizada na operação. 
 *
 * - RETORNO: Resultado da comparação.
 *   	-> Se > 0 - A string deve vir depois do nome do reg. 
 *   	-> Se = 0 - A string é igual ao nome do reg.
 *   	-> Se < 0 - A string deve vir antes do nome do reg.
 */
int reg_compar(const void *name, const void *reg);

#endif /* REG_HEADER */
