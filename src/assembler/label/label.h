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
 *           Autor:  Gustavo Freitas de Amorim (), gustavofreitasamorim@gmail.com
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


#define LABEL_LABELNAMELENGTH   20

#define LABEL_EALLOC			NULL

#define LABEL_STR_EALLOC		"Falha na alocação de memória no TAD LABEL."

typedef struct _label
{
    char *          labelName;
    uint64_t        labelLineNum;
    struct _label * next;
} LABEL;

LABEL *     label_new(const char *name, uint64_t num);
void        label_free(LABEL *label);

char *      label_getName(LABEL *label);
uint64_t    label_getLineNum(LABEL *label);

#endif /* LABEL_HEADER */
