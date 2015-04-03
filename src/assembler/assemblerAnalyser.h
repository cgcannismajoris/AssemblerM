/*
 * ===========================================================================
 *
 * Nome do Arquivo:  assemblerAnalyser.h
 *
 *       Descricao:  Módulo de co-processamento do montador.
 *
 *          Versao:  1.0
 *       Criado em:  21/03/2015 10:13:21
 *         Revisao:  none
 *      Compilador:  gcc
 *
 *           Autor:  Cristian Costa Mello, Gustavo Freitas de Amorim
 *     Organizacao:  VY Cannis Majoris
 *
 * ===========================================================================
 */

#ifndef ASSEMBLERANALYSER_H
#define ASSEMBLERANALYSER_H

#include "assembler_struct.h"

#define ASSEMBLERANALYSER_EALLOC		NULL
#define ASSEMBLERANALYSER_EALLOC_MSG	"Falha ao alocar memória no módulo ASSEMBLERANALYSER."

#define ASSEMBLERANALYSER_EUSER_INVALIDMACHINE ASSEMBLER_FAILURE
#define ASSEMBLERANALYSER_EUSER_INVALIDMACHINE_MSG "Definição inválida da máquina."

#define ASSEMBLERANALYSER_EUSER_DOUBLE_DECLARATION ASSEMBLER_FAILURE
#define ASSEMBLERANALYSER_EUSER_DOUBLE_DECLARATION_MSG "Declaração duplicada de registradores."

#define ASSEMBLERANALYSER_EUSER_REGNOTDEC		ASSEMBLER_FAILURE
#define ASSEMBLERANALYSER_EUSER_REGNOTDEC_MSG 	"Registrador não declarado."

uint64_t        assembler_searchLabel(ASSEMBLER *asmr, const char *label);

char **			assembler_makeStrVector(int qtd, ...);

void 			assembler_freeStrVector(char **strVector);

int             assembler_labelJudge(char *label);

void			__assembler_makeRegisters_insert(ASSEMBLER *asmr, TOKENS *tokens, uint8_t block_type);

int 			assembler_makeRegisters(ASSEMBLER *asmr);

INSTRUCTION *   assembler_makeInst(ASSEMBLER *asmr, TOKENS *input,
                                   TOKENS *pattern, TOKENS *translation);

int             assembler_makeLabels(ASSEMBLER *asmr);

#endif
