/* imain.c
 * Interface do AssemblerM. Aqui será fornecido recursos de linha de comando
 * para entrada feita pelo usuário.
 */

#include <stdio.h>
#include <stdlib.h>

#include "asmError.h"
#include "assembler/assembler.h"        /* Inclua o TAD principal */


int *input_process(int argc, char **argv)
{
	
	int i;
	
	int *inputList;

	if((inputList = (int*)malloc((argc-2) * sizeof(int))) == NULL)
		return NULL;

	//Salta duas posições nos argumentos 
	//(ignora a chamada do programa e arquivo de entrada)
	i = 2;

	for(i; i < argc; i++)
	{
		inputList[i - 2] = atoi(argv[i]);
	}

	return (inputList);
}

int main(int argc, char **argv)
{
    ASSEMBLER *asmr;
	
	int *inputList;
	if(argc < 2)
	{
		fprintf(stderr, "Sem arquivo de entrada.\n");
		return EXIT_FAILURE;
	}
	
	if((inputList = input_process(argc, argv)) == NULL)
	{
		fprintf(stderr, "INPUT: Falha ao alocar memória.\n");
		return EXIT_FAILURE;
	}

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
    if(assembler_assemble(asmr, argv[1], "exit.out", "data/dic_m.dic", 
							inputList, argc - 2) == ASSEMBLER_FAILURE)
	{
		fprintf(stderr, "ASSEMBLER: %s\n", asmError_getDesc());
        return EXIT_FAILURE;
	}
	else
	{
		printf("Concluído com %li linhas processadas.\n", asmr->instCounter);
	}
	
	free(inputList);
    asmError_free();

    return EXIT_SUCCESS;
}


