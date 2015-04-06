/*
 * Nome do Arquivo:  assembler.c
 *       Descricao:  Implementação do TAD ASSEMBLER.
 * 
 * Main Module of AssemblerM.
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

    if ((novo->regs = registers_new()) == REGISTERS_EALLOC)
	{
		lista_free(novo->labels);
		free(novo);
		return ASSEMBLER_EALLOC;
	}
       
	novo->instCounter = 0;

	return (novo);
}


void assembler_close(ASSEMBLER *asmr)
{
	asmLoader_free(asmr->loader);
	asmWriter_free(asmr->writer);
	dic_free(asmr->dic);
}


void assembler_free(ASSEMBLER *asmr)
{
	lista_free(asmr->labels);
	registers_free(asmr->regs);
	
	free(asmr);
}


int assembler_assemble(ASSEMBLER *asmr, const char *src, 
							const char *bin, const char *dicFile, int *inputValues, 
							uint32_t length)
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

	//Inicializa o writer
    if ((asmr->writer = asmWriter_new(bin)) == ASMWRITER_EALLOC)
        return (ASSEMBLER_FAILURE);
	
	//Inicia o dicionário
	if((asmr->dic    = dic_new(dicFile)) == DICTIONARY_EALLOC)
        return (ASSEMBLER_FAILURE);

	
	//------ INICIA O PROCESSAMENTO -------------------------------------

	//Analisa a declaração da maquina e cria a lista de registradores
	if(assembler_makeRegisters(asmr) != ASSEMBLER_SUCCESS)
	{
		printf("Definição inválida da máquina.\n");
		return (ASSEMBLER_FAILURE);
	}

	//Grava o cabeçalho	
	if(assembler_makeHeader(asmr, inputValues, length) != ASSEMBLER_SUCCESS)
		return(ASSEMBLER_FAILURE);


	//Faz busca pelas labels declaradas no arquivo
	if((asmr->instCounter = assembler_makeLabels(asmr)) != ASSEMBLER_SUCCESS){
		printf("Declaração de label invalida ou repetida encontrada na %liª instrução.\n", 
						asmr->instCounter);
        return (ASSEMBLER_FAILURE);
	}
	asmr->instCounter = 1;

	//Carrega o dicionário
	dic_load(asmr->dic);


	//Cria a lista de termos a serem ignorados
	ignoreList = assembler_makeStrVector(ASSEMBLER_IGNORE_QTD, ASSEMBLER_IGNORE1, 
											ASSEMBLER_IGNORE2, ASSEMBLER_IGNORE3, 
											ASSEMBLER_IGNORE4, ASSEMBLER_IGNORE5);

	//Ignora a primeira linha do arquivo (já foi processada)
	//Nela está o cabeçalho.
	actualInst = asmLoader_getNextInst(asmr->loader);

	//Enquanto for possível carregar novas instruções
	while((actualInst = asmLoader_getNextInst(asmr->loader)) != NULL){
	
		//Remove possíveis comentários da instrução lida
		assembler_removeComment(actualInst);

		//Gera os tokens
		actualTokens = scanner_scan(actualInst, ignoreList, ASSEMBLER_SEPARATOR, 
						ASSEMBLER_IGNORE_QTD);

		//Procura o nome da instrução no dicionário
		actualEntry = dic_search(asmr->dic, token_getToken(actualTokens, 1));
	

		//Se não conseguiu encontrar a instrução referenciada no dicionário...
		if(actualEntry == NULL){
			printf("A %liª instrução é inválida.\n", asmr->instCounter);
			asmError_setDesc(ASSEMBLER_EMOUNT); 
			assembler_close(asmr);
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
			printf("Escrita inválida na %liª instrução.\n", asmr->instCounter);
			asmError_setDesc(ASSEMBLER_EMOUNT);
			assembler_close(asmr);			
            return (ASSEMBLER_FAILURE);
		}	


		//Gera a instrução de máquina	
		inst = assembler_makeInst(asmr, actualTokens, patternTokens, transTokens);
		
		if(inst == ASSEMBLER_EALLOC){
			printf("Erro na %liª instrução!\n", asmr->instCounter);
			//asmError já foi setado...
			assembler_close(asmr);
            return (ASSEMBLER_FAILURE);
		}
		
	
		//Grava a instrução gerada no arquivo
		asmWriter_writeInst(asmr->writer, inst);


		//Libera regiões de memória que não serão mais utilizadas
		token_free(actualTokens);

		asmr->instCounter++;	
	}
	

	//Se processou nenhuma instrução
	if(asmr->instCounter == 1)
	{
		printf("Arquivo fonte vazio.\n");
		asmError_setDesc(ASSEMBLER_EUSER_EMPTYSRC);
		return (ASSEMBLER_FAILURE);
	}

 	//Libera regiões de memória que não serão mais utilizadas	
	assembler_freeStrVector(ignoreList);
	assembler_close(asmr);
	
	return (--(asmr->instCounter));
}
