/* scanner.h
 * SCANNER.
 */
#ifndef SCANNER_HEADER
#define SCANNER_HEADER

#include "tokens/tokens.h" /* incluir o TAD TOKENS (Conjunto de TOKENS) */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#define SCANNER_IGNOREFACASTR       "faca"
#define SCANNER_IGNOREVAPARASTR     "va_para"
#define SCANNER_DELIMS              " :"
#define SCANNER_SPCLS               0x20        /* Space Bar*/

#define SCANNER_ERROR               NULL
#define SCANNER_ERROR_MSG           "Falha na operação de scanner."


TOKENS *scanner_scan(char *sentence);

#endif /* SCANNER_HEADER */
