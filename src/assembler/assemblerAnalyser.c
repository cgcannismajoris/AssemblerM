/*
 * Nome do Arquivo:  assemblerAnalyser.c
 *       Descricao:  Implementação do módulo assemblerAnalyser.
 * 
 * AssemblerAnalyser for AssemblerM.
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
#include "assemblerAnalyser.h"

uint64_t assembler_searchLabel(ASSEMBLER *asmr, const char *label)
{
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


char **assembler_makeStrVector(int qtd, ...)
{
    char **strVector;
	char *tmp;
	uint32_t i;
	va_list args;

	va_start(args, qtd);

    if((strVector = (char**)malloc(sizeof(char*) * qtd + 1)) == NULL){
		return (ASSEMBLER_EALLOC);
	}

	for(i = 0; i < qtd; i++){
		strVector[i] = (char *)malloc(sizeof(char) * strlen(ASSEMBLER_IGNORE1) + 1);

        if(strVector[i] == NULL){
			for(i; i != 0; i--){
                free(strVector[i]);
			}
			
			free(strVector);
			return (ASSEMBLER_EALLOC);
		}

		tmp = va_arg(args, char*);
		memcpy(strVector[i], tmp, (sizeof(char) * strlen(tmp)) + 1);
	}
	
	strVector[i] = NULL;

	return(strVector);
}

void assembler_freeStrVector(char **strVector)
{	
	uint64_t counter;
	
	for(counter = 0; strVector[counter] != NULL; counter++){
		free(strVector[counter]);
	}

	free(strVector);
}

int assembler_labelJudge(char *label)
{
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

void assembler_removeComment(char *inst)
{

	int i;
	uint32_t chrsLength = strlen(ASSEMBLER_COMMENT_CHRS);
	char chrs[chrsLength + 1];

	//Copia os chrs para a string
	strcpy(chrs, ASSEMBLER_COMMENT_CHRS);
	
	//Enquanto inst não chegar no final
	while(*inst != '\0')
	{
		//Verifica se existem ocorrências dos caracteres
		for(i = 0; i < chrsLength; i++)
		{
			//Se existir, coloca o terminador e retorna
			if(*inst == chrs[i])
			{
				*inst = '\0';
				return;
			}
		}
		inst++;
	}
}

static void __assembler_makeRegisters_insert(ASSEMBLER *asmr, 
												TOKENS *tokens, uint8_t block_type)
{
	int i;

	for(i = 0; i < token_getQtd(tokens); i++)
	{
		registers_addReg(asmr->regs, token_getToken(tokens, i), block_type); 
	}
}

int assembler_makeRegisters(ASSEMBLER *asmr)
{
	
	TOKENS  *machineTokens;
	
	char *header;

	char *arrowStart;
	int arrowDirection;

	char **ignoreList;

	TOKENS *output, *input;

	int i;

	asmLoader_rewind(asmr->loader);

	//Carrega a descrição da máquina
	if((header = asmLoader_getNextInst(asmr->loader)) == NULL)
	{
		return (ASSEMBLER_FAILURE);
	}
		
	// ---------------- PRÉ-PROCESSA O HEADER ----------------
	//Salta para a posição posterior à declaração do nome da máquina 
	while(*(header - 1) != ASSEMBLER_LABEL_TERMINATOR_CHR && *header != '\0')
	{
		header ++;
	}	

	//Obtém a posição da seta (seta para a esquerda)
	arrowStart = strstr(header, ASSEMBLER_MACHINEDEC_LARROW);
	arrowDirection = 0;

	//Se não achou, significa que pode estar no sentido inverso... (para a direita)
	if(arrowStart == NULL)
	{
		//Procura a seta invertida
		arrowStart = strstr(header, ASSEMBLER_MACHINEDEC_RARROW);
		
		//Se não achou, uma definição inválida foi escrita
		if(arrowStart == NULL)
 		{
			asmError_setDesc(ASSEMBLERANALYSER_EUSER_INVMAC_MSG);
			return (ASSEMBLER_FAILURE);
		}

		arrowDirection = 1;
	}

	//Remove a seta do header
	arrowStart[0] = '\0';
	arrowStart[1] = '\0';	
	arrowStart += 2;
		
	//Separa os tokens da lista de registradores de saida
	if(arrowDirection == 0)
	{
		output = scanner_scan(header, NULL, ASSEMBLER_MACHINEDEC_SEPARATORS, 0);
		input  = scanner_scan(arrowStart, NULL, ASSEMBLER_MACHINEDEC_SEPARATORS, 0);
	}
	else
	{
		output = scanner_scan(arrowStart, NULL, ASSEMBLER_MACHINEDEC_SEPARATORS, 0);
		input  = scanner_scan(header, NULL, ASSEMBLER_MACHINEDEC_SEPARATORS, 0);
	}

	// ------------------ PROCESSA OS TOKENS ------------------
	
	//Se um dos tokens for vazio (não foi declarado input ou output)
	if(token_getQtd(input) == 0)
	{
		asmError_setDesc(ASSEMBLERANALYSER_EUSER_NOINPUT_MSG);
		return (ASSEMBLER_FAILURE);
	}	
	if(token_getQtd(output) == 0)
	{
		asmError_setDesc(ASSEMBLERANALYSER_EUSER_NOOUTPUT_MSG);
		return (ASSEMBLER_FAILURE);
	}	


	//Busca por tokens em comum... Se existe, uma declaração inválida foi feita
	if(token_verifCommon(input, output) == 1 || 
					token_verifRepetitions(input) == 1 ||
					token_verifRepetitions(output) == 1)
	{
		asmError_setDesc(ASSEMBLERANALYSER_EUSER_DOUBDEC_MSG);
		return (ASSEMBLER_FAILURE);
	}


	//Insere nos registradores na ordem que foram declarados
	if(arrowDirection == 0)
	{
		__assembler_makeRegisters_insert(asmr, output, REG_TYPE_OUTPUT);
		__assembler_makeRegisters_insert(asmr, input, REG_TYPE_INPUT);
	}
	else
	{
		__assembler_makeRegisters_insert(asmr, input, REG_TYPE_INPUT);
		__assembler_makeRegisters_insert(asmr, output, REG_TYPE_OUTPUT);
	}

	asmLoader_rewind(asmr->loader);

	return (ASSEMBLER_SUCCESS);
}


int assembler_makeHeader(ASSEMBLER *asmr, int *inputList, uint32_t length)
{
	
	uint8_t *header;
	size_t headerLength, i, j, k;
	
	/* i -> contador do inputList
	 * j -> contador do header
	 * k -> contador da lista de registradores
	 */

	//Se a quantidade de argumentos exceder a quantidade de registradores
	if(length > registers_getQtdInput(asmr->regs))
	{
		asmError_setDesc(ASSEMBLERANALYSER_EUSER_EXCESSARGS_MSG);
		return ASSEMBLER_FAILURE; 
	}
	//Se a quantidade é inferior...
	else if(length < registers_getQtdInput(asmr->regs))
	{
		asmError_setDesc(ASSEMBLERANALYSER_EUSER_LESSARGS_MSG);
		return ASSEMBLER_FAILURE; 
	}	

	//Calcula o tamanho do header
	headerLength = ((sizeof(uint8_t) + sizeof(int)) * 
					registers_getQtdRegs(asmr->regs)) + (sizeof(uint32_t));
	
	//Aloca a memória necessária
	if((header = (uint8_t*)malloc(headerLength)) == NULL)
	{
		asmError_setDesc(ASSEMBLER_EALLOC_MSG);
		return (ASSEMBLERANALYSER_EALLOC_ID);
	}
   
	//Grava a quantidade de registradores a serem utilizados
	*((uint32_t*)(header)) = registers_getQtdRegs(asmr->regs);
	
 	//Grava os valores iniciais de memória com o respectivo tipo do registrador
	//(input ou output) 
	for(i = 0, k = 0, j = sizeof(uint32_t); k < registers_getQtdRegs(asmr->regs); k++)
	{
		//Grava o tipo 
		*((uint8_t*)(header + j)) = reg_getType(registers_getReg(asmr->regs, k));
		j += sizeof(uint8_t);
		
		//Grava o valor inicial de memória
		//Se o registrador atual for de input grava o valor recebido, se não grava 0
		if(reg_getType(registers_getReg(asmr->regs, k)) == REG_TYPE_INPUT)
		{
			*((int*)(header + j)) = inputList[i];
			i++;
		}
		else
		{
			*((int*)(header + j)) = 0;
		}

		j += sizeof(int);
	} 

	//Grava o cabeçalho no arquivo
 	asmWriter_writeHeader(asmr->writer, header, headerLength);
	
	//Libera a memória utilizada
	free(header);
	
	//Retorna sucesso	
	return (ASSEMBLER_SUCCESS);
}


