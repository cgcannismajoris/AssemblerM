/*
 * ==========================================================================
 *
 * Nome do Arquivo:  tokens.h
 *
 *       Descricao:  TAD para armazenar os tokens detectados pelo
 *       			 scaner do assembler.
 *
 *          Versao:  1.0
 *       Criado em:  11/03/2015 14:57:04
 *         Revisao:  none
 *      Compilador:  gcc
 *
 *           Autor:  Cristian Costa Mello, Gustavo Freitas de Amorim
 *     Organizacao:  VY Cannis Majoris
 *
 * =========================================================================
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


/* -> TOKENS *token_new(uint8_t qtd)
 * 
 * - DESCRIÇÃO: Instancia uma nova estrutura do tipo TOKENS para armazenar os 
 *   			tokens gerados pelo scanner.   
 *
 * - PARÂMETROS: 
 *      -> uint8_t qtd: Quantidade máxima de tokens que poderão ser armazenados
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


/* -> uint8_t token_getQtd(TOKENS *token)
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


/* -> char *token_getToken(TOKENS *token, uint8_t pos)
 * 
 * - DESCRIÇÃO: Retorna o token armazenado na estrutura em uma determinada posição.
 *
 * - PARÂMETROS: 
 *      -> TOKENS *token: Estrutura a ser utilizada na operação.
 *      -> uint8_t pos: Posição do token desejado.
 *
 * - RETORNO: Token armazenado na posição desejada.
 *   	-> Se NULL    - Erro na operação.
 *   	-> Se != NULL - Sucesso na operação.
 */
char *      token_getToken(TOKENS *token, uint32_t pos);


/* -> void token_addToken(TOKENS *token, char *t)
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


long int    token_search(TOKENS *token, const char *search);

/* -> int token_searchCommonTokens(TOKENS *one, TOKENS *two)
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

#endif /* TOKENS_HEADER */
