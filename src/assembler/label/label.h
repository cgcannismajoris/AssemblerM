/*
 * ==========================================================================
 *
 * Nome do Arquivo:  label.h
 *
 *       Descricao:  TAD de lista encadeada simples de labels para auxíliar o
 *       			 assembler na indexação de labels.
 *
 *          Versao:  1.0
 *       Criado em:  09/03/2015 18:38:19
 *         Revisao:  none
 *      Compilador:  gcc
 *
 *           Autor:  Cristian Costa Mello, Gustavo Freitas de Amorim 
 *     Organizacao:  VY Cannis Majoris
 *
 * =========================================================================
 */

#ifndef LABEL_HEADER
#define LABEL_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


#define LABEL_EALLOC			NULL

#define LABEL_STR_EALLOC		"Falha na alocação de memória no TAD LABEL."



typedef struct _label
{
    char *          labelName;    //Nome da label;
    uint64_t        labelLineNum; //Linha onde a label foi declarada;
} LABEL;


/* -> LABEL *label_new(const char *name, uint64_t num)
 * 
 * - DESCRIÇÃO: Instancia uma nova estrutura que armazena uma label declarada no
 *   código fonte do programa.
 *
 * - PARÂMETROS: 
 *      -> const char *name: Nome da label.
 *      -> uint64_t num: Número da linha onde a label foi declarada.
 *
 * - RETORNO: Estrutura do tipo LABEL instanciada.
 *   	-> Se LABEL_EALLOC     - Erro na operação.
 *   	-> Se !=  LABEL_EALLOC - Sucesso na operação.
 */
LABEL *     label_new(const char *name, uint64_t num);


/* -> void label_free(LABEL *label)
 *
 * - DESCRIÇÃO: Destrói uma estrutura do tipo LABEL existente em memória.
 *
 * - PARÂMETROS: 
 *      -> LABEL *label: Estrutura a ser destruída.
 *
 * - RETORNO: void.
 */
void        label_free(LABEL *label);


/* -> char *label_getName(LABEL *label)
 * 
 * - DESCRIÇÃO: Retorna o nome da label armazenado na estrutura recebida como
 *   parâmetro.
 *
 * - PARÂMETROS: 
 *      -> LABEL *label: Estrutura a ser utilizada na operação. 
 *
 * - RETORNO: Nome armazenado na estrutura.
 *   	-> Se NULL       - Erro na operação.
 *   	-> Se != NULL    - Sucesso na operação.
 */
char *      label_getName(LABEL *label);


/* -> uint64_t label_getLineNum(LABEL *label)
 * 
 * - DESCRIÇÃO: Retorna o número da linha armazenado na estrutura recebida como
 *   parâmetro.
 *
 * - PARÂMETROS: 
 *      -> LABEL *label: Estrutura a ser utilizada na operação. 
 *
 * - RETORNO: Nome armazenado na estrutura.
 *   	-> Se 0       - Erro na operação.
 *   	-> Se != 0    - Sucesso na operação.
 */
uint64_t    label_getLineNum(LABEL *label);

#endif /* LABEL_HEADER */
