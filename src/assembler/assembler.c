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

static char **__assembler_assemble_makeIgnoreList(){

	char **ignoreList = (char**)malloc(sizeof(char*) * ASSEMBLER_IGNORE_QTD);
	uint64_t i;


	if(ignoreList == NULL){
		return (ASSEMBLER_EALLOC);
	}

	for(i = 0; i < ASSEMBLER_IGNORE_QTD; i++){
		ignoreList[i] = (char *)malloc(sizeof(char) * strlen(ASSEMBLER_IGNORE1) + 1);
		
		if(ignoreList[i] == 0){
			for(i; i != 0; i--){
				ignoreList[i] = (char *)malloc(sizeof(char) * strlen(ASSEMBLER_IGNORE1) + 1);
			}
			
			free(ignoreList);
			return (ASSEMBLER_EALLOC);
		}
	}
	

	strcpy(ignoreList[0], ASSEMBLER_IGNORE1);
	strcpy(ignoreList[1], ASSEMBLER_IGNORE2);

	return(ignoreList);
}

static void __assembler_assemble_freeIgnoreList(char **ignoreList){
	
	uint64_t counter;
	
	if(ignoreList == NULL){
		return;
	}

	for(counter = 0; counter < ASSEMBLER_IGNORE_QTD; counter++){
		free(ignoreList[counter]);
	}

	free(ignoreList);
}

static int __assembler_assemble_labelJudge(char *label){

	char *pos;
  	
   	//Se a entrada é inválida	
	if(label == NULL){
		return (ASSEMBLER_FALSE);
	}

	//Procura o terminador de label
	pos = strstr(label, ASSEMBLER_LABEL_TERMINATOR);

	//Se não achou
	if(pos == NULL){
		return (ASSEMBLER_FALSE);
	}
	
	//Se achou na última posição da string
	if(pos == ((char*)(label + strlen(label) - 1))){
		return (ASSEMBLER_TRUE);
	}

	//Se achou em outra posição, é uma label inválida
	return (ASSEMBLER_FALSE);
}

static int __assembler_assemble_makeLabels(ASSEMBLER *asmr){
	
	uint64_t counter = 1;

	char *actualInst;
	char *actualLabel;

	char **ignoreList;

	TOKENS *actualTokens;
	NODE *tmpNode;
	LABEL *tmpLabel;

	if(asmr == NULL){
		return (ASSEMBLER_ENULLPOINTER);
	}
	
	//Gera a lista de itens a serem ignorados	
	ignoreList = __assembler_assemble_makeIgnoreList();

	//Posiciona no início do arquivo
	asmLoader_rewind(asmr->loader);

	//Enquanto for possível ler...
	while((actualInst = asmLoader_getNextInst(asmr->loader)) != NULL){

		//Gera os tokens
		actualTokens = scanner_scan(actualInst, ignoreList, ASSEMBLER_SEPARATOR, 
						ASSEMBLER_IGNORE_QTD);
		
		//Se a label não for válida
		if(__assembler_assemble_labelJudge(token_getToken(actualTokens, 0)) ==
						ASSEMBLER_FALSE){
			//Libera regiões de memória que não serão mais utilizadas
			lista_free(asmr->labels);
			token_free(actualTokens);
			__assembler_assemble_freeIgnoreList(ignoreList);
			asmr->labels = NULL;
			
			//Reposiciona o arquivo
			asmLoader_rewind(asmr->loader);
			
			//Retorna
			return (counter);
		}
		
		//Se a label for válida, segue adiante.


		//Constrói a label, removendo o ':' presente no final
		actualLabel = token_getToken(actualTokens, 0);
		actualLabel[strlen(actualLabel) - 1] = '\0';

		//Insere a label lista
		tmpLabel = label_new(actualLabel, counter);
		tmpNode = node_new(tmpLabel, 0, sizeof(LABEL));
		lista_insertLastNode(asmr->labels, tmpNode);

		//Libera a região de memória que não será mais utilizada
		token_free(actualTokens);
		
		//Incrementa o contador de linha
		counter++;
	}

	__assembler_assemble_freeIgnoreList(ignoreList);

	//Reposiciona no início do arquivo
	asmLoader_rewind(asmr->loader);
	
	//Retorna sucesso
	return (ASSEMBLER_SUCCESS);
}

int assembler_assemble(ASSEMBLER *asmr, const char *src, 
							const char *bin, const char *dicFile)
{
	
	char *actualInst;

	char **ignoreList;

	TOKENS *actualTokens;
	ENTRY *actualEntry;
	LABEL *tmpLabel;
	NODE *tmpNode;

	TOKENS *tk;

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
	if((counter = __assembler_assemble_makeLabels(asmr)) != ASSEMBLER_SUCCESS){
		printf("Declaração de label invalida encontrada na linha: %li\n", counter);
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

		
		//Busca tokens dentro do resultado da busca
		tk = scanner_scan((char*)entry_getPattern(actualEntry), NULL, 
						ASSEMBLER_SEPARATOR, 0);
		printf("PATTERN TOKENS:\n");
		for(counter = 0; counter < token_getQtd(tk); counter++){
			printf(" -> %s\n", token_getToken(tk, (uint8_t)counter));
		}
		printf("\n");
		free(tk);
		tk = scanner_scan((char*)entry_getTranslation(actualEntry), NULL, 
						ASSEMBLER_SEPARATOR, 0);
		printf("TRANSLATION TOKENS:\n");
		for(counter = 0; counter < token_getQtd(tk); counter++){
			printf(" -> %s\n", token_getToken(tk, (uint8_t)counter));
		}
		printf("\n");
		free(tk);
		
		
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
