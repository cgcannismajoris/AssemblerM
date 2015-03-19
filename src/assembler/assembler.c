/*
 * ==========================================================================
 *
 * Nome do Arquivo:  assembler.c
 *
 *       Descricao:  Implementação do TAD ASSEMBLER.
 *
 *          Versao:  1.0
 *       Criado em:  15/03/2015 19:46:30
 *         Revisao:  none
 *      Compilador:  gcc
 *
 *           Autor:  Cristian Costa Mello, Gustavo Freitas de Amorim 
 *     Organizacao:  VY Cannis Majoris
 *
 * =========================================================================
 */


#include "assembler.h"
#include "assemblerAnaliser.c"

ASSEMBLER *assembler_new()
{
    ASSEMBLER *novo;
	
    if ((novo = (ASSEMBLER*)malloc(sizeof(ASSEMBLER))) == NULL)
        return ASSEMBLER_EALLOC;

	novo->labels = lista_new();

	if(novo->labels == NULL){
		free(novo);
		novo = NULL;
	}

	novo->reg = (REG**)malloc(sizeof(REG*) * MACHINE_MAX_REG);

	novo->qtdReg = 0;
	
	novo->instCounter = 0;

	if(novo->reg == NULL){
		lista_free(novo->labels);
		free(novo);
		novo = NULL;
	}

	return (novo);
}


void assembler_free(ASSEMBLER *asmr)
{

	lista_free(asmr->labels);
		
	
	free(asmr);
}

long int assembler_addReg(ASSEMBLER *asmr, char *regName){
	
	REG *novo;

	if(asmr->qtdReg >= 31){
		return (-1);
	}

	novo = reg_new(regName);

	if(novo != NULL){
		asmr->reg[asmr->qtdReg] = novo;
		asmr->qtdReg++;
		return (asmr->qtdReg - 1); //Retorna a posição onde foi adicionado
	}

	return (0);
}

long int assembler_regSearch(ASSEMBLER *asmr, char *name){
	
	long int i;
	for(i = 0; i < asmr->qtdReg; i++){
		if(strcmp(reg_getName(asmr->reg[i]), name) == 0){
			return (i);
		}
	}
	
	return (-1);
}

int assembler_assemble(ASSEMBLER *asmr, const char *src, 
							const char *bin, const char *dicFile)
{
	
	char *actualInst;  //Armazena a instrução lida que está sendo processada no 
					   //momento

	char **ignoreList; //Armazena a lista de substrings a serem ignoradas

	TOKENS *actualTokens; //Armazena os tokens da instrução atual
	ENTRY *actualEntry;   //Armazena a entrada do dicionário corresponde atual
		
	INSTRUCTION *inst;

	TOKENS *patternTokens;
	TOKENS *transTokens;


	//--------------- VARIÁVEIS PARA DEBUG ---------------------
	uint64_t i;
	//---------------------- FIM -------------------------------

	if(asmr == NULL || src == NULL || bin == NULL || dicFile == NULL){
		return (ASSEMBLER_ENULLPOINTER);
	}

	//Inicializa as estruturas que irão compor o assembler:
	asmr->loader = asmLoader_new(src);
	asmr->writer = asmWriter_new(bin);
	asmr->dic    = dic_new(dicFile);
	asmr->reg    = (REG**)malloc(sizeof(REG*) * MACHINE_MAX_REG);
	
	//Faz busca pelas labels declaradas no arquivo
	if((i = __assembler_assemble_makeLabels(asmr)) != ASSEMBLER_SUCCESS){
		printf("Declaração de label invalida encontrada na linha: %li\n", i);
		return -1;
	}

	//Carrega o dicionário
	dic_load(asmr->dic);
	
	//Cria a lista de termos a serem ignorados
	ignoreList = __assembler_assemble_makeIgnoreList();

	//Enquanto for possível carregar novas instruções
	while((actualInst = asmLoader_getNextInst(asmr->loader)) != NULL){

		//Inicio da operação
		printf("\n--------------- ACTUAL INSTRUCTION = %s -------------\n\n", actualInst);
		
		
		//Gera os tokens
		actualTokens = scanner_scan(actualInst, ignoreList, ASSEMBLER_SEPARATOR, 
						ASSEMBLER_IGNORE_QTD);
		

		//Exibe os tokens gerados
		printf("GENERATED TOKENS:\n");
		for(i = 0; i < token_getQtd(actualTokens); i++){
			printf(" -> %s\n", token_getToken(actualTokens, (uint8_t)i));
		}
		printf("\n");


		//Procura o nome da instrução no dicionário
		actualEntry = dic_search(asmr->dic, token_getToken(actualTokens, 1));
		
		//Se não conseguiu encontrar a instrução referenciada no dicionário...
		if(actualEntry == NULL){
			printf("Instrução inválida na linha %li.\n", asmr->instCounter);
			assembler_free(asmr);
			return (-1);
		}


		//Gera os tokens da entrada encontrada
		patternTokens = scanner_scan(entry_getPattern(actualEntry), NULL, " ", 0);
		transTokens = scanner_scan(entry_getTranslation(actualEntry), NULL, " ", 0);
	
		//Se escreveu uma quantidade de argumentos inválida
		//O decremento de 1 é devido à entrada apresentar o label da intrução
		//e o dicionário não ter este armazenado
		if(token_getQtd(patternTokens) != token_getQtd(actualTokens) - 1){
			//Mostra o erro e finaliza
			printf("Escrita inválida na linha %li.\n", asmr->instCounter);
			assembler_free(asmr);			
			return (-1);
		}	

		//Gera a instrução de máquina	
		inst = __assembler_assemble_makeInstruction(asmr, actualTokens, patternTokens,
														transTokens);
		
		if(inst == NULL){
			printf("Erro na linha %li!\n", asmr->instCounter);
			assembler_free(asmr);
			return (-1);
		}
		
		//Grava a instrução gerada no arquivo
		asmWriter_writeInst(asmr->writer, inst);

		//Libera regiões de memória que não serão mais utilizadas
		token_free(actualTokens);

		asmr->instCounter++;	

		//Fim da operação
		printf("--------------------------- END -----------------------\n");
	}
	printf("\n");
		
	//Libera regiões de memória que não serão mais utilizadas	
	asmLoader_free(asmr->loader);
	asmWriter_free(asmr->writer);
	lista_free(asmr->labels);
	dic_free(asmr->dic);
	for(--asmr->qtdReg; asmr->qtdReg >= 0; asmr->qtdReg--){
		reg_free(asmr->reg[asmr->qtdReg]);
	}
	free(asmr->reg);

    return (ASSEMBLER_SUCCESS);
}
