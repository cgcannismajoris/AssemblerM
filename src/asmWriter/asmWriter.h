/*
 * Nome do Arquivo:  asmWriter.h
 *       Descricao:  TAD para escrita do arquivo binário de saída do 
 *                   assembler.
 *
 * Exported functions from asmWriter.c.
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


#ifndef ASMWRITER_HEADER
#define ASMWRITER_HEADER

#include <stdio.h>
#include <stdlib.h>

#include "../instruction/instruction.h"

#define ASMWRITER_EALLOC        NULL
#define ASMWRITER_EALLOC_MSG    "Falha na alocação da estrutura ASWRITER."

#define ASMWRITER_EFOPEN        NULL
#define ASMWRITER_EFOPEN_MSG    "Falha ao salvar arquivo binário."


typedef struct _asmWriter
{
    FILE *file; //Arquivo a ser utilizado
} ASMWRITER;

 
/* -> ASMWRITER *     asmWriter_new(const char *filename)
 * 
 * - DESCRIÇÃO: Instancia um novo writer do assembler que será utilizado na
 *              escrita do arquivo binário.
 *   
 * - PARÂMETROS: 
 *      -> const char *filename: Nome do arquivo a ser utilizado.
 *
 * - RETORNO: Estrutura do tipo ASMWRITER instanciada.
 *   	-> Se NULL    - Erro na operação.
 *   	-> Se != NULL - Sucesso na operação.
 */
ASMWRITER *     asmWriter_new(const char *filename);


/* -> void asmWriter_free(ASMWRITER *asmWriter)
 * 
 * - DESCRIÇÃO: Destrói uma estrutura existente em memória.
 *
 * - PARÂMETROS: 
 *      -> ASMWRITER *asmWriter: Estrutura a ser destruída.
 *
 * - RETORNO: void.
 */
void            asmWriter_free(ASMWRITER *asmWriter);


/* -> void asmWriter_writeInst(ASMWRITER *asmWriter, INSTRUCTION *instruction)
 * 
 * - DESCRIÇÃO: Grava no arquivo a instrução binária recebida como parâmetro.
 *
 * - PARÂMETROS: 
 *      -> ASMWRITER *asmWriter: Estrutura a ser utilizada para a escrita da 
 *      instrução.
 *      -> INSTRUCTION *instruction: Instrução a ser escrita.
 *
 * - RETORNO: void.
 */
void            asmWriter_writeInst(ASMWRITER *asmWriter,
                                    INSTRUCTION *instruction);


/* -> void asmWriter_writeHeader(ASMWRITER *asmWriter, uint8_t *header, size_t length)
 * 
 * - DESCRIÇÃO: Grava no arquivo o cabeçãlho recebido.
 *
 * - PARÂMETROS: 
 *      -> ASMWRITER *asmWriter: Estrutura a ser utilizada para a escrita da 
 *      instrução.
 *      -> uint8_t *header: Cabeçalho a ser escrito.
 *      -> size_t length: Tamanho, em bytes, do cabeçalho.
 *
 * - RETORNO: void.
 */
void asmWriter_writeHeader(ASMWRITER *asmWriter, uint8_t *header, size_t length);

#endif /* ASMWRITER_HEADER */
