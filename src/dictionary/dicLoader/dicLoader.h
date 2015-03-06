/* dicLoader.h
 * TAD DICLOADER.
 */
#ifndef DICLOADER_HEADER
#define DICLOADER_HEADER

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

typedef struct _dicLoader
{
    FILE *file;
} DICLOADER;

DICLOADER *     dicLoader_new(const char *filename);
void            dicLoader_free(DICLOADER *dicLoader);

uint32_t        dicLoader_getQtdInst(DICLOADER *dicLoader);
uint32_t        dicLoader_getNextInst(DICLOADER *dicLoader);

#endif /* DICLOADER_HEADER */
