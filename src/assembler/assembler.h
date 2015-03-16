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


#define MACHINE_MAX_REG              32

#define ASSEMBLER_SUCCESS            0
#define ASSEMBLER_ENULLPOINTER       -1

#define ASSEMBLER_SUCCESS_MSG        "Programa gerado com sucesso!"
#define ASSEMBLER_ENULLPOINTER_MSG   "Referência inválida recebida no TAD ASSEMBLER."

#define ASSEMBLER_EALLOC             NULL
#define ASSEMBLER_EALLOC_MSG         "Falha na alocação do TAD ASSEMBLER."


typedef struct _assembler
{
    ASMLOADER *     loader;
    ASMWRITER *     writer;
    DICTIONARY *    dic;
    REG **          reg;
    LISTA *         labels;

    uint64_t        qtdReg;

} ASSEMBLER, ASM;


ASSEMBLER * assembler_new();
void        assembler_free(ASSEMBLER *asmr);

int         assembler_assemble(ASSEMBLER *asmr,
                               const char *src,
                               const char *bin,
                               const char *dicFile);

static void __assembler_assemble_makeLabels(ASSEMBLER *asmr);

 
#endif /* ASSEMBLER_HEADER */
