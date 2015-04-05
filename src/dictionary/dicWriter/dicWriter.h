/*
 * Nome do Arquivo:  dicWriter.h
 *       Descricao:  TAD para a escrita do arquivo de padrões e opcodes
 *                   aceitos pelo assembler.
 *
 * Exported functions from dicWriter.c.
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

#ifndef DICWRITER_HEADER
#define DICWRITER_HEADER

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../../asmError.h"

#define DICWRITER_EALLOC            NULL    /* FALHA DE ALOCAÇÃO */
#define DICWRITER_EALLOC_MSG        "Falha na alocação da estrutura DICWRITER."

#define DICWRITER_EFOPEN            NULL
#define DICWRITER_EFOPEN_MSG        "Falha na abertura do arquivo de gravação do dicionário."

#define DICWRITER_SEPARATOR         "&"
#define DICWRITER_TERMINATOR        "\0"

#define DICWRITER_SEPARATOR_CHR		'&'
#define DICWRITER_TERMINATOR_CHR	'\0'


typedef struct _dicWriter
{
    FILE *file; //Ponteiro para o arquivo utilizado nas operações de escrita.
} DICWRITER;


/* -> DICWRITER *dicWriter_new(const char *filename)
 * 
 * - DESCRIÇÃO: Instancia um novo writer do dicionário que será utilizado na
 *              escrita do arquivo de configurações do mesmo.
 *   
 * - PARÂMETROS: 
 *      -> const char *filename: Nome do arquivo a ser utilizado.
 *
 * - RETORNO: Estrutura do tipo DICWRITER instanciada.
 *   	-> Se NULL    - Erro na operação.
 *   	-> Se != NULL - Sucesso na operação.
 */
DICWRITER *     dicWriter_new(const char *filename);


/* -> void dicWriter_free(DICWRITER *dicWriter)
 * 
 * - DESCRIÇÃO: Destrói uma estrutura existente em memória.
 *
 * - PARÂMETROS: 
 *      -> DICWRITER *dicWriter: Estrutura a ser destruída.
 *
 * - RETORNO: void.
 */
void            dicWriter_free(DICWRITER *dicWriter);


/* -> void dicWriter_writeQtdInst(DICWRITER *dicWriter, uint64_t num)
 * 
 * - DESCRIÇÃO: Grava no arquivo o número recebido como parâmetro.
 *
 * - PARÂMETROS: 
 *      -> DICWRITER *dicWriter: Estrutura a ser utilizada para a escrita da 
 *      quantidade de instruções.
 *      -> uint64_t num: Número a ser escrito.
 *
 * - RETORNO: void.
 */
void             dicWriter_writeQtdInst(DICWRITER *dicWriter, uint64_t num);


/* -> void dicWriter_writeInst(DICWRITER *dicWriter, const char *instPattern, 
 *    const char *instTranslation);
 * 
 * - DESCRIÇÃO: Grava no arquivo da entrada do dicionário recebida como parâmetro.
 *
 * - PARÂMETROS: 
 *      -> DICWRITER *dicWriter: Estrutura a ser utilizada para a escrita da
 *      entrada.
 *      -> const char *instPattern: Padrão de instrução a ser escrito.
 *      -> const char *instTranslation: Tradução da instrução a ser escrita.
 *
 * - RETORNO: void.
 */
void             dicWriter_writeInst(DICWRITER *dicWriter, 
										const char *instPattern,
                                        const char *instTranslation);

#endif /* DICWRITER_HEADER */
