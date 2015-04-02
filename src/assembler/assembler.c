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

ASSEMBLER *assembler_new()
{
    ASSEMBLER *novo;
	
    if ((novo = (ASSEMBLER*)malloc(sizeof(ASSEMBLER))) == NULL)
    {
        asmError_setDesc(ASSEMBLER_EALLOC_MSG);
        return ASSEMBLER_EALLOC;
    }

    if ((novo->labels = lista_new()) == LIST_EALLOC)
	{
		free(novo);
		return (ASSEMBLER_EALLOC);
	}

    if ((novo->regs = registers_new(MACHINE_MAX_REG)) == REGISTERS_EALLOC)
	{
		lista_free(novo->labels);
		free(novo);
		return ASSEMBLER_EALLOC;
	}
       
	novo->instCounter = 0;

	return (novo);
}


void assembler_free(ASSEMBLER *asmr)
{
	lista_free(asmr->labels);
	registers_free(asmr->regs);	
	free(asmr);
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

	//------ Inicializa as estruturas que irão compor o assembler: ------ 
	//Inicializa o loader
    if ((asmr->loader = asmLoader_new(src)) == ASMLOADER_EALLOC)
        return (ASSEMBLER_FAILURE);

	//Inciliza o writer
    if ((asmr->writer = asmWriter_new(bin)) == ASMWRITER_EALLOC)
        return (ASSEMBLER_FAILURE);
	
	//Inicia o dicionário
	if((asmr->dic    = dic_new(dicFile)) == DICTIONARY_EALLOC)
        return (ASSEMBLER_FAILURE);

	asmr->instCounter = 0;

	//------ INICIA O PROCESSAMENTO -------------------------------------



	//Faz busca pelas labels declaradas no arquivo
	if(assembler_makeLabels(asmr) != ASSEMBLER_SUCCESS){
		printf("Declaração de label invalida encontrada na linha: %li\n", asmr->instCounter);
		asmError_setDesc(ASSEMBLER_EMOUNT);
        return (ASSEMBLER_FAILURE);
	}

	//Carrega o dicionário
	dic_load(asmr->dic);
	
	//Cria a lista de termos a serem ignorados
	ignoreList = assembler_makeIgnoreList();

	//Enquanto for possível carregar novas instruções
	while((actualInst = asmLoader_getNextInst(asmr->loader)) != NULL){

		//Gera os tokens
		actualTokens = scanner_scan(actualInst, ignoreList, ASSEMBLER_SEPARATOR, 
						ASSEMBLER_IGNORE_QTD);
		

		//Procura o nome da instrução no dicionário
		actualEntry = dic_search(asmr->dic, token_getToken(actualTokens, 1));
		
		
		//Se não conseguiu encontrar a instrução referenciada no dicionário...
		if(actualEntry == NULL){
			printf("Instrução inválida na linha %li.\n", asmr->instCounter);
			asmError_setDesc(ASSEMBLER_EMOUNT); 
			assembler_free(asmr);
            return (ASSEMBLER_FAILURE);
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
			asmError_setDesc(ASSEMBLER_EMOUNT);
			assembler_free(asmr);			
            return (ASSEMBLER_FAILURE);
		}	


		//Gera a instrução de máquina	
		inst = assembler_makeInst(asmr, actualTokens, patternTokens, transTokens);
		
		if(inst == ASSEMBLER_EALLOC){
			printf("Erro na linha %li!\n", asmr->instCounter);
			//asmError já foi setado...
			assembler_free(asmr);
            return (ASSEMBLER_FAILURE);
		}
		
	
		//Grava a instrução gerada no arquivo
		asmWriter_writeInst(asmr->writer, inst);


		//Libera regiões de memória que não serão mais utilizadas
		token_free(actualTokens);

		asmr->instCounter++;	
	}

	//Libera regiões de memória que não serão mais utilizadas	
	asmLoader_free(asmr->loader);
	asmWriter_free(asmr->writer);
	lista_free(asmr->labels);
	dic_free(asmr->dic);
	registers_free(asmr->regs);

    return (asmr->instCounter);
}
