/* scanner.h
 * SCANNER.
 */
#ifndef SCANNER_HEADER
#define SCANNER_HEADER

#include "tokens/tokens.h" /* incluir o TAD TOKENS (Conjunto de TOKENS) */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


TOKENS *scanner_scan(char *sentence);

#endif /* SCANNER_HEADER */
