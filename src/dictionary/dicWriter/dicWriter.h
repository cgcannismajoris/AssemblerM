/* dicWriter.h
 * TAD DICWRITER.
 */
#ifndef DICWRITER_HEADER
#define DICWRITER_HEADER

#include <stdio.h>
#include <stdint.h>

typedef struct _dicWriter
{
    FILE *file;
} DICWRITER;

DICWRITER *     dicWriter_new(const char *filename);
void            dicWriter_free(DICWRITER *dicWriter);

void            dicWriter_writeQtdInst(DICWRITER *dicWriter, uint32_t num);

void            dicWriter_writeInst(DICWRITER *dicWriter,
                                    const char *rotulo,
                                    uint32_t opcode);

#endif /* DICWRITER_HEADER */
