/* 
 * Nome do Arquivo:  main.c
 *       Descrição:  Ferramenta dicwriter para escrita do dicionário (DICTIONARY).
 * 
 * Tool DicWriter for AssemblerM.
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
#include <stdio_ext.h>
#include <signal.h>

#include "../../src/dictionary/dicWriter/dicWriter.h"
#include "../../src/linkedList/linkedList.h"
#include "../../src/dictionary/entry/entry.h"

#define STR_MAXLENGTH	256
#define STR_OPMAXLENGTH 3

#define FATAL_ERROR_ALLOC_MSGID    100
#define SUCCESS_MSGID              90

int translateOpcode(char *str);

void writeMsg(uint8_t id);

int main(int argc, char **argv)
{

	LIST *entryList;
	NODE *no;
	ENTRY *entry;
	DICWRITER *writer;
	
	char end = 's';
	char instPattern[STR_MAXLENGTH];
	char instTranslation[STR_MAXLENGTH];

	if(argc < 2)
	{
		writeMsg(1);
		return (-1);
	}

	if(strncmp(argv[1], "-help", 6) == 0)
	{
		writeMsg(6);
		return (0);
	}

	entryList = lista_new();
	writer = dicWriter_new(argv[1]);

	if(entryList == NULL || writer == NULL)
	{
		free(entryList);
		free(writer);

		writeMsg(FATAL_ERROR_ALLOC_MSGID);

		return (-1);
	}

	while(end != 'n')
	{
		writeMsg(2);
		scanf("\n%[^\n]", instPattern);

		writeMsg(3);
		scanf("\n%[^\n]", instTranslation);
		
		while(translateOpcode(instTranslation) == -1)
		{
			writeMsg(4);
			scanf("\n%[^\n]", instTranslation);
		}
		
		//Instancia os novos elementos da lista
		entry = entry_new(instPattern, instTranslation);
		no = lista_node_new(entry);
	
		//Insere os novos elementos na lista
		lista_insertLastNode(entryList, no);

		//Se ocorreu algum problema
		if(no == NULL || entry == NULL)
		{
			writeMsg(FATAL_ERROR_ALLOC_MSGID);

			lista_free(entryList);
			entry_free(entry);
			node_free(no);

			return (-1);
		}

		writeMsg(5);
		scanf(" %c", &end);
		while(end != 'n' && end != 's')
		{
			scanf(" %c", &end);
		}
	}

	writeMsg(7);

	//Grava a quantidade de verbetes gerados 
	dicWriter_writeQtdInst(writer, lista_getQuant(entryList));

	//Grava os verbetes
	while((no = lista_removeRaiz(entryList)) != NULL)
	{	
		entry = (ENTRY*)node_getData(no);
		
		dicWriter_writeInst(writer, entry_getPattern(entry), 
						       entry_getTranslation(entry));

		node_free(no);
	}
	
	writeMsg(SUCCESS_MSGID);

	dicWriter_free(writer);
	lista_free(entryList);
   
   	return 0;
}


int translateOpcode(char *str)
{
	int i, j;
	char opStr[STR_OPMAXLENGTH];

	for(i = 0; i < STR_OPMAXLENGTH && str[i] != ' ' && str[i] != '\0'; i++)
	{
		opStr[i] = str[i];
		str[i] = ' ';
	}
	opStr[i] = '\0';

	str[0] = (uint8_t)atoi(opStr);
	
	//Se inseriu um opcode maior do que o limite...
	if(str[i] != ' ' || str[0] > 62)
	{
		return (-1);
	}

	for(j = 1, i = i; i < STR_MAXLENGTH && j  < STR_MAXLENGTH && str[i] != '\0'; 
					j++, i++)
	{
		str[j] = str[i];
	}

	str[j] = '\0';

	return (0);
}

void writeMsg(uint8_t id)
{
	switch(id)
	{
		case 1:
			printf("Sem arquivo de saída.\n");
			printf("Utilize -help para obter ajuda.\n");
			break;

		case 2:
			printf("Insira o padrão da instrução: ");
			break;

		case 3:
			printf("Insira a tradução do padrão: ");
			break;

		case 4:
			printf("Opcode muito grande ou inválido! Tente novamente.\n");
			break;

		case 5:
			printf("Adicionar mais? (s - SIM // n - NÃO) ");
			break;

		case 6:
			printf("Padrão da instrução:\n");
			printf(" -> Padrão de instrução:\n");
		   	printf("  $ -> Registrador\n");
			printf("  %% -> Próxima instrução\n");
			printf("  Exemplo: ADD $1 $2 $3 %%\n\n");
			printf(" -> Tradução do padrão:\n");
		   	printf("  $ -> Registrador\n");
			printf("  %% -> Próxima instrução\n");
			printf("  Exemplo: 12 $1 $2 $3 %%\n");
			break;
		case 7:
			printf("Gravando dados no arquivo...");
			break;

		case SUCCESS_MSGID:
			printf("SUCESSO!\n");
			break;

		case FATAL_ERROR_ALLOC_MSGID:
			printf("\n\nFalha na alocação de memória!\n\n");
			break;
		default:
			printf("\n\nERROR: MSG NOT FOUND!\n\n");
	}
}

void asmerror_setinst(char *erro)
{
	printf("Um erro ocorreu: %s", erro);
}
