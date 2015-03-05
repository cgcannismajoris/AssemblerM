/* asmLoader.h
 * TAD do Buffer de Leitura de instrução de um arquivo de texto de entrada.
 */
#ifndef ASMLOADER_HEADER
#define ASMLOADER_HEADER

#include <stdio.h>  /* para I/O */

typedef struct _asmLoader
{
    FILE *file;
} ASMLOADER;

ASMLOADER *     asmLoader_new(const char *filename);
void            asmLoader_free(ASMLOADER *asmLoader);
void            asmLoader_getNextInst(ASMLOADER *asmLoader);

#endif /* ASMLOADER_HEADER */
