/* main.c
 * Ferramenta dicwriter para escrita do dicionário (DICTIONARY).
*/
	
#include <stdio.h>
#include <stdio_ext.h>
#include <signal.h>

#include "../../src/dictionary/dicWriter/dicWriter.h"


#define STR_MAXLENGTH	256
#define STR_OPMAXLENGTH 3


int translateOpcode(char *str);

void writeMsg(uint8_t id);

int main(int argc, char **argv)
{

	DICWRITER *output;
	
	char end = 's';
	char instPattern[STR_MAXLENGTH];
	char instTranslation[STR_MAXLENGTH];


	if(argc < 2){
		writeMsg(1);
		return (-1);
	}
	if(strncmp(argv[1], "-help", 6) == 0){
		writeMsg(6);
		return (0);
	}

	output = dicWriter_new(argv[1]);

	while(end != 'n'){

		writeMsg(2);
		scanf("\n%[^\n]", instPattern);

		writeMsg(3);
		scanf("\n%[^\n]", instTranslation);
		
		while(translateOpcode(instTranslation) == -1){
			writeMsg(4);
			scanf("\n%[^\n]", instTranslation);
		}

		dicWriter_writeInst(output, instPattern, instTranslation);
		
		writeMsg(5);
		scanf(" %c", &end);
		while(end != 'n' && end != 's'){
			scanf(" %c", &end);
		}

	}

	dicWriter_free(output);

    return 0;
}


int translateOpcode(char *str){

	int i, j;
	char opStr[STR_OPMAXLENGTH];

	for(i = 0; i < STR_OPMAXLENGTH && str[i] != ' '; i++){
		opStr[i] = str[i];
		str[i] = ' ';
	}
	opStr[i] = '\0';

	str[0] = (uint8_t)atoi(opStr);
	
	//Se inseriu um opcode maior do que o limite...
	if(str[i] != ' ' || str[0] > 63){
		return (-1);
	}

	for(j = 1, i = i; i < STR_MAXLENGTH && j  < STR_MAXLENGTH; j++, i++){
		str[j] = str[i];
	}

	str[j] = '\0';

	return (0);
}

void writeMsg(uint8_t id){
	switch(id){
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
		default:
			printf("\n\nERROR: MSG NOT FOUND!\n\n");
	}
}
