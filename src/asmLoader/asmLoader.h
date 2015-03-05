/*
 * ==========================================================================
 *
 * Nome do Arquivo:  asmLoader.h
 *
 *       Descricao:  TAD para leitura do arquivo contendo o código fonte 
 *       			 escrito pelo programador.
 *
 *          Versao:  1.0
 *       Criado em:  05/03/2015 16:52:48
 *         Revisao:  none
 *      Compilador:  gcc
 *
 *           Autor:  Cristian Costa Mello, Gustavo Freitas de Amorim
 *     Organizacao:  VY Cannis Majoris
 *
 * =========================================================================
 */


#ifndef ASMLOADER_HEADER
#define ASMLOADER_HEADER

#include <stdio.h>  /* para I/O */

typedef struct _asmLoader
{
    FILE *file; //Ponteiro para o arquivo a ser lido.
} ASMLOADER;


/* -> ASMLOADER *asmLoader_new(const char *filename)
 * 
 * - DESCRIÇÃO: Instancia um novo loader do assembler que será utilizado na leitura
 *   de instruções escritas pelo programador.
 *
 * - PARÂMETROS: 
 *      -> const char *filename: Nome do arquivo a ser utilizado.
 *
 * - RETORNO: Estrutura do tipo ASMLOADER instanciada.
 *   	-> Se NULL    - Erro na operação.
 *   	-> Se != NULL - Sucesso na operação.
 */
ASMLOADER *     asmLoader_new(const char *filename);


/* -> void asmLoader_free(ASMLOADER *asmLoader)
 * 
 * - DESCRIÇÃO: Destrói uma estrutura existente em memória.
 *
 * - PARÂMETROS: 
 *      -> ASMLOADER *asmLoader: Estrutura a ser destruída.
 *
 * - RETORNO: void.
 */
void            asmLoader_free(ASMLOADER *asmLoader);


/* -> void asmLoader_getNextInst(ASMLOADER *asmLoader)
 * 
 * - DESCRIÇÃO: Carrega a próxima instrução escrita pelo programador presente no 
 *   arquivo.
 *   	- Se nenhuma intrução foi lida até o momento, carrega a primeira.
 *   	- Se ja leu alguma, carrega a intrução subsequênte à anteriormente carregada.
 *
 * - PARÂMETROS: 
 *      -> ASMLOADER *asmLoader: Estrutura a ser utilizada para a leitura da 
 *      instrução.
 *
 * - RETORNO: Instrução escrita pelo programador carregada.
 *   	-> Se NULL    - Erro na operação.
 *   	-> Se != NULL - Sucesso na operação.
 */
char *         asmLoader_getNextInst(ASMLOADER *asmLoader);


#endif /* ASMLOADER_HEADER */
