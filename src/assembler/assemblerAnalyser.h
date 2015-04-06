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

#define ASSEMBLERANALYSER_EUSER_NOINPUT_MSG		"Registradores de entrada não declarados."

#define ASSEMBLERANALYSER_EUSER_NOOUTPUT_MSG	"Registradores de saída não declarados."

/* -> uint64_t assembler_searchLabel(ASSEMBLER *asmr, const char *label)
 * 
 * - DESCRIÇÃO: Pesquisa uma label na estrutura recebida.
 *
 * - PARÂMETROS: 
 *      -> ASSEMBLER *asmr: Estrutura a ser utilizada na operação.
 *      -> const char *label: Label a ser pesquisada.
 *
 * - RETORNO: Posição da label encontrada.
 *      -> Se 0    - Não encontrou.
 *      -> Se != 0 - Encontrou.
 */
uint64_t        assembler_searchLabel(ASSEMBLER *asmr, const char *label);


/* -> char **assembler_makeStrVector(int qtd, ...)
 * 
 * - DESCRIÇÃO: Cria um vetor de strings com a última posição igual a NULL.
 *
 * - PARÂMETROS: 
 *      -> int qtd: Quantidade de argumentos.
 *      -> ...: Strings a serem armazenadas pelo vetor.
 *
 * - RETORNO: Vetor de strings gerado.
 *      -> Se NULL    - Erro.
 *      -> Se != NULL - Sucesso.
 */
char **			assembler_makeStrVector(int qtd, ...);


/* -> void assembler_freeStrVector(char **strVector)
 * 
 * - DESCRIÇÃO: Destrói um vetor de strings terminado em NULL.
 *
 * - PARÂMETROS: 
 *      -> char **strVector: Vetor a ser destruído.
 *
 * - RETORNO: void.
 */
void 			assembler_freeStrVector(char **strVector);


/* -> int assembler_labelJudge(char *label)
 * 
 * - DESCRIÇÃO: Verifica se a string recebida respeita o padrão estabelecido
 *   para uma label (termina em ':').
 *
 * - PARÂMETROS: 
 *      -> char *label: String a ser verificada.
 *
 * - RETORNO: Resultado da verificação.
 *      -> Se 1 - Atende ao padrão.
 *      -> Se 0 - Não atende ao padrão.
 */
int             assembler_labelJudge(char *label);


/* -> void assembler_removeComment(char *inst)
 * 
 * - DESCRIÇÃO: Remove um comentário de uma string a partir da
 *   definição ASSEMBLER_COMMENT_CHRS.
 *
 * - PARÂMETROS: 
 *      -> char *inst: String a ser manipulada.
 *
 * - RETORNO: void.
 */
void assembler_removeComment(char *inst);


/* -> static void 	__assembler_makeRegisters_insert(ASSEMBLER *asmr, TOKENS *tokens, 
 *    uint8_t block_type)
 * 
 * - DESCRIÇÃO: Instancia e armazena os registradores na lista de registradores do 
 *   montador recebido como argumento.
 *
 * - PARÂMETROS: 
 *      -> ASSEMBLER *asmr: Montador que irá receber os registradores.
 *      -> TOKENS *tokens: Tokens contendo o nome dos registradores a serem instanciados.
 *      -> uint8_t block_type: Tipo do bloco (input ou output).
 *
 * - RETORNO: void.
 */
static void 	__assembler_makeRegisters_insert(ASSEMBLER *asmr, TOKENS *tokens, 
										uint8_t block_type);


/* -> int assembler_makeRegisters(ASSEMBLER *asmr)
 * 
 * - DESCRIÇÃO: Gera a lista de registradores declarados no cabeçalho do código fonte
 *   aberto pelo montador recebido como argumento.
 *
 * - PARÂMETROS: 
 *      -> ASSEMBLER *asmr: Montador que irá receber os registradores.
 *
 * - RETORNO: Estado da operação.
 *      -> Se 0    - Sucesso.
 *      -> Se != 0 - Erro.
 */
int 			assembler_makeRegisters(ASSEMBLER *asmr);


/* -> int assembler_makeHeader(ASSEMBLER *asmr, int *inputList, uint32_t length)
 * 
 * - DESCRIÇÃO: Gera e grava no arquivo binário o cabeçalho de inicialização do 
 *   programa.
 *
 * - PARÂMETROS: 
 *      -> ASSEMBLER *asmr: Montador que irá ser utilizado.
 *      -> int *inputList: Valores iniciais dos registradores de entrada.
 *      -> uint32_t length: Quantidade de valores iniciais.
 *
 * - RETORNO: Estado da operação.
 *      -> Se 0    - Sucesso.
 *      -> Se != 0 - Erro.
 */
int 			assembler_makeHeader(ASSEMBLER *asmr, int *inputList, 
										uint32_t length);


/* -> INSTRUCTION *assembler_makeInst(ASSEMBLER *asmr, TOKENS *input, TOKENS *pattern, TOKENS *translation)
 * 
 * - DESCRIÇÃO: Gera a próxima instrução a ser armazenada no arquivo binário.
 *
 * - PARÂMETROS: 
 *      -> ASSEMBLER *asmr: Montador que irá ser utilizado.
 *      -> TOKENS *input: Tokens gerados a partir do código fonte.
 *      -> TOKENS *pattern: Padrão da instrução fornecido pelo dicionário.
 *      -> TOKENS *translation: Tradução do padrão de instrução fornecido pelo dicionário.
 *
 * - RETORNO: Instrução gerada.
 *      -> Se NULL    - Erro.
 *      -> Se != NULL - Sucesso.
 */
INSTRUCTION *   assembler_makeInst(ASSEMBLER *asmr, TOKENS *input,
										TOKENS *pattern, TOKENS *translation);


/* -> int assembler_makeLabels(ASSEMBLER *asmr)
 * 
 * - DESCRIÇÃO: Gera a lista de labels declaras no arquivo de código fonte.
 *
 * - PARÂMETROS: 
 *      -> ASSEMBLER *asmr: Montador que irá receber as labels.
 *
 * - RETORNO: Estado da operação.
 *      -> Se 0    - Sucesso.
 *      -> Se != 0 - Erro.
 */
int             assembler_makeLabels(ASSEMBLER *asmr);

#endif
