/*
 * Nome do Arquivo:  tokens.h 
 *       Descricao:  TAD para armazenar os tokens detectados pelo
 *                   scaner do assembler.
 *
 * Exported functions from tokens.c.
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

#ifndef TOKENS_HEADER
#define TOKENS_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "../../asmError.h"

#define TOKENS_EALLOC               NULL
#define TOKENS_EALLOC_MSG           "Falha ao alocar memória no TAD TOKENS."

#define TOKENS_ETOKOVERFLOW         -1
#define TOKENS_ETOKOVERFLOW_MSG     "Estouro do limite de TOKENS."


typedef struct _tokens
{
    char **     tokens;    //Vetor onde são armazenados os tokens
    uint32_t    qtdUsed;   //Quantidade de tokens armazenados
    uint32_t    qtdMax;    //Quantidade máxima de tokens (tamanho do vetor char **tokens)
} TOKENS;


/* -> TOKENS *token_new(uint32_t qtd)
 * 
 * - DESCRIÇÃO: Instancia uma nova estrutura do tipo TOKENS para armazenar os 
 *   			tokens gerados pelo scanner.   
 *
 * - PARÂMETROS: 
 *      -> uint32_t qtd: Quantidade máxima de tokens que poderão ser armazenados
 *      				na estrutura.
 *
 * - RETORNO: Estrutura do tipo TOKENS instanciada.
 *   	-> Se NULL    - Erro na operação.
 *   	-> Se != NULL - Sucesso na operação.
 */
TOKENS *    token_new(uint32_t qtd);


/* -> void token_free(TOKENS *token)
 *
 * - DESCRIÇÃO: Destrói uma estrutura existente em memória.
 *
 * - PARÂMETROS: 
 *      -> TOKENS *token: Estrutura a ser destruída.
 *
 * - RETORNO: void.
 */
void        token_free(TOKENS *token);


/* -> uint32_t token_getQtd(TOKENS *token)
 * 
 * - DESCRIÇÃO: Retorna a quantidade de tokens armazenados na estrutura recebida.
 *
 * - PARÂMETROS: 
 *      -> TOKENS *token: Estrutura a ser utilizada na operação.
 *
 * - RETORNO: Quantidade de tokens armazenados.
 *   	-> Se 0    - Erro na operação.
 *   	-> Se != 0 - Sucesso na operação.
 */
uint32_t    token_getQtd(TOKENS *token);


/* -> char *token_getToken(TOKENS *token, uint32_t pos)
 * 
 * - DESCRIÇÃO: Retorna o token armazenado na estrutura em uma determinada posição.
 *
 * - PARÂMETROS: 
 *      -> TOKENS *token: Estrutura a ser utilizada na operação.
 *      -> uint32_t pos: Posição do token desejado.
 *
 * - RETORNO: Token armazenado na posição desejada.
 *   	-> Se NULL    - Erro na operação.
 *   	-> Se != NULL - Sucesso na operação.
 */
char *      token_getToken(TOKENS *token, uint32_t pos);


/* -> int token_addToken(TOKENS *token, char *t)
 * 
 * - DESCRIÇÃO: Adiciona um token na primeira posição disponível.
 *
 * - PARÂMETROS: 
 *      -> TOKENS *token: Estrutura a ter o token adicionado.
 *      -> char *t: Token a ser armazenado.
 *
 * - RETORNO: Estado da operação.
 *   	-> Se 0    - Sucesso.
 *   	-> Se -1   - Erro.
 */
int         token_addToken(TOKENS *token, char *t);


/* -> long int token_search(TOKENS *token, const char *search)
 * 
 * - DESCRIÇÃO: Procura por um token na estrura recebida.
 *
 * - PARÂMETROS: 
 *      -> TOKENS *token: Estrutura a ser utilizada na operação.
 *      -> const char *search: Chave da busca.
 *
 * - RETORNO: Posição do token.
 *   	-> Se >= 0 - Encontrou.
 *   	-> Se < 0  - Não encontrou.
 */
long int    token_search(TOKENS *token, const char *search);

/* -> int token_verifCommon(TOKENS *one, TOKENS *two)
 * 
 * - DESCRIÇÃO: Verifica se existem tokens em comum dentro 
 *   			das duas estruturas recebidas.
 *
 * - PARÂMETROS: 
 *      -> TOKENS *one: Estrutura a ser utilizada na operação.
 *      -> TOKENS *two: Estrutura a ser utilizada na operação.
 *
 * - RETORNO: Estado da operação.
 *   	-> Se 0    - Não possuem tokens em comum.
 *   	-> Se 1    - Possuem tokens em comum.
 */
int 		token_verifCommon(TOKENS *one, TOKENS *two);


/* -> int token_verifCommon(TOKENS *one, TOKENS *two)
 * 
 * - DESCRIÇÃO: Verifica se existem tokens repetidos armazenados 
 *   			na estrutura.
 *
 * - PARÂMETROS: 
 *      -> TOKENS *one: Estrutura a ser utilizada na operação.
 *
 * - RETORNO: Estado da operação.
 *   	-> Se 0    - Não possuem tokens repetidos.
 *   	-> Se 1    - Possuem tokens repetidos.
 */
int			token_verifRepetitions(TOKENS *one);

#endif /* TOKENS_HEADER */
