/*
 * Nome do Arquivo:  assembler.h
 *       Descricao:  TAD responsável pela montagem do arquivo binário.
 *
 * Exported functions from assembler.c.
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

#ifndef ASSEMBLER_HEADER
#define ASSEMBLER_HEADER

#include "assembler_struct.h"
#include "assemblerAnalyser.h"

/* -> ASSEMBLER *assembler_new()
 * 
 * - DESCRIÇÃO: Instancia um nova estrutura em memória.
 *   
 * - PARÂMETROS: void.
 *
 * - RETORNO: Estrutura do tipo ASSEMBLER instanciada.
 *   	-> Se NULL    - Erro na operação.
 *   	-> Se != NULL - Sucesso na operação.
 */
ASSEMBLER * assembler_new();


/* -> void assembler_free(ASSEMBLER *asmr)
 * 
 * - DESCRIÇÃO: Destrói uma estrutura existente em memória.
 *
 * - PARÂMETROS: 
 *      -> ASSEMBLER *asmr: Estrutura a ser destruída.
 *
 * - RETORNO: void.
 */
void        assembler_free(ASSEMBLER *asmr);


/* -> int assembler_assemble(ASSEMBLER *asmr, const char *src, const char *bin,
 *    const char *dicFile, int *inputValues, uint32_t length)
 * 
 * - DESCRIÇÃO: Realiza a operação de montagem do programa.
 *
 * - PARÂMETROS: 
 *      -> ASSEMBLER *asmr: Estrutura a ser utilizada na montagem.
 *      -> const char *src: Caminho do arquivo de código fonte.
 *      -> const char *bin: Caminho do arquivo binário a ser gerado.
 *      -> const char *dicFile: Caminho do arquivo de dicionário a ser utilizado.
 *      -> int *inputValues: Valores iniciais dos registradores de entrada.
 *      -> uint32_t length: Quantidade de valores iniciais.
 *
 * - RETORNO: Resultado da operação.
 *      -> Se 0    - Sucesso.
 *      -> Se != 0 - Erro.
 */
int 		assembler_assemble(ASSEMBLER *asmr, 
							   const char *src, 
							   const char *bin,
							   const char *dicFile, 
							   int *inputValues, 
							   uint32_t length);
 
#endif /* ASSEMBLER_HEADER */
