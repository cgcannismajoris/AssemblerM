/*
 * ===========================================================================
 *
 * Nome do Arquivo:  asmError.h
 *
 *       Descricao:  Módulo para auxílio no tratamento de erro.
 *
 *          Versao:  1.0
 *       Criado em:  21/03/2015 08:44:13
 *         Revisao:  none
 *      Compilador:  gcc
 *
 *           Autor:  Gustavo Freitas de Amorim (), gustavofreitasamorim@gmail.com
 *     Organizacao:  VY Cannis Majoris
 *
 * ===========================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


/* -> char *asmError_new(uint32_t desc)
 * 
 * - DESCRIÇÃO: Instancia uma nova string para armazenamento de erros.
 *
 * - PARÂMETROS: 
 *      -> uint32_t desc: Tamanho da string a ser alocada.
 *
 * - RETORNO: String alocada para armazenar o erro.
 *   	-> Se NULL    - Erro na operação.
 *   	-> Se != NULL - Sucesso na operação.
 */
char *   asmError_new(uint32_t desc_length);


/* -> void asmError_free()
 * 
 * - DESCRIÇÃO: Destrói a string.
 *
 * - PARÂMETROS: void.
 *
 * - RETORNO: void.
 */
void     asmError_free();


/* -> void asmError_setDesc(const char *failureDesc)
 * 
 * - DESCRIÇÃO: Seta a mensagem a ser armazenada pela string de erros.
 *
 * - PARÂMETROS: 
 *      -> const char *failureDesc: Mensagem a ser gravada. 
 *
 * - RETORNO: void.
 */
void     asmError_setDesc(const char *failureDesc);


/* -> char *asmError_getDesc()
 * 
 * - DESCRIÇÃO: Retorna o ponteiro para a string de erros.
 *
 * - PARÂMETROS: void. 
 *
 * - RETORNO: Ponteiro para a string.
 */
char *   asmError_getDesc();

