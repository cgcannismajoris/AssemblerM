/*
 * Nome do Arquivo:  dicLoader.h
 *       Descricao:  TAD para carregamento de padrões e opcodes aceitos pelo
 *                   assembler.
 *
 * Exported functions from dicLoader.c.
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

#ifndef DICLOADER_HEADER
#define DICLOADER_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "../../asmError.h"
 
#define DICLOADER_MAX_INST_LENGTH   256

#define DICLOADER_EALLOC            NULL
#define DICLOADER_EALLOC_MSG        "Falha na alocação da estrutura DICLOADER."

#define DICLOADER_EFOPEN            NULL
#define DICLOADER_EFOPEN_MSG        "Falha ao abrir arquivo de dicionário."


typedef struct _dicLoader
{
    FILE *file; //Arquivo a ser utilizado pelo dicionário
} DICLOADER;


/* -> DICLOADER *dicLoader_new(const char *filename)
 * 
 * - DESCRIÇÃO: Instancia um novo loader do dicionário que será utilizado na
 *              tradução da linguagem.
 *   
 * - PARÂMETROS: 
 *      -> const char *filename: Nome do arquivo a ser utilizado.
 *
 * - RETORNO: Estrutura do tipo DICLOADER instanciada.
 *   	-> Se NULL    - Erro na operação.
 *   	-> Se != NULL - Sucesso na operação.
 */
DICLOADER *     dicLoader_new(const char *filename);


/* -> void dicLoader_free(DICLOADER *dicLoader)
 * 
 * - DESCRIÇÃO: Destrói uma estrutura existente em memória.
 *
 * - PARÂMETROS: 
 *      -> DICWRITER *dicLoader: Estrutura a ser destruída.
 *
 * - RETORNO: void.
 */
void            dicLoader_free(DICLOADER *dicLoader);


/* -> uint64_t dicLoader_getQtdInst(DICLOADER *dicLoader)
 * 
 * - DESCRIÇÃO: Retorna os 8 próximos bytes do arquivo.
 *
 * - PARÂMETROS: 
 *      -> DICLOADER *dicLoader: Estrutura a ser utilizada para a leitura da 
 *      quantidade de instruções.
 *
 * - RETORNO: Estado da operação.
 *      -> Se 0    - Erro na operação.
 *      -> Se != 0 - Sucesso na operação.
 */
uint64_t        dicLoader_getQtdInst(DICLOADER *dicLoader);


/* -> char *dicLoader_getNextInst(DICLOADER *dicLoader)
 * 
 * - DESCRIÇÃO: Carrega a próxima entrada do arquivo de configurações. 
 *   
 * - PARÂMETROS: 
 *      -> DICLOADER *dicLoader: Estrutura a ser utilizada na leitura.
 *
 * - RETORNO: String contendo a entrada lida.
 *   	-> Se NULL    - Erro na operação.
 *   	-> Se != NULL - Sucesso na operação.
 */
char *          dicLoader_getNextInst(DICLOADER *dicLoader);

#endif /* DICLOADER_HEADER */
