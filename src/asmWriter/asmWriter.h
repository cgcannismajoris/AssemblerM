/*
 * ===========================================================================
 *
 * Nome do Arquivo:  asmWriter.h
 *
 *       Descricao:  TAD para escrita do arquivo binário de saída do 
 *       			 assembler.
 *
 *          Versao:  1.0
 *       Criado em:  05/03/2015 17:14:00
 *         Revisao:  none
 *      Compilador:  gcc
 *
 *           Autor:  Cristian Costa Mello, Gustavo Freitas de Amorim
 *     Organizacao:  VY Cannis Majoris
 *
 * ===========================================================================
 */


#ifndef ASMWRITER_HEADER
#define ASMWRITER_HEADER

#include <stdio.h>

typedef struct _asmWriter
{
    FILE *file;
} ASMWRITER;

 
/* -> ASMWRITER *     asmWriter_new(const char *filename)
 * 
 * - DESCRIÇÃO: Instancia um novo write do assembler que será utilizado na
 *              escrita do arquivo binário.
 *   
 * - PARÂMETROS: 
 *      -> const char *filename: Nome do arquivo a ser utilizado.
 *
 * - RETORNO: Estrutura do tipo ASMWRITER instanciada.
 *   	-> Se NULL    - Erro na operação.
 *   	-> Se != NULL - Sucesso na operação.
 */
ASMWRITER *     asmWriter_new(const char *filename);


/* -> void asmWriter_free(ASMWRITER *asmWriter)
 * 
 * - DESCRIÇÃO: Destrói uma estrutura existente em memória.
 *
 * - PARÂMETROS: 
 *      -> ASMWRITER *asmWriter: Estrutura a ser destruída.
 *
 * - RETORNO: void.
 */
void            asmWriter_free(ASMWRITER *asmWriter);


/* -> void asmLoader_getNextInst(ASMLOADER *asmLoader)
 * 
 * - DESCRIÇÃO: Grava no arquivo a instrução binária recebida como parâmetro.
 *
 * - PARÂMETROS: 
 *      -> ASMWRITER *asmWriter: Estrutura a ser utilizada para a escrita da 
 *      instrução.
 *      -> INSTRUCTION *instruction: Instrução a ser escrita.
 *
 * - RETORNO: void.
 */
void            asmWriter_writeInst(ASMWRITER *asmWriter
                                    /*, INSTRUCTION *instruction*/);

#endif /* ASMWRITER_HEADER */
