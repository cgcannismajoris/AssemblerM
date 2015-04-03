/*
 * ==========================================================================
 *
 * Nome do Arquivo:  assembler.h
 *
 *       Descricao:  TAD responsável pela montagem do arquivo binário.
 *
 *          Versao:  1.0
 *       Criado em:  15/03/2015 19:47:32
 *         Revisao:  none
 *      Compilador:  gcc
 *
 *           Autor:  Cristian Costa Mello, Gustavo Freitas de Amorim 
 *     Organizacao:  VY Cannis Majoris
 *
 * =========================================================================
 */


#ifndef ASSEMBLER_HEADER
#define ASSEMBLER_HEADER

#include "assembler_struct.h"
#include "assemblerAnalyser.h"


ASSEMBLER * assembler_new();
void        assembler_free(ASSEMBLER *asmr);

int 		assembler_assemble(ASSEMBLER *asmr, 
							   const char *src, 
							   const char *bin,
							   const char *dicFile, 
							   int *inputValues, 
							   uint32_t length);

static int  __assembler_assemble_makeLabels(ASSEMBLER *asmr);

 
#endif /* ASSEMBLER_HEADER */
