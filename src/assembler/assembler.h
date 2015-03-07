/* assembler.h
 * TAD principal do Montador.
 */
#ifndef ASSEMBLER_HEADER
#define ASSEMBLER_HEADER

#include "../asmLoader/asmLoader.h" /* incluir TAD ASMLOADER */
#include "../asmWriter/asmWriter.h" /* incluir TAD ASMWRITER */
#include "../instruction/instruction.h" /* incluir o TAD INSTRUCTION */
#include "../dictionary/dictionary.h" /* incluir o TAD DICTIONARY */
#include "label/label.h" /* incluir o TAD LABEL */

typedef struct _assembler
{
    ASMLOADER *asmLoader;
    ASMWRITER *asmWriter;
    /* Implementar LISTA ENCADEADA para LABEL */
} ASSEMBLER, ASM;

ASSEMBLER * assembler_new(const char *input, char *output);
void        assembler_free(ASSEMBLER *assembler);
int         assembler_assemble(ASSEMBLER *assembler, const char *src, const char *bin, const char *dicFile);

#endif /* ASSEMBLER_HEADER */
