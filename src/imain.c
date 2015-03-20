/* imain.c
 * Interface do AssemblerM. Aqui será fornecido recursos de linha de comando
 * para entrada feita pelo usuário.
 */

#include <stdio.h>
#include <stdlib.h>

#define ASMERROR_FAILEUREDESCLENGTH     100

extern void     asmError_setDesc(const char *failureDesc);

#include "assembler/assembler.h"        /* Inclua o TAD principal */

static char *   __failureDescription;   /* Descrição de falha. */

static char *   asmError_new(uint32_t desc);
static void     asmError_free();
static char *   asmError_getDesc();


int main(int argc, char **argv)
{
    ASSEMBLER *asmr;

    if ((__failureDescription = asmError_new(ASMERROR_FAILEUREDESCLENGTH)) == NULL)
    {
        fprintf(stderr, "ASMERROR: Ocorreu uma falha na alocaçao do ASMERROR.\n");
        return EXIT_FAILURE;
    }

    if ((asmr = assembler_new()) == ASSEMBLER_EALLOC)
    {
        fprintf(stderr, "ASSEMBLER: %s\n", asmError_getDesc());
        return EXIT_FAILURE;
    }

	assembler_assemble(asmr, argv[1], "exit.out", "data/dic_m.dic");

    asmError_free();

    return EXIT_SUCCESS;
}

static char *asmError_new(uint32_t desc)
{
    char *failure_desc;

    if ((failure_desc = (char *)malloc(sizeof(char) * desc)) == NULL)
        return NULL;

    return failure_desc;
}

void asmError_free()
{
    free(__failureDescription);
}

static char *asmError_getDesc()
{
    return __failureDescription;
}

void asmError_setDesc(const char *failureDesc)
{
    sprintf(__failureDescription, "%s", failureDesc);
}
