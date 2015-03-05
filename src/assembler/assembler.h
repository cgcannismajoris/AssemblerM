/* assembler.h
 * TAD principal do Montador.
 */
#ifndef ASSEMBLER_HEADER
#define ASSEMBLER_HEADER

#include "../asmLoader/asmLoader.h" /* incluir TAD ASMLOADER */
#include "../asmWriter/asmWriter.h" /* incluir TAD ASMWRITER */

typedef struct _assembler
{
    ASMLOADER *asmLoader;
    ASMWRITER *asmWriter;
} ASSEMBLER, ASM;

ASSEMBLER * assembler_new(const char *input, char *output);
void        assembler_free(ASSEMBLER *assembler);
int         assembler_assemble(const char *filename);

#endif /* ASSEMBLER_HEADER */
