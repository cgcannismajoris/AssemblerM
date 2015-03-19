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

#include "../asmLoader/asmLoader.h"         /* incluir o TAD ASMLOADER */
#include "../asmWriter/asmWriter.h"         /* incluir o TAD ASMWRITER */
#include "../instruction/instruction.h"     /* incluir o TAD INSTRUCTION */
#include "../dictionary/dictionary.h"       /* incluir o TAD DICTIONARY */
#include "reg/reg.h"                        /* incluir o TAD REG */
#include "label/label.h"                    /* incluir o TAD LABEL */
#include "../scanner/scanner.h"             /* incluir o TAD SCANNER */
#include "../linkedList/linkedList.h"		/* incluir o TAD LISTA */


#define ASSEMBLER_TRUE               1
#define ASSEMBLER_FALSE              0

#define MACHINE_MAX_REG              32

#define ASSEMBLER_SUCCESS            0
#define ASSEMBLER_ENULLPOINTER       -1

#define ASSEMBLER_SUCCESS_MSG        "Programa gerado com sucesso!"
#define ASSEMBLER_ENULLPOINTER_MSG   "Referência inválida recebida no TAD ASSEMBLER."

#define ASSEMBLER_EALLOC             NULL
#define ASSEMBLER_EALLOC_MSG         "Falha na alocação do TAD ASSEMBLER."

#define ASSEMBLER_IGNORE1			 "faca"
#define ASSEMBLER_IGNORE2			 "va_para"

#define ASSEMBLER_IGNORE_QTD		 2

#define ASSEMBLER_SEPARATOR			 " "

#define ASSEMBLER_LABEL_TERMINATOR	 ":" //Terminador da label (deve aparecer na 
									     //declaração de uma nova label)

typedef struct _assembler
{
    ASMLOADER *     loader;
    ASMWRITER *     writer;
    DICTIONARY *    dic;
    REG **          reg;
    LISTA *         labels;

    long int        qtdReg;
	uint64_t		instCounter;
} ASSEMBLER, ASM;


ASSEMBLER * assembler_new();
void        assembler_free(ASSEMBLER *asmr);

int         assembler_assemble(ASSEMBLER *asmr,
                               const char *src,
                               const char *bin,
                               const char *dicFile);

long int assembler_regSearch(ASSEMBLER *asmr, char *name);
long int assembler_addReg(ASSEMBLER *asmr, char *regName);
static int __assembler_assemble_makeLabels(ASSEMBLER *asmr);

 
#endif /* ASSEMBLER_HEADER */
