/*
 * ==========================================================================
 *
 * Nome do Arquivo:  assemblerAnalyser.c
 *
 *       Descricao:  Implementação do módulo assemblerAnalyser.
 *
 *          Versao:  1.0
 *       Criado em:  18/03/2015 16:08:36
 *         Revisao:  none
 *      Compilador:  gcc
 *
 *           Autor:  Cristian Costa Mello, Gustavo Freitas de Amorim
 *     Organizacao:  VY Cannis Majoris
 *
 * =========================================================================
 */

#include "assemblerAnalyser.h"

uint64_t assembler_searchLabel(ASSEMBLER *asmr, const char *label){

	NODE *tmpNode;
	LABEL *tmpLabel;
	
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


char **assembler_makeIgnoreList(){

    char **ignoreList;
	uint64_t i;

    if((ignoreList = (char**)malloc(sizeof(char*) * ASSEMBLER_IGNORE_QTD)) == NULL){
		return (ASSEMBLER_EALLOC);
	}

	for(i = 0; i < ASSEMBLER_IGNORE_QTD; i++){
		ignoreList[i] = (char *)malloc(sizeof(char) * strlen(ASSEMBLER_IGNORE1) + 1);
		
        if(ignoreList[i] == NULL){
			for(i; i != 0; i--){
                free(ignoreList[i]);
			}
			
			free(ignoreList);
			return (ASSEMBLER_EALLOC);
		}
	}
	
	strcpy(ignoreList[0], ASSEMBLER_IGNORE1);
	strcpy(ignoreList[1], ASSEMBLER_IGNORE2);

	return(ignoreList);
}

void assembler_freeIgnoreList(char **ignoreList){
	
	uint64_t counter;
	
	for(counter = 0; counter < ASSEMBLER_IGNORE_QTD; counter++){
		free(ignoreList[counter]);
	}

	free(ignoreList);
}

int assembler_labelJudge(char *label){

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


INSTRUCTION *assembler_makeInst(ASSEMBLER *asmr, 
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

		if(token_getQtd(translation) != 3){
			asmError_setDesc(ASSEMBLER_EUSER_INVALIDDIC_MSG);
			return (NULL);
		}

		TIPO_R inst;
		
		inst.opcode = opcode;
	
		//--------------- Monta dest ---------------
		//Obtém a string que identifica o reg
		aux = token_getToken(pattern, 1);
		//Obtém a posição correspondente na tradução
		pos = token_search(translation, aux);
	
		//Erro de processamento! DICIONÁRIO INVÁLIDO
		if(pos == -1){
			asmError_setDesc(ASSEMBLER_EUSER_INVALIDDIC_MSG);
			return (NULL);
		}
	
		//Obtém a string correspondente na instrução
		//O +1 é devido ao input armazenar o label da instrução
		aux = token_getToken(input, pos + 1);
		
		//Obtém a posição do registrador referênciado
		//Se não encontrar, instancia um novo
		if((pos = registers_regSearch(asmr->regs, aux)) == -1){
			
			//Obtém a posição correta criando um novo registrador
			pos = registers_addReg(asmr->regs, aux);

			if(pos == - 1){ //Excedeu 32 registradores
				//A descrição do erro já foi setada no asmError.
				return (NULL);
			}
		}

		//Seta o valor:
		inst.reg = pos;

		//--------------- Monta address ---------------
		//Obtém a string que identifica o endereço
		aux = token_getToken(pattern, 2);
		
		//Obtém a posição correspondente no pattern
		pos = token_search(translation, aux);

		//Erro de processamento! DICIONÁRIO INVÁLIDO - ENTRADA INCONSISTENTE
		if(pos == -1){
			asmError_setDesc(ASSEMBLER_EUSER_INVALIDDIC_MSG);
			return (NULL);
		}
 	
		//Busca a referência na entrada	
		aux = token_getToken(input, pos + 1);
		
		//Obtém o número da linha da label referenciada
		//Se não achar é sinal que deseja finalizar o programa
		if((pos = assembler_searchLabel(asmr, aux)) == 0){
			pos = lista_getQuant(asmr->labels) + 1; 
		}
	
		//Armazena a distância do salto
		inst.address = (int)(pos - (long int)asmr->instCounter - 1);
	
		//Armazena o valor na estrutura INSTRUCTION
		novo = (INSTRUCTION*)malloc(sizeof(INSTRUCTION));
		INSTRUCTION_SETINST(novo->inst, inst);
	}

	//Tipos especiais
	else if(opcode == 56){
		/* BEQZ: 
		 *  0 - Opcode
		 *  1 - reg
		 *  2 - address_t
		 *  3 - address_f
		 */

		if(token_getQtd(translation) != 4){
			asmError_setDesc(ASSEMBLER_EUSER_INVALIDDIC_MSG);
			return (NULL);
		}

		TYPE_ESP_BEQZ inst;
		
		inst.opcode = opcode;
			
		//--------------- Monta reg ---------------
		//Obtém a string que identifica o reg
		aux = token_getToken(pattern, 1);
		//Obtém a posição correspondente na tradução
		pos = token_search(translation, aux);
	
		//Erro de processamento! DICIONÁRIO INVÁLIDO
		if(pos == -1){
			asmError_setDesc(ASSEMBLER_EUSER_INVALIDDIC_MSG);
			return (NULL);
		}
		
		//Obtém a string correspondente na instrução
		//O + 1 é devido ao input armazenar o label da instrução
		aux = token_getToken(input, pos + 1);
		
		//Obtém a posição do registrador referênciado
		//Se não encontrar, instancia um novo
		if((pos = registers_regSearch(asmr->regs, aux)) == -1){
			
			//Obtém a posição correta criando um novo registrador
			pos = registers_addReg(asmr->regs, aux);

			if(pos == - 1){ //Excedeu 32 registradores
				//A descrição do erro já foi setada no asmError.
				return (NULL);
			}
		}

		//Seta o valor:
		inst.reg = pos;
		
		//--------------- Monta address_t ---------------
		//Obtém a string que identifica a label
		aux = token_getToken(translation, 2);
		
		//Obtém a posição correspondente no pattern
		pos = token_search(pattern, aux);

 		//Erro de processamento! DICIONÁRIO INVÁLIDO - ENTRADA INCONSISTENTE
		if(pos == -1){
			asmError_setDesc(ASSEMBLER_EUSER_INVALIDDIC_MSG);
			return (NULL);
		}
	 	
		//Busca a referência na entrada	
		aux = token_getToken(input, pos + 1);
		
		//Obtém o número da linha da label referenciada
		//Se não achar é sinal que deseja finalizar o programa
		if((pos = assembler_searchLabel(asmr, aux)) == 0){
			pos = lista_getQuant(asmr->labels) + 1; 
		}
		
		//address só pode armazenar 11bits, se o salto a ser feito é maior
		//que isto, não é possível montar o programa
//		if((int)(pos - asmr->instCounter) > 1023 || 
//						(int)(pos - asmr->instCounter) < -1023){
//			asmError_setDesc(ASSEMBLER_EUSER_ADDRESSOVERFLOW_MSG);
//			return(NULL);
//		}

		//Armazena a distância do salto
		inst.address_t = (int)(pos - (long int)asmr->instCounter - 1);

		//--------------- Monta address_f ---------------
		//Obtém a string que identifica a label
		aux = token_getToken(translation, 3);
		
		//Obtém a posição correspondente no pattern
		pos = token_search(pattern, aux);

		//Erro de processamento! DICIONÁRIO INVÁLIDO - ENTRADA INCONSISTENTE
		if(pos == -1){
			asmError_setDesc(ASSEMBLER_EUSER_INVALIDDIC_MSG);
			return (NULL);
		}
	 	
		//Busca a referência na entrada	
		aux = token_getToken(input, pos + 1);
		
		//Obtém o número da linha da label referenciada
		//Se não achar é sinal que deseja finalizar o programa
		if((pos = assembler_searchLabel(asmr, aux)) == 0){
			//Define o salto para uma instrução posterior a última
			pos = lista_getQuant(asmr->labels) + 1; 
		}
		
		//address só pode armazenar 11bits, se o salto a ser feito é maior
		//que isto, não é possível montar o programa
//		if((int)(pos - asmr->instCounter) > 1023 || 
//						(int)(pos - asmr->instCounter) < -1023){
//			asmError_setDesc(ASSEMBLER_EUSER_ADDRESSOVERFLOW_MSG);
//			return(NULL);
//		}
		
		//Armazena a distância do salto
		inst.address_f = (int)(pos - (long int)asmr->instCounter - 1);
		
		//Armazena o valor na estrutura INSTRUCTION
		novo = (INSTRUCTION*)malloc(sizeof(INSTRUCTION));
		INSTRUCTION_SETINST(novo->inst, inst);

	}
	//Tipo não definido
	else{
		return (NULL);
	}

	return (novo);
}

int assembler_makeLabels(ASSEMBLER *asmr){
	
	uint64_t counter = 1;

	char *actualInst;
	char *actualLabel;

	char **ignoreList;

	TOKENS *actualTokens;
	NODE *tmpNode;
	LABEL *tmpLabel;

	//Gera a lista de itens a serem ignorados	
	ignoreList = assembler_makeIgnoreList();

	//Posiciona no início do arquivo
	asmLoader_rewind(asmr->loader);

	//Enquanto for possível ler...
	while((actualInst = asmLoader_getNextInst(asmr->loader)) != NULL){

		//Gera os tokens
		actualTokens = scanner_scan(actualInst, ignoreList, ASSEMBLER_SEPARATOR, 
						ASSEMBLER_IGNORE_QTD);
		
		//Se a label não for válida
		if(assembler_labelJudge(token_getToken(actualTokens, 0)) ==
						ASSEMBLER_FALSE){
			//Libera regiões de memória que não serão mais utilizadas
			lista_free(asmr->labels);
			token_free(actualTokens);
			assembler_freeIgnoreList(ignoreList);
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

	assembler_freeIgnoreList(ignoreList);

	//Reposiciona no início do arquivo
	asmLoader_rewind(asmr->loader);
	
	//Retorna sucesso
	return (ASSEMBLER_SUCCESS);
}
