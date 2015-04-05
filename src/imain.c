/* 
 * Nome do Arquivo:  imain.c
 *       Descrição:  Interface do AssemblerM. Aqui será fornecido recursos 
 *                   de linha de comando para entrada feita pelo usuário.
 * 
 * Main file of AssemblerM.
 * Copyright (C) 2015  Cristian Costa Mello and Gustavo Freitas de Amorim
 *
 * This is part of AssemblerM
 * AssemblerM is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * AssemblerM is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#include <stdio.h>
#include <stdlib.h>

#include "asmError.h"
#include "assembler/assembler.h"        /* Inclua o TAD principal */

#define INPUT_FILE		1
#define OUTPUT_FILE		2
#define DIC_FILE		3
#define ARG_IGNORE_QTD	4
#define MIN_QTD_ARG		5

int *input_process(int argc, char **argv)
{
	int i;
	
	int *inputList;
	
	//Aloca o vetor que irá armazenar os valores.
	if((inputList = (int*)malloc((argc - ARG_IGNORE_QTD) * sizeof(int))) == NULL)
		return NULL;

	//Salta duas posições nos argumentos 
	//(ignora a chamada do programa e arquivo de entrada)
	i = ARG_IGNORE_QTD;
	
	//Armazena os valores
	for(i; i < argc; i++)
	{
		inputList[i - ARG_IGNORE_QTD] = atoi(argv[i]);
	}
	
	//Retorna
	return (inputList);
}

int main(int argc, char **argv)
{
    ASSEMBLER *asmr;
	
	int *inputList;

	//Se não passou parrâmetro algum exibe a ajuda
	if(argc < 2)
	{
		fprintf(stdout, "\nAssemblerM.\n");
		fprintf(stdout, "Copyright (C) 2015  Cristian Costa Mello and Gustavo Freitas de Amorim.\n\n");
		fprintf(stdout, "Linha de comando:\n");
		fprintf(stdout, "    AssemblerM <ARQUIVO_ENTRADA> <ARQUIVO_SAÍDA> <ARQUIVO_DICIONARIO> <arg1> <arg2> ... <argn>\n\n");
		fprintf(stdout, "Descrição dos argumentos:\n");
		fprintf(stdout, "   <ARQUIVO_ENTRADA>        : é um arquivo de texto codificado no padrão ANSI ASCII contendo\n");
		fprintf(stdout, "                              o código a ser montado.\n");
		fprintf(stdout, "   <ARQUIVO_SAÍDA>          : é o arquivo de saída do processo de montagem.\n");
		fprintf(stdout, "   <ARQUIVO_DICIONARIO>     : é o arquivo de dicionário a ser utilizado na montagem.\n");
		fprintf(stdout, "   <arg1> <arg2> ... <argn> : os valores numéricos inteiros para configurar os valores\n");
		fprintf(stdout, "                              iniciais dos registradores de entrada declarados no cabeçalho\n");
		fprintf(stdout, "                              do arquivo de texto de entrada.\n\n");
		return EXIT_SUCCESS;
	}

	//Se a quantidade mínima não for atingida
	else if(argc < MIN_QTD_ARG)
	{
		fprintf(stdout, "Linha de comando inválida. Invoque o programa sem argumentos para mais informações.\n");
		return (EXIT_FAILURE);
	}	

	//Gera a lista de valores de input
	if((inputList = input_process(argc, argv)) == NULL)
	{
		fprintf(stderr, "INPUT: Falha ao alocar memória.\n");
		return EXIT_FAILURE;
	}

	//Inicializa o sistema de erros
	if (asmError_new(ASMERROR_FAILEUREDESCLENGTH) == NULL)
    {
        fprintf(stderr, "ASMERROR: Ocorreu uma falha na alocaçao do ASMERROR.\n");

		//Libera as regiões de memória que não serão mais utilizadas
		free(inputList);

		return EXIT_FAILURE;
    }

	//Instancia o assembler
    if ((asmr = assembler_new()) == ASSEMBLER_EALLOC)
    {
        fprintf(stderr, "ASSEMBLER: %s\n", asmError_getDesc());

		//Libera as regiões de memória que não serão mais utilizadas
		free(inputList);
   		asmError_free();

		return EXIT_FAILURE;
    }

	//Monta o arquivo
	//Se ocorrer um erro, exibe na tela
    if(assembler_assemble(asmr, argv[INPUT_FILE], argv[OUTPUT_FILE], argv[DIC_FILE], inputList, 
							argc - ARG_IGNORE_QTD) == ASSEMBLER_FAILURE)
	{
		fprintf(stderr, "ASSEMBLER: %s\n", asmError_getDesc());

		//Libera as regiões de memória que não serão mais utilizadas
		assembler_free(asmr);
		free(inputList);
   	 	asmError_free();

		return EXIT_FAILURE;
	}
	//Se não, exibe sucesso
	printf("Montagem concluída com %li instruç%s processadas.\n", asmr->instCounter, 
						asmr->instCounter == 1 ? "ão" : "ões");
	
	//Libera as regiões de memória que não serão mais utilizadas
	assembler_free(asmr);
	free(inputList);
    asmError_free();
	
	//Finaliza
    return EXIT_SUCCESS;
}

