/*
 * Nome do Arquivo:  scanner.h
 *       Descricao:  Método para geração de tokens para o assembler.
 *
 * Exported functions from scanner.c.
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

#ifndef SCANNER_HEADER
#define SCANNER_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "tokens/tokens.h" /* incluir o TAD TOKENS (Conjunto de TOKENS) */
#include "../linkedList/linkedList.h" /* incluir o TAD LIST */

#define SCANNER_SBCLS               0x20        /* Space Bar */

#define SCANNER_ERROR               NULL
#define SCANNER_ERROR_MSG           "Falha na operação de scanner."


/* -> TOKENS *scanner_scan(const char *sentence, char **ignoreList,
 *                                       char *delims, uint64_t n_ignore)
 * 
 * - DESCRIÇÃO: Escaneador de uma sentença.
 *
 * - PARÂMETROS: 
 *      -> const char *sentence: Sentença a ser escaneada.
 *      -> char **ignoreList: Lista de termos a serem ignorados.
 *      -> char *delims: Expressão onde cada caractere é um delimitador.
 *      -> uint64_t n_ignore: Total de termos a serem ignorados.
 *
 * - RETORNO: Estrutura do tipo TOKENS contendo os tokens gerados.
 *   	-> Se NULL    - Erro na operação.
 *   	-> Se != NULL - Sucesso na operação.
 */
TOKENS *scanner_scan(const char *sentence,
                     char **ignoreList,
                     char *delims,
                     uint64_t n_ignore);

#endif /* SCANNER_HEADER */
