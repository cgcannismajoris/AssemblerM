/*
 * ===========================================================================
 *
 * Nome do Arquivo:  assembler_struct.h
 *
 *       Descricao:  Declaração da estrutura principal do assembler.
 *
 *          Versao:  1.0
 *       Criado em:  21/03/2015 10:38:09
 *         Revisao:  none
 *      Compilador:  gcc
 *
 *           Autor:  Gustavo Freitas de Amorim (), gustavofreitasamorim@gmail.com
 *     Organizacao:  VY Cannis Majoris
 *
 * ===========================================================================
 */

#ifndef ASSEMBLER_STRUCT_H
#define ASSEMBLER_STRUCT_H

#include "../asmLoader/asmLoader.h"         /* incluir o TAD ASMLOADER */
#include "../asmWriter/asmWriter.h"         /* incluir o TAD ASMWRITER */
#include "../instruction/instruction.h"     /* incluir o TAD INSTRUCTION */
#include "../dictionary/dictionary.h"       /* incluir o TAD DICTIONARY */
#include "registers/registers.h"            /* incluir o TAD REGISTERS */
#include "label/label.h"                    /* incluir o TAD LABEL */
#include "../scanner/scanner.h"             /* incluir o TAD SCANNER */
#include "../linkedList/linkedList.h"		/* incluir o TAD LISTA */

#include <stdarg.h>

#define ASSEMBLER_TRUE                  1
#define ASSEMBLER_FALSE                 0

#define MACHINE_MAX_REG                 32

#define ASSEMBLER_SUCCESS               0
#define ASSEMBLER_FAILURE               -1

#define ASSEMBLER_SUCCESS_MSG           "Programa gerado com sucesso!"
#define ASSEMBLER_ENULLPOINTER_MSG      "Referência inválida recebida no TAD ASSEMBLER."

#define ASSEMBLER_EALLOC                NULL
#define ASSEMBLER_EALLOC_MSG            "Falha na alocação do TAD ASSEMBLER."

#define ASSEMBLER_EUSER_INVALIDDIC_MSG	"Dicionário inconsistente."

#define ASSEMBLER_EMOUNT                "Não é possível continuar."

#define ASSEMBLER_IGNORE1               "faca"
#define ASSEMBLER_IGNORE2               "va_para"

#define ASSEMBLER_IGNORE_QTD            2

#define ASSEMBLER_SEPARATOR             " "

#define ASSEMBLER_LABEL_TERMINATOR      ":"  //Terminador da label (deve aparecer na
										     //declaração de uma nova label)

#define ASSEMBLER_MACHINEDEC_RARROW		"->"
#define ASSEMBLER_MACHINEDEC_LARROW		"<-"

#define ASSEMBLER_MACHINEDEC_SEPARATORS	",:"
 

typedef struct _assembler
{
    ASMLOADER *     loader;
    ASMWRITER *     writer;
    DICTIONARY *    dic;
    REGISTERS *     regs;
    LISTA *         labels;
	uint64_t		instCounter;
} ASSEMBLER, ASM;

#endif
