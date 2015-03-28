/* imain.c
 * Interface do AssemblerM. Aqui será fornecido recursos de linha de comando
 * para entrada feita pelo usuário.
 */

#include <stdio.h>
#include <stdlib.h>

#define ASMERROR_FAILEUREDESCLENGTH     100

#include "asmError.h"
#include "assembler/assembler.h"        /* Inclua o TAD principal */


int main(int argc, char **argv)
{
    ASSEMBLER *asmr;

    if (asmError_new(ASMERROR_FAILEUREDESCLENGTH) == NULL)
    {
        fprintf(stderr, "ASMERROR: Ocorreu uma falha na alocaçao do ASMERROR.\n");
        return EXIT_FAILURE;
    }

    if ((asmr = assembler_new()) == ASSEMBLER_EALLOC)
    {
        fprintf(stderr, "ASSEMBLER: %s\n", asmError_getDesc());
        return EXIT_FAILURE;
    }

    if(assembler_assemble(asmr, argv[1], "exit.out", "data/dic_m.dic") == ASSEMBLER_FAILURE)
	{
		fprintf(stderr, "ASSEMBLER: %s\n", asmError_getDesc());
        return EXIT_FAILURE;
	}
	else
	{
		printf("Concluído com %li linhas processadas.\n", asmr->instCounter);
	}

    asmError_free();

    return EXIT_SUCCESS;
}


