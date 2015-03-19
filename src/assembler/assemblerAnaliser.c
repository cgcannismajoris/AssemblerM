/*
 * ==========================================================================
 *
 * Nome do Arquivo:  assemblerAnaliser.c
 *
 *       Descricao:  
 *
 *          Versao:  1.0
 *       Criado em:  18/03/2015 16:08:36
 *         Revisao:  none
 *      Compilador:  gcc
 *
 *           Autor:  Gustavo Freitas de Amorim (), gustavofreitasamorim@gmail.com
 *     Organizacao:  VY Cannis Majoris
 *
 * =========================================================================
 */

#include "assembler.h"

static uint64_t __assembler_assemble_getNumNextLabel(ASSEMBLER *asmr, 
								const char *label){

	NODE *tmpNode;
	LABEL *tmpLabel;


	if(label == NULL){
		return (0);
	}
	
	//Busca a próxima label na lista	
	tmpNode = lista_search(asmr->labels, label, label_comparName);

	//se encontrou
	if(tmpNode != NULL){
		//Obtém o número da próxima label e retorna
		tmpLabel = node_getData(tmpNode);
		return (label_getLineNum(tmpLabel));
	}

	//Não encontrou
	return (0);
}


static int __assembler_assemble_isAddress(const char *add){
	
	if(add == NULL){
		return (ASSEMBLER_FALSE);
	}

	if(add[0] == '%'){
		return (ASSEMBLER_TRUE);
//		return (atoi(add + 1));
	}

	return (ASSEMBLER_FALSE);

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
	if(label == NULL || strlen(label) == 1){
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

static INSTRUCTION *__assembler_assemble_makeInstruction(ASSEMBLER *asmr, 
				TOKENS *input, TOKENS *pattern, TOKENS *translation){

	INSTRUCTION *novo = NULL;
	
	uint8_t patternCounter;
    uint8_t transCounter;

	uint8_t opcode = token_getToken(translation, 0)[0];

	char *aux;

	int pos;

	//Tipo R
	if(opcode >= 1 && opcode <= 22){

		/* ORDEM NO TRANSLATION EM POSIÇÕES
		 *  0 - Opcode
		 *  1 - dest
		 *  2 - orig1
		 *  3 - orig2 ou value
		 *  4 - Address
		 */

		if(token_getQtd(translation) != 5){
			return (NULL);
		}

		TIPO_R inst;
		
		inst.opcode = opcode;
		
		//--------------- Monta dest ---------------
		//Obtém a string que identifica o reg
		aux = token_getToken(translation, 1);
		//Obtém a posição correspondente na tradução
		pos = token_search(pattern, aux);
		
		//Erro de processamento! DICIONÁRIO INVÁLIDO
		if(pos == -1){
			return (NULL);
		}
		
		//Obtém a string correspondente na instrução
		//O + 1 é devido ao input armazenar o label da instrução
		aux = token_getToken(input, pos + 1);
			
		//Obtém a posição do registrador referênciado
		//Se não encontrar, instancia um novo
		if((pos = assembler_regSearch(asmr, aux)) == -1){
			
			//Obtém a posição correta
			pos = assembler_addReg(asmr, aux);

			if(pos == - 1){ //Excedeu 32 registradores
				return (NULL);
			}
		}

		//Seta o valor:
		inst.dest = pos;

		//--------------- Monta orig1 ---------------
		//Obtém a string que identifica o reg
	 	aux = token_getToken(translation, 2);
		//Obtém a posição correspondente na tradução
		pos = token_search(pattern, aux);

		//Erro de processamento! DICIONÁRIO INVÁLIDO
		if(pos == -1){
			return (NULL);
		}

		//Obtém a string correspondente na instrução
		aux = token_getToken(input, pos + 1);
		
		//Obtém a posição do registrador referênciado
		//Se não encontrar, instancia um novo
		if((pos = assembler_regSearch(asmr, aux)) == -1){
			//Obtém a posição correta
			pos = assembler_addReg(asmr, aux);

			if(pos == - 1){ //Excedeu 32 registradores
				return (NULL);
			}
		}

		//Seta o valor:
		inst.orig1 = pos;	

		//--------------- Monta orig2 ---------------
		//Obtém a string que identifica o reg/num
		aux = token_getToken(translation, 3);

		switch(inst.opcode){
			//Se opcode = 1, é um número
			case(1):
			case(2):
				pos = atoi(aux);
				break;

			default:	
				//Obtém a posição correspondente no pattern
				pos = token_search(pattern, aux);
				//Erro de processamento! DICIONÁRIO INVÁLIDO
				if(pos == -1){
					return (NULL);
				}
	
				//Obtém a string correspondente na instrução
				aux = token_getToken(input, pos + 1);
	
				//Obtém a posição do registrador referênciado
				//Se não encontrar, instancia um novo
				if((pos = assembler_regSearch(asmr, aux)) == -1){
					//Obtém a posição correta
					pos = assembler_addReg(asmr, aux);
		
					if(pos == - 1){ //Excedeu 32 registradores
						return (NULL);
					}
				}
				//Fim defalt		
		}

		//Seta o valor:
		inst.orig2 = pos;	

		//--------------- Monta address ---------------
		//Obtém a string que identifica a label
		aux = token_getToken(translation, 4);
		
		//Obtém a posição correspondente no pattern
		pos = token_search(pattern, aux);

		//Erro de processamento! DICIONÁRIO INVÁLIDO - ENTRADA INCONSISTENTE
		if(pos == -1){
			return (NULL);
		}
	 	
		//Busca a referência na entrada	
		aux = token_getToken(input, pos + 1);
		
		//Obtém o número da linha da label referenciada
		//Se não achar é sinal que deseja finalizar o programa
		if((pos = __assembler_assemble_getNumNextLabel(asmr, aux)) == 0){
			pos = lista_getQuant(asmr->labels) + 1; 
		}
		
		//address só pode armazenar 11bits, se o salto a ser feito é maior
		//que isto, não é possível montar o programa
		if((int)(pos - asmr->instCounter) > 1023 || 
						(int)(pos - asmr->instCounter) < -1023){
			return(NULL);
		}

		//Armazena a distância do salto
		inst.address = (int)(pos - (long int)asmr->instCounter - 1);
		
		//Armazena o valor na estrutura INSTRUCTION
		novo = (INSTRUCTION*)malloc(sizeof(INSTRUCTION));
		INSTRUCTION_SETINST(novo->inst, inst);
	}

	//Tipo BRANCH
	else if(opcode >= 23 && opcode <= 44){

	}

	//Tipo JUMP
	else if(opcode >= 45 && opcode <= 55){

	}
	//Tipo não definido
	else{
		return (NULL);
	}



	return (novo);
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
