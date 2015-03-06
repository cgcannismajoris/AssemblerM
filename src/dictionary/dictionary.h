/* dictionary.h
 * TAD DICTIONARY.
 */
#ifndef DICTIONARY_HEADER
#define DICTIONARY_HEADER

#include "entry/entry.h"            /* incluir o TAD ENTRY */
#include "dicLoader/dicLoader.h"    /* incluir o TAD DICLOADER */
#include "dicWriter/dicWriter.h"    /* incluir o TAD DICWRITER */

#include <stddef.h>
#include <stdint.h>

typedef struct _dictionary
{
    ENTRY *verbetes;
    uint32_t qtdEntry;
} DICTIONARY, DIC;

DICTIONARY *    dic_new(const char *filename);
void            dic_free(DICTIONARY *dic);

int             dic_search(const char *rotulo);
void            dic_create(const char *output);

#endif /* DICIONARY_HEADER */
