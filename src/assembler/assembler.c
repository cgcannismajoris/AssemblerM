/* assembler.c
 * Implementaçao do TAD ASSEMBLER (PRINCIPAL).
 */

#include "assembler.h"


ASSEMBLER *assembler_new()
{
	ASSEMBLER *novo = (ASSEMBLER*)malloc(sizeof(ASSEMBLER));

	return (novo);
}


void assembler_free(ASSEMBLER *asmr)
{
	free(asmr);
}


int assembler_assemble(ASSEMBLER *asmr, const char *src, 
							const char *bin, const char *dicFile)
{
	
	char *actualInst;

	TOKENS *actualTokens;
	ENTRY *actualEntry;

	//--------------- VARIÁVEIS PARA DEBUG ---------------------
	uint64_t counter;
	//---------------------- FIM -------------------------------

	if(asmr == NULL || src == NULL || bin == NULL || dicFile == NULL){
		return (ASSEMBLER_ENULLPOINTER);
	}

	//Inicializa as estruturas que irão compor o assembler:
	asmr->loader = asmLoader_new(src);
	asmr->writer = asmWriter_new(bin);
	asmr->dic    = dic_new(dicFile);
	asmr->reg    = (REG**)malloc(sizeof(REG*) * MACHINE_MAX_REG);

	dic_load(asmr->dic);

	while((actualInst = asmLoader_getNextInst(asmr->loader)) != NULL){
		//Inicio da opração
		printf("--------------- ACTUAL INSTRUCTION = %s -------------\n", actualInst);
		
		
		//Gera os tokens
		actualTokens = scanner_scan(actualInst);
		

		//Exibe os tokens gerados
		printf("GENERATED TOKENS:\n");
		for(counter = 0; counter < token_getQtd(actualTokens); counter++){
			printf(" -> %s\n", token_getToken(actualTokens, (uint8_t)counter));
		}
		printf("\n");


		//Procura o nome da instrução no dicionário
		actualEntry = dic_search(asmr->dic, token_getToken(actualTokens, 1));
	

		//Exibe o resultado da busca
		printf("INSTRUCTION ENTRY:\n");
		printf(" PATTERN    : %s\n", entry_getPattern(actualEntry));
		printf(" TRANSLATION: %s\n", entry_getTranslation(actualEntry));
	

		//Libera regiões de memória que não serão mais utilizadas
		token_free(actualTokens);


		//Fim da operação
		printf("--------------------------- END -----------------------\n");
	}
	
	asmLoader_free(asmr->loader);
	asmWriter_free(asmr->writer);
	dic_free(asmr->dic);

	for(counter = 0; counter < asmr->qtdReg; counter++){
		reg_free(asmr->reg[counter]);
	}
	free(asmr->reg);



	return (ASMLOADER_SUCCESS);
}


