/*
 * ==========================================================================
 *
 * Nome do Arquivo:  reg.h
 *
 *       Descricao:  TAD para armazenamento de um registrador declarado pelo
 *       			 programador.
 *
 *          Versao:  1.0
 *       Criado em:  20/03/2015 22:37:54
 *         Revisao:  none
 *      Compilador:  gcc
 *
 *           Autor:  Gustavo Freitas de Amorim (), gustavofreitasamorim@gmail.com
 *     Organizacao:  VY Cannis Majoris
 *
 * =========================================================================
 */


#ifndef REG_HEADER
#define REG_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "../../asmError.h"

#define REG_EALLOC          NULL
#define REG_EALLOC_MSG      "Falha ao alocar memória para REG."

typedef struct _reg
{
    char *      name;
} REG;


/* -> REG *reg_new(const char *name)
 * 
 * - DESCRIÇÃO: Instancia um novo registro de registrador declarado.
 *   
 * - PARÂMETROS: 
 *      -> const char *name: Nome dado ao registrador.
 *
 * - RETORNO: Estrutura do tipo REG instanciada.
 *   	-> Se NULL    - Erro na operação.
 *   	-> Se != NULL - Sucesso na operação.
 */
REG *       reg_new(const char *name);


/* -> void reg_free(REG *reg)
 * 
 * - DESCRIÇÃO: Destrói uma estrutura existente em memória.
 *
 * - PARÂMETROS: 
 *      -> REG *reg: Estrutura a ser destruída.
 *
 * - RETORNO: void.
 */
void        reg_free(REG *reg);


/* -> char *dicLoader_getNextInst(DICLOADER *dicLoader)
 * 
 * - DESCRIÇÃO: Retorna o nome dado ao registrador. 
 *   
 * - PARÂMETROS: 
 *      -> REG *reg: Estrutura a ser utilizada na leitura.
 *
 * - RETORNO: String contendo o nome dado ao registrador.
 */
char *      reg_getName(REG *reg);

#endif /* REG_HEADER */
