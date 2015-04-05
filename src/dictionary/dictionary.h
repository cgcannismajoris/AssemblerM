/*
 * Nome do Arquivo:  dictionary.h
 *       Descricao:  TAD para manipulação dos verbetes reconhecidos pelo 
 *                   assembler.
 *
 * Exported functions from dictionary.c.
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

#ifndef DICTIONARY_HEADER
#define DICTIONARY_HEADER

#include <stdlib.h>
#include <stdint.h>

#include "../asmError.h"
#include "entry/entry.h"            /* incluir o TAD ENTRY */
#include "dicLoader/dicLoader.h"    /* incluir o TAD DICLOADER */
#include "dicWriter/dicWriter.h"    /* incluir o TAD DICWRITER */


#define DICTIONARY_EALLOC               NULL
#define DICTIONARY_EALLOC_MSG           "Falha ao alocar estrutura DICTIONARY."

#define DICTIONARY_ELOAD                -1
#define DICTIONARY_ELOAD_MSG            "Falha ao carregar o dicionário."

#define DICTIONARY_BSEARCH_NOTFOUND     NULL


typedef struct _dictionary
{
    DICLOADER * loader;	  //Loader do dicionário
    ENTRY **    verbetes; //Lista de verbetes do dicionário
    uint64_t    qtdEntry; //Quantidade de verbetes
} DICTIONARY;


/* -> DICTIONARY *dic_new(const char *filename)
 * 
 * - DESCRIÇÃO: Instancia um novo dicionário que será utilizado na
 *              tradução da linguagem.
 *   
 * - PARÂMETROS: 
 *      -> const char *filename: Nome do arquivo a ser utilizado no carregamento
 *         do dicionário.
 *
 * - RETORNO: Estrutura do tipo DICTIONARY instanciada.
 *   	-> Se NULL    - Erro na operação.
 *   	-> Se != NULL - Sucesso na operação.
 */
DICTIONARY *    dic_new(const char *filename);


/* -> void dic_free(DICTIONARY *dic)
 * 
 * - DESCRIÇÃO: Destrói uma estrutura existente em memória.
 *
 * - PARÂMETROS: 
 *      -> DICTIONARY *dic: Estrutura a ser destruída.
 *
 * - RETORNO: void.
 */
void            dic_free(DICTIONARY *dic);


/* -> static int __dic_search_compar(const void *one, const void *two)
 * 
 * - DESCRIÇÃO: Método auxiliar da pesquisa de verbetes do dicionário.
 *
 * - PARÂMETROS: 
 *      -> const void *one: String enviada à pesquisa.
 *      -> const void *two: Estrutura ENTRY a ser comparada.
 *
 * - RETORNO: Resultado da comparação.
 *      -> Se +1 - O primeiro deve vir antes do segundo.
 *   	-> Se  0 - Elementos correspondem.
 *   	-> Se -1 - O segundo deve vir antes do primeiro.
 */
static int __dic_search_compar(const void *one, const void *two);


/* -> ENTRY *dic_search(DICTIONARY *dic, const char *nomeOperacao)
 * 
 * - DESCRIÇÃO: Busca um nome da operação dentro dos padrões de instrução 
 *              cadastrados.
 *
 * - PARÂMETROS: 
 *      -> DICTIONARY *dic: Estrutura a ser utilizada na busca.
 *      -> const char *nomeOperacao: Nome a ser pesquisado.
 *
 * - RETORNO: Estrutura do tipo ENTRY resultante do processo de busca.
 *   	-> Se NULL    - Não encontrado.
 *   	-> Se != NULL - Encontrado.
 */
ENTRY *         dic_search(DICTIONARY *dic, const char *nomeOperacao);


/* -> int dic_save(DICTIONARY *dic, const char *filename)
 * 
 * - DESCRIÇÃO: Salva o dicionário em um arquivo.
 *
 * - PARÂMETROS: 
 *      -> DICTIONARY *dic: Estrutura a ser utilizada na busca.
 *      -> const char *filename: Nome do arquivo a ser salvo.
 *
 * - RETORNO: Estado da operação.
 *      -> Se 0    - Erro na operação.
 *      -> Se != 0 - Sucesso na operação.
 */
int             dic_save(DICTIONARY *dic, const char *filename);


/* -> static int __dic_load_compar(const void *one, const void *two)
 * 
 * - DESCRIÇÃO: Método de comparação auxiliar na ordenação dos verbetes do dicionário.
 *
 * - PARÂMETROS: Estruturas a serem comparadas. 
 *      -> const void *one: Estrutura ENTRY a ser comparada.
 *      -> const void *two: Estrutura ENTRY a ser comparada.
 *
 * - RETORNO: Resultado da comparação.
 *      -> Se +1 - O primeiro deve vir antes do segundo.
 *   	-> Se  0 - Elementos correspondem.
 *   	-> Se -1 - O segundo deve vir antes do primeiro.
 */
static int __dic_load_compar(const void *one, const void *two);


/* -> int dic_load(DICTIONARY *dic)
 * 
 * - DESCRIÇÃO: Carrega o dicionário presente em um arquivo.
 *
 * - PARÂMETROS: 
 *      -> DICTIONARY *dic: Estrutura a ser utilizada no carregamento.
 *
 * - RETORNO: Estado da operação.
 *      -> Se 0    - Erro na operação.
 *      -> Se != 0 - Sucesso na operação.
 *
 * - OBSERVAÇÃO: O arquivo de entrada é aberto na criação do dicionário, ou seja, 
 *   na execução da função dic_new().
 */
int             dic_load(DICTIONARY *dic);

#endif /* DICIONARY_HEADER */
