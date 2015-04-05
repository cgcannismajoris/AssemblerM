/*
 * Nome do Arquivo:  label.h
 *       Descricao:  TAD para auxiliar o assembler na indexação de labels.
 *
 * Exported functions from label.c.
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

#ifndef LABEL_HEADER
#define LABEL_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "../../asmError.h"

#define LABEL_EALLOC			NULL
#define LABEL_EALLOC_MSG		"Falha na alocação da estrutura LABEL."


typedef struct _label
{
    char *          name;    //Nome da label;
    uint64_t        num;     //Linha onde a label foi declarada;
} LABEL;


/* -> LABEL *label_new(const char *name, uint64_t num)
 * 
 * - DESCRIÇÃO: Instancia uma nova estrutura que armazena uma label declarada no
 *   código fonte do programa.
 *
 * - PARÂMETROS: 
 *      -> const char *name: Nome da label.
 *      -> uint64_t num: Número da linha onde a label foi declarada.
 *
 * - RETORNO: Estrutura do tipo LABEL instanciada.
 *   	-> Se NULL     - Erro na operação.
 *   	-> Se !=  NULL - Sucesso na operação.
 */
LABEL *     label_new(const char *name, uint64_t num);


/* -> void label_free(LABEL *label)
 *
 * - DESCRIÇÃO: Destrói uma estrutura existente em memória.
 *
 * - PARÂMETROS: 
 *      -> LABEL *label: Estrutura a ser destruída.
 *
 * - RETORNO: void.
 */
void        label_free(LABEL *label);


/* -> char *label_getName(LABEL *label)
 * 
 * - DESCRIÇÃO: Retorna o nome da label armazenado na estrutura recebida como
 *   parâmetro.
 *
 * - PARÂMETROS: 
 *      -> LABEL *label: Estrutura a ser utilizada na operação. 
 *
 * - RETORNO: Nome armazenado na estrutura.
 */
char *      label_getName(LABEL *label);


/* -> uint64_t label_getLineNum(LABEL *label)
 * 
 * - DESCRIÇÃO: Retorna o número da linha armazenado na estrutura recebida como
 *   parâmetro.
 *
 * - PARÂMETROS: 
 *      -> LABEL *label: Estrutura a ser utilizada na operação. 
 *
 * - RETORNO: Numero da linha armazenado na estrutura.
 */
uint64_t    label_getLineNum(LABEL *label);


/* -> int label_comparName(const void *name, const void *label)
 * 
 * - DESCRIÇÃO: Compara uma string com o nome da label recebida.
 *
 * - PARÂMETROS: 
 *      -> const void *name: String a ser utilizada na operação.
 *      -> const void *label: Estrutura a ser utilizada na operação. 
 *
 * - RETORNO: Nome armazenado na estrutura.
 *   	-> Se > 0 - A string deve vir depois do nome da label. 
 *   	-> Se = 0 - A string é igual ao nome da label.
 *   	-> Se < 0 - A string deve vir antes do nome da label.
 */
int			label_comparName(const void *name, const void *label);

#endif /* LABEL_HEADER */
