/* asmWriter.h
 * TAD do Buffer de Escrita de instrução em um arquivo binário.
 */

#ifndef ASMWRITER_HEADER
#define ASMWRITER_HEADER

#include <stdio.h>

typedef struct _asmWriter
{
    FILE *file;
} ASMWRITER;

ASMWRITER *     asmWriter_new(const char *filename);
void            asmWriter_free(ASMWRITER *asmWriter);

void            asmWriter_writeInst(ASMWRITER *asmWriter
                                    /*, INSTRUCTION *instruction*/);

#endif /* ASMWRITER_HEADER */
