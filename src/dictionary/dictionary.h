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
    uint64_t qtdEntry;
	const char *filename;
} DICTIONARY, DIC;

DICTIONARY *    dic_new(const char *filename);
void            dic_free(DICTIONARY *dic);

ENTRY *         dic_search(DICTIONARY *dic, const char *rotulo);
int             dic_save(DICTIONARY *dic);
int             dic_load(DICTIONARY *dic);

#endif /* DICIONARY_HEADER */
