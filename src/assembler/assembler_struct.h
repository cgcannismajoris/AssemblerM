/*
 * Nome do Arquivo:  assembler_struct.h
 *       Descricao:  Declaração da estrutura principal do assembler.
 *
 * Exported definitions from assembler.c and assemblerAnalyser.c.
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


#ifndef ASSEMBLER_STRUCT_H
#define ASSEMBLER_STRUCT_H

#include "../asmLoader/asmLoader.h"         /* incluir o TAD ASMLOADER */
#include "../asmWriter/asmWriter.h"         /* incluir o TAD ASMWRITER */
#include "../instruction/instruction.h"     /* incluir o TAD INSTRUCTION */
#include "../dictionary/dictionary.h"       /* incluir o TAD DICTIONARY */
#include "registers/registers.h"            /* incluir o TAD REGISTERS */
#include "label/label.h"                    /* incluir o TAD LABEL */
#include "../scanner/scanner.h"             /* incluir o TAD SCANNER */
#include "../linkedList/linkedList.h"		/* incluir o TAD LISTA */

#include <stdarg.h>

#define ASSEMBLER_TRUE                  1
#define ASSEMBLER_FALSE                 0

#define ASSEMBLER_SUCCESS               0
#define ASSEMBLER_FAILURE               -1

#define ASSEMBLER_SUCCESS_MSG           "Programa gerado com sucesso!"
#define ASSEMBLER_ENULLPOINTER_MSG      "Referência inválida recebida no TAD ASSEMBLER."

#define ASSEMBLER_EALLOC                NULL
#define ASSEMBLER_EALLOC_MSG            "Falha na alocação do TAD ASSEMBLER."

#define ASSEMBLER_EUSER_INVALIDDIC_MSG	"Dicionário inconsistente."

#define ASSEMBLER_EUSER_EMPTYSRC		"O arquivo não possui intruções."

#define ASSEMBLER_EMOUNT                "Não é possível continuar."

#define ASSEMBLER_IGNORE1               "faca"
#define ASSEMBLER_IGNORE2               "va_para"
#define ASSEMBLER_IGNORE3               "senao"
#define ASSEMBLER_IGNORE4               "se"
#define ASSEMBLER_IGNORE5               "entao"
#define ASSEMBLER_IGNORE_QTD            5

#define ASSEMBLER_SEPARATOR             " \t"
#define ASSEMBLER_LABEL_TERMINATOR      ":"  //Terminador da label (deve aparecer na
#define ASSEMBLER_LABEL_TERMINATOR_CHR  ':'  //declaração de uma nova label)

#define ASSEMBLER_MACHINEDEC_RARROW		"->"
#define ASSEMBLER_MACHINEDEC_LARROW		"<-"
#define ASSEMBLER_MACHINEDEC_SEPARATORS	",: \t"
 
#define ASSEMBLER_COMMENT_CHRS			";#"


typedef struct _assembler
{
    ASMLOADER *     loader;
    ASMWRITER *     writer;
    DICTIONARY *    dic;
    REGISTERS *     regs;
    LISTA *         labels;
	uint64_t		instCounter;
} ASSEMBLER, ASM;

#endif
