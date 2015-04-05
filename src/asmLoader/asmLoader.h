/*
 * Nome do Arquivo:  asmLoader.h
 *       Descricao:  TAD para leitura do arquivo contendo o código fonte 
 *                   escrito pelo programador.
 *
 * Exported functions from asmLoader.c.
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


#ifndef ASMLOADER_HEADER
#define ASMLOADER_HEADER

#include <stdio.h>  /* para I/O */
#include <stdlib.h>
#include <string.h>

#include "../asmError.h"

#define ASMLOADER_EALLOC        NULL    /* FALHA DE ALOCAÇÃO */
#define ASMLOADER_EGETINST      NULL    /* Falha ao se obter nova instrução */

#define ASMLOADER_EALLOC_MSG    "Falha na alocação da estrutura ASMLOADER."
#define ASMLOADER_EGETINST_MSG  "Falha ao se obter nova instrução."

#define ASMLOADER_EFOPEN_MSG    "Falha na abertura do arquivo de código-fonte."

#define ASMLOADER_FCOD_ASCII           1                             /* Codificação ASCII (1 byte/caractere) */
#define ASMLOADER_INST_MAXCHARLENGTH   256 * (ASMLOADER_FCOD_ASCII)  /* Quantidade máxima de caracteres da instrução */


typedef struct _asmLoader
{
    FILE *          file;       // Ponteiro para o arquivo a ser lido.
    char *          inst_atual; // Instrução atual lida.
} ASMLOADER;


/* -> ASMLOADER *asmLoader_new(const char *filename)
 * 
 * - DESCRIÇÃO: Instancia um novo loader do assembler que será utilizado na leitura
 *   de instruções escritas pelo programador.
 *
 * - PARÂMETROS: 
 *      -> const char *filename: Nome do arquivo a ser utilizado.
 *
 * - RETORNO: Estrutura do tipo ASMLOADER instanciada.
 *   	-> Se NULL    - Erro na operação.
 *   	-> Se != NULL - Sucesso na operação.
 */
ASMLOADER *     asmLoader_new(const char *filename);


/* -> void asmLoader_free(ASMLOADER *asmLoader)
 * 
 * - DESCRIÇÃO: Destrói uma estrutura existente em memória.
 *
 * - PARÂMETROS: 
 *      -> ASMLOADER *asmLoader: Estrutura a ser destruída.
 *
 * - RETORNO: void.
 */
void            asmLoader_free(ASMLOADER *asmLoader);


/* -> void asmLoader_getNextInst(ASMLOADER *asmLoader)
 * 
 * - DESCRIÇÃO: Carrega a próxima instrução escrita pelo programador presente no 
 *   arquivo.
 *   	- Se nenhuma intrução foi lida até o momento, carrega a primeira.
 *   	- Se já leu alguma, carrega a intrução subsequênte à anteriormente carregada.
 *
 * - PARÂMETROS: 
 *      -> ASMLOADER *asmLoader: Estrutura a ser utilizada para a leitura da 
 *      instrução.
 *
 * - RETORNO: Instrução escrita pelo programador carregada.
 *   	-> Se NULL    - Erro na operação.
 *   	-> Se != NULL - Sucesso na operação.
 */
char *         asmLoader_getNextInst(ASMLOADER *asmLoader);


/* -> void asmLoader_rewind(ASMLOADER *asmLoader)
 * 
 * - DESCRIÇÃO: Retorna para o início do arquivo.
 *
 * - PARÂMETROS: 
 *      -> ASMLOADER *asmLoader: Estrutura a ser utilizada ma operação. 
 *
 * - RETORNO: void.
 */
void            asmLoader_rewind(ASMLOADER *asmLoader);

#endif /* ASMLOADER_HEADER */