INSTRUCTION *assembler_makeInst(ASSEMBLER *asmr, 
				TOKENS *input, TOKENS *pattern, TOKENS *translation)
{

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
		//Se não encontrar, indica erro
		if((pos = registers_regSearch(asmr->regs, aux)) == -1){
			asmError_setDesc(ASSEMBLERANALYSER_EUSER_REGNOTDEC_MSG);
			return (NULL);
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
		inst.address = (int)(pos - (long int)asmr->instCounter);
	
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
		//Se não encontrar, indica erro
		if((pos = registers_regSearch(asmr->regs, aux)) == -1){
			asmError_setDesc(ASSEMBLERANALYSER_EUSER_REGNOTDEC_MSG);
			return (NULL);
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
		
		//Armazena a distância do salto
		inst.address_t = (int)(pos - (long int)asmr->instCounter);

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
		
		//Armazena a distância do salto
		inst.address_f = (int)(pos - (long int)asmr->instCounter);
		
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

int assembler_makeLabels(ASSEMBLER *asmr)
{	
	uint64_t counter = 1;

	char *actualInst;
	char *actualLabel;

	char **ignoreList;

	TOKENS *actualTokens;
	NODE *tmpNode;
	LABEL *tmpLabel;

	//Gera a lista de itens a serem ignorados	
	ignoreList = assembler_makeStrVector(ASSEMBLER_IGNORE_QTD, ASSEMBLER_IGNORE1, 
											ASSEMBLER_IGNORE2, ASSEMBLER_IGNORE3, 
											ASSEMBLER_IGNORE4, ASSEMBLER_IGNORE5);

	//Posiciona no início do arquivo
	asmLoader_rewind(asmr->loader);
	
	//Ignora a primeira linha...
	asmLoader_getNextInst(asmr->loader);

	//Enquanto for possível ler...
	while((actualInst = asmLoader_getNextInst(asmr->loader)) != NULL)
	{
		//Remove possíveis comentários da instrução lida
		assembler_removeComment(actualInst);
	
		//Gera os tokens
		actualTokens = scanner_scan(actualInst, ignoreList, ASSEMBLER_SEPARATOR, 
						ASSEMBLER_IGNORE_QTD);
		
		//Se a label não for válida
		if(assembler_labelJudge(token_getToken(actualTokens, 0)) ==
						ASSEMBLER_FALSE)
		{
			//Libera regiões de memória que não serão mais utilizadas
			lista_free(asmr->labels);
			token_free(actualTokens);
			assembler_freeStrVector(ignoreList);
			asmr->labels = NULL;
			
			//Reposiciona o arquivo
			asmLoader_rewind(asmr->loader);
			
			//Lança o erro
			asmError_setDesc(ASSEMBLERANALYSER_EUSER_INVLABEL_MSG);

			//Retorna
			return (counter);
		}
		
		//Se a label foi declarada corretamente, segue adiante.

		//Constrói a label, removendo o ':' presente no final
		actualLabel = token_getToken(actualTokens, 0);
		actualLabel[strlen(actualLabel) - 1] = '\0';
		
		//Busca pela label na lista de labels já declaradas.
		//Se existir, foi feita uma declaração duplicada.
		if(assembler_searchLabel(asmr, actualLabel) != 0)
		{
			//Libera regiões de memória que não serão mais utilizadas
			lista_free(asmr->labels);
			token_free(actualTokens);
			assembler_freeStrVector(ignoreList);
			asmr->labels = NULL;
			
			//Reposiciona o arquivo
			asmLoader_rewind(asmr->loader);
	
			//Lança o erro	
			asmError_setDesc(ASSEMBLERANALYSER_EUSER_DUPLABEL_MSG);

			//Retorna
			return (counter);
		}
		
		//Insere a label lista
		tmpLabel = label_new(actualLabel, counter);
//		tmpNode = node_new(tmpLabel, 0, sizeof(LABEL));
		tmpNode = lista_node_new(tmpLabel);
		lista_insertLastNode(asmr->labels, tmpNode);

		//Libera a região de memória que não será mais utilizada
		token_free(actualTokens);
		
		//Incrementa o contador de linha
		counter++;
	}

	assembler_freeStrVector(ignoreList);

	//Reposiciona no início do arquivo
	asmLoader_rewind(asmr->loader);
	
	//Retorna sucesso
	return (ASSEMBLER_SUCCESS);
}
