/* entry.h
 * TAD ENTRY.
 */
#ifndef ENTRY_HEADER
#define ENTRY_HEADER

#include <stddef.h>

typedef struct _entry
{
    char *  rotuloDaInst;
    int     opcode;
} ENTRY;

ENTRY *         entry_new(const char *rotulo, int opcode);
void            entry_free(ENTRY *entry);

const char *    entry_getRotulo(ENTRY *entry);
const char *    entry_getOpcode(ENTRY *entry);

#endif /* ENTRY_HEADER */
