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


uint64_t        assembler_searchLabel(ASSEMBLER *asmr, const char *label);

char **         assembler_makeIgnoreList();

void            assembler_freeIgnoreList(char **ignoreList);

int             assembler_labelJudge(char *label);

INSTRUCTION *   assembler_makeInst(ASSEMBLER *asmr, TOKENS *input,
                                   TOKENS *pattern, TOKENS *translation);

int             assembler_makeLabels(ASSEMBLER *asmr);

#endif
