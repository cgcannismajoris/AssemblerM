/* entry.h
 * TAD ENTRY.
 */
#ifndef ENTRY_HEADER
#define ENTRY_HEADER

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
 
#define ENTRY_EALLOC		NULL

#define ENTRY_EALLOC_MSG 	"Falha na alocação da estrutura ASMLOADER."


#define ENTRY_ROTCOD_ASCII 		1
#define ENTRY_ROT_MAXLENGTH 	(11 * ENTRY_ROTCOD_ASCII)


typedef struct _entry
{
    char *  rotulo;
    uint8_t opcode;
} ENTRY;

ENTRY *         entry_new(char *rotulo, int opcode);
void            entry_free(ENTRY *entry);

const char *    entry_getRotulo(ENTRY *entry);
uint8_t         entry_getOpcode(ENTRY *entry);

#endif /* ENTRY_HEADER */
