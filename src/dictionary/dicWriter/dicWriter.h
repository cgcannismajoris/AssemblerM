/*
 * ==========================================================================
 *
 * Nome do Arquivo:  dicWriter.h
 *
 *       Descricao:  TAD para a escrita do arquivo de padrões e opcodes
 *                   aceitos pelo assembler.
 *
 *          Versao:  1.0
 *       Criado em:  07/03/2015 17:50:06
 *         Revisao:  none
 *      Compilador:  gcc
 *
 *           Autor:  Cristian Costa Mello, Gustavo Freitas de Amorim
 *     Organizacao:  VY Cannis Majoris
 *
 * =========================================================================
 */


#ifndef DICWRITER_HEADER
#define DICWRITER_HEADER

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define DICWRITER_SUCCESS        0      /* Sucesso na operação (não vale para ponteiros) */
#define DICWRITER_EWRITE        -1      /* Falha ao escrever no arquivo */
#define DICWRITER_ENULLPOINTER  -2      /* Ponteiro nulo recebido */
#define DICWRITER_EALLOC		NULL    /* FALHA DE ALOCAÇÃO */


#define DICWRITER_EWRITE_MSG        "Falha ao escrever no arquivo em DICWRITER."
#define DICWRITER_ENULLPOINTER_MSG  "Ponteiro nulo recebido em DICWRITER."
#define DICWRITER_EALLOC_MSG        "Falha na alocação da estrutura DICWRITER."


typedef struct _dicWriter
{
    FILE *file; //Ponteiro para o arquivo utilizado nas operações de escrita.
} DICWRITER;


/* -> DICWRITER *dicWriter_new(const char *filename)
 * 
 * - DESCRIÇÃO: Instancia um novo writer do assembler que será utilizado na
 *              escrita do arquivo de traduções da linguagem.
 *   
 * - PARÂMETROS: 
 *      -> const char *filename: Nome do arquivo a ser utilizado.
 *
 * - RETORNO: Estrutura do tipo DICWRITER instanciada.
 *   	-> Se NULL    - Erro na operação.
 *   	-> Se != NULL - Sucesso na operação.
 */
DICWRITER *     dicWriter_new(const char *filename);


/* -> void dicWriter_free(DICWRITER *dicWriter)
 * 
 * - DESCRIÇÃO: Destrói uma estrutura existente em memória.
 *
 * - PARÂMETROS: 
 *      -> DICWRITER *dicWriter: Estrutura a ser destruída.
 *
 * - RETORNO: void.
 */
void            dicWriter_free(DICWRITER *dicWriter);


/* -> void dicWriter_writeQtdInst(DICWRITER *dicWriter, uint64_t num)
 * 
 * - DESCRIÇÃO: Grava no arquivo a instrução binária recebida como parâmetro.
 *
 * - PARÂMETROS: 
 *      -> DICWRITER *dicWriter: Estrutura a ser utilizada para a escrita da 
 *      quantidade de instruções.
 *      -> uint64_t num: Quantidade de instruções a ser escrita.
 *
 * - RETORNO: Estado da operação.
 *      -> Se 0                      - Sucesso na operação.
 *      -> Se DICWRITER_ENULLPOINTER - Erro na operação.
 */
int             dicWriter_writeQtdInst(DICWRITER *dicWriter, uint64_t num);


/* -> void dicWriter_writeInst(DICWRITER *dicWriter, const char *instructionPattern, 
 *                               uint32_t opcode)
 * 
 * - DESCRIÇÃO: Grava no arquivo o padrão de instrução recebida como parâmetro.
 *
 * - PARÂMETROS: 
 *      -> ASMWRITER *asmWriter: Estrutura a ser utilizada para a escrita da 
 *      instrução.
 *      -> const char *instructionPattern: Padrão de instrução a ser escrito.
 *      -> uint32_t opcode: Opcode correspondente ao padrão recebido.
 *
 * - RETORNO: Estado da operação.
 *      -> Se 0                      - Sucesso na operação.
 *      -> Se DICWRITER_ENULLPOINTER - Erro na peração.
 */
int             dicWriter_writeInst(DICWRITER *dicWriter, 
										const char *instructionPattern,
                                    		uint32_t opcode);

#endif /* DICWRITER_HEADER */
