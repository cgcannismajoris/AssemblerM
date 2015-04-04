/*
 * Nome do Arquivo:  assemblerAnalyser.h
 *       Descricao:  Módulo de co-processamento do montador.
 *
 * Exported functions from assemblerAnalyser.c.
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
#ifndef ASSEMBLERANALYSER_H
#define ASSEMBLERANALYSER_H

#include "assembler_struct.h"

#define ASSEMBLERANALYSER_EALLOC				NULL
#define ASSEMBLERANALYSER_EALLOC_ID				-1
#define ASSEMBLERANALYSER_EALLOC_MSG			"Falha ao alocar memória no módulo ASSEMBLERANALYSER."

#define ASSEMBLERANALYSER_EUSER_INVMAC 			ASSEMBLER_FAILURE
#define ASSEMBLERANALYSER_EUSER_INVMAC_MSG 		"Definição inválida da máquina."

#define ASSEMBLERANALYSER_EUSER_DOUBDEC 		ASSEMBLER_FAILURE
#define ASSEMBLERANALYSER_EUSER_DOUBDEC_MSG 	"Declaração duplicada de registradores."

#define ASSEMBLERANALYSER_EUSER_REGNOTDEC		ASSEMBLER_FAILURE
#define ASSEMBLERANALYSER_EUSER_REGNOTDEC_MSG 	"Registrador não declarado."

#define ASSEMBLERANALYSER_EUSER_DUPLABEL		0
#define ASSEMBLERANALYSER_EUSER_DUPLABEL_MSG	"Declaração de label duplicada."

#define ASSEMBLERANALYSER_EUSER_INVLABEL		0
#define ASSEMBLERANALYSER_EUSER_INVLABEL_MSG	"Declaração de label inválida."

#define ASSEMBLERANALYSER_EUSER_EXCESSARGS		ASSEMBLER_FAILURE
#define ASSEMBLERANALYSER_EUSER_EXCESSARGS_MSG	"Excesso de argumentos."

#define ASSEMBLERANALYSER_EUSER_LESSARGS		ASSEMBLER_FAILURE
#define ASSEMBLERANALYSER_EUSER_LESSARGS_MSG	"Quantidade insuficiente de argumentos."

uint64_t        assembler_searchLabel(ASSEMBLER *asmr, const char *label);

char **			assembler_makeStrVector(int qtd, ...);

void 			assembler_freeStrVector(char **strVector);

int             assembler_labelJudge(char *label);

static void 	__assembler_makeRegisters_insert(ASSEMBLER *asmr, TOKENS *tokens, 
										uint8_t block_type);
	
int 			assembler_makeRegisters(ASSEMBLER *asmr);

int 			assembler_makeHeader(ASSEMBLER *asmr, int *inputList, 
										uint32_t length);

INSTRUCTION *   assembler_makeInst(ASSEMBLER *asmr, TOKENS *input,
										TOKENS *pattern, TOKENS *translation);

int             assembler_makeLabels(ASSEMBLER *asmr);

#endif
