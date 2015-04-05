/*
 * Nome do Arquivo:  dictionary.c
 *       Descricao:  Implementação do TAD DICTIONARY.
 * 
 * Dictionary for AssemblerM.
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

#include "dictionary.h"

DICTIONARY *dic_new(const char *filename)
{
    DICTIONARY *novo;

    if ((novo = (DICTIONARY*)malloc(sizeof(DICTIONARY))) == NULL)
    {
        asmError_setDesc(DICTIONARY_EALLOC_MSG);
        return DICTIONARY_EALLOC;
    }

    if ((novo->loader = dicLoader_new(filename)) == NULL)
    {
        free(novo);
        return DICTIONARY_EALLOC;
    }

	novo->qtdEntry = dicLoader_getQtdInst(novo->loader);

    if ((novo->verbetes = (ENTRY**)malloc(sizeof(ENTRY*) * novo->qtdEntry)) == NULL)
    {
        asmError_setDesc(DICTIONARY_ELOAD_MSG);

        dicLoader_free(novo->loader);
        free(novo);
        return DICTIONARY_EALLOC;
    }

	return novo;
}

void dic_free(DICTIONARY *dic)
{
    dicLoader_free(dic->loader);

    for(--dic->qtdEntry; dic->qtdEntry != 0; dic->qtdEntry--)
        entry_free(dic->verbetes[dic->qtdEntry]);
		
    free(dic->verbetes);
    free(dic);
}

static int __dic_search_compar(const void *one, const void *two){
	
	//*one -> string enviada a bsearch como argumento
	//*two -> ponteiro para a posição do vetor com o ponteiro para a estrutura ENTRY

	uint64_t one_length = strlen(one);
	const char *pattern = entry_getPattern(*(ENTRY**)two);
	
	return (strncasecmp(one, pattern, one_length));
}

ENTRY *dic_search(DICTIONARY *dic, const char *nomeOperacao)
{
	char *nomeOperacao_ex;
	
	if(nomeOperacao == NULL)
		 return (DICTIONARY_BSEARCH_NOTFOUND);

	nomeOperacao_ex = (char*)malloc((sizeof(char) * strlen(nomeOperacao)) + 1);

	strcpy(nomeOperacao_ex, nomeOperacao);
	nomeOperacao_ex[strlen(nomeOperacao)] = ' ';
	nomeOperacao_ex[strlen(nomeOperacao) + 1] = '\0';

	ENTRY **result = bsearch(nomeOperacao_ex, dic->verbetes, dic->qtdEntry, 
					sizeof(ENTRY**), __dic_search_compar);

    if(result != DICTIONARY_BSEARCH_NOTFOUND)
		return (*result);

    return (DICTIONARY_BSEARCH_NOTFOUND);
}

int dic_save(DICTIONARY *dic, const char *filename)
{	
	return (-1);
}

static int __dic_load_compar(const void *one, const void *two){

	//*one -> ENTRY enviado a qsort como argumento
	//*two -> ponteiro para a posição do vetor com o ponteiro para a estrutura ENTRY
	//		  que está sendo comparada atualmente
	
	const char *pattern_one = entry_getPattern(*(ENTRY**)one); 
	const char *pattern_two = entry_getPattern(*(ENTRY**)two);
	size_t length_nomeOp;
	uint32_t pattern_one_length = strlen(pattern_one);
	
	for(length_nomeOp = 0; length_nomeOp < pattern_one_length && 
					pattern_one[length_nomeOp] != ' '; length_nomeOp++){ }
	
	return (strncasecmp(pattern_one, pattern_two, length_nomeOp));
}

int dic_load(DICTIONARY *dic)
{	
	uint64_t count;
	uint64_t separator;
	char *verbete;

	for(count = 0; count < dic->qtdEntry; count++){

		verbete = dicLoader_getNextInst(dic->loader);
		
        if (verbete == NULL)
        {
			free(dic);
			return (DICTIONARY_ELOAD);
		}

		separator = 0;
		while(verbete[separator] != DICWRITER_SEPARATOR_CHR){
			separator++;
		}
		verbete[separator] = '\0';
		separator++;

		dic->verbetes[count] = entry_new(verbete, (char*)(verbete+separator));
		
		if(dic->verbetes[count] == NULL){
			free(dic);
			return (DICTIONARY_ELOAD);
		}
	}

	qsort(dic->verbetes, dic->qtdEntry, sizeof(ENTRY**), __dic_load_compar);

	return (0);
}
