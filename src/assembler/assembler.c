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
        return ASSEMBLER_EALLOC;

	novo->labels = lista_new();

	if(novo->labels == NULL){
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

static void __assembler_assemble_makeLabels(ASSEMBLER *asmr){
	
	uint64_t counter = 0;

	char *actualInst;

	TOKENS *actualTokens;
	NODE *tmpNode;
	LABEL *tmpLabel;
	

	if(asmr == NULL){
		return;
	}
	
	//Posiciona no início do arquivo
	asmLoader_rewind(asmr->loader);

	//Enquanto for possível ler...
	while((actualInst = asmLoader_getNextInst(asmr->loader)) != NULL){
		//Gera os tokens
		actualTokens = scanner_scan(actualInst);

		//Insere na lista
		tmpLabel = label_new(token_getToken(actualTokens, 0), counter);
		tmpNode = node_new(tmpLabel, 0, sizeof(LABEL));
		lista_insertLastNode(asmr->labels, tmpNode);

		//Libera a região de memória que não será mais utilizada
		token_free(actualTokens);
		
		//Incrementa o contador de linha
		counter++;
	}
	
	//Reposiciona no início do arquivo
	asmLoader_rewind(asmr->loader);
}

int assembler_assemble(ASSEMBLER *asmr, const char *src, 
							const char *bin, const char *dicFile)
{
	
	char *actualInst;

	TOKENS *actualTokens;
	ENTRY *actualEntry;
	LABEL *tmpLabel;
	NODE *tmpNode;

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
	
	//Faz busca pelas labels declaradas no arquivo
	__assembler_assemble_makeLabels(asmr);

	//Carrega o dicionário
	dic_load(asmr->dic);
	
	//Enquanto for possível carregar novas instruções
	while((actualInst = asmLoader_getNextInst(asmr->loader)) != NULL){
		
		//Inicio da operação
		printf("\n--------------- ACTUAL INSTRUCTION = %s -------------\n\n", actualInst);
		
		
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
		printf(" TRANSLATION: %s\n\n", entry_getTranslation(actualEntry));


		//Procura a label da próxima linha na lista
		tmpNode = lista_search(asmr->labels, token_getToken(actualTokens, 
								token_getQtd(actualTokens) - 1), label_comparName);
		tmpLabel = (LABEL*)node_getData(tmpNode);
		printf("DESTINY LABEL:\n");
		printf("  NAME  : %s\n", label_getName(tmpLabel));
		printf("  NUMBER: %li\n\n", label_getLineNum(tmpLabel));

		//Libera regiões de memória que não serão mais utilizadas
		token_free(actualTokens);


		//Fim da operação
		printf("--------------------------- END -----------------------\n");
	}
	printf("\n");
		
	//Libera regiões de memória que não serão mais utilizadas	
	asmLoader_free(asmr->loader);
	asmWriter_free(asmr->writer);
	lista_free(asmr->labels);
	dic_free(asmr->dic);
	for(counter = 0; counter < asmr->qtdReg; counter++){
		reg_free(asmr->reg[counter]);
	}
	free(asmr->reg);



    return (ASSEMBLER_SUCCESS);
}


