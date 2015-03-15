/* imain.c
 * Interface do AssemblerM. Aqui será fornecido recursos de linha de comando
 * para entrada feita pelo usuário.
 */

#include <stdio.h>
#include <stdlib.h>

#include "assembler/assembler.h"   /* Inclua o TAD principal */

int main(int argc, char **argv)
{

	ASSEMBLER *asmr = assembler_new();

	assembler_assemble(asmr, argv[1], "exit.out", "data/dic_m.dic");

    return 0;
}
