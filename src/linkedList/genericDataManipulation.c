/*
 * =================================================================================
 *
 *        Arquivo:  genericDataManipulation.c
 *    	Descrição:  
 *     Compilador:  gcc
 *          Autor:  Gustavo Freitas de Amorim, gustavofreitasamorim@gmail.com
 *
 * =================================================================================
 */


#include "genericDataManipulation.h"

/* ----                Métodos Constrututores e Destrutures                 ----*/
GENERIC *genericData_new(void *data, GENERIC_UCHAR ID){
	
	GENERIC *new = (GENERIC*)malloc(sizeof(GENERIC));

	if(new != NULL){
		new->data = data;
		new->data_ID = ID;
	}

	return(new);
}

GENERIC_INT genericData_free(GENERIC *this){
	if(this != NULL){
	
		//Apaga o conteúdo do tipo genérico
		this->data_ID = 0;
		this->data = 0;

		//Desalocando o conteúdo genérico
		free(this->data);
		//Desalocando o tipo GENERIC
		free(this);

		return (GENERIC_SUCCESS);
	}

	return (GENERIC_NULL_POINTER);
}

/*----                     Métodos de Análize de dados                      ----*/
GENERIC_BOOL generic_isDataIDEqual(GENERIC *one, GENERIC *two){
	if(one != NULL && two != NULL){
		if(one->data_ID == two->data_ID){
			return (GENERIC_TRUE);
		}
		else{
			return (GENERIC_FALSE);
		}
	}

	return (GENERIC_NULL_POINTER);
}

GENERIC_BOOL generic_compare(GENERIC *one, GENERIC *two, char (*data_compare)()){
	return(data_compare(one, two));
}

/*----           Métodos de Armazenamento e Recuperação de Dados            ----*/
GENERIC_INT generic_setData(GENERIC *this, void *data, GENERIC_UCHAR data_ID){
	if(this != NULL){
		this->data = data;
		this->data_ID = data_ID;

		return(GENERIC_SUCCESS);
	}

	return (GENERIC_NULL_POINTER);
}

GENERIC_INT generic_setID(GENERIC *this, GENERIC_UCHAR data_ID){
	if(this != NULL){
		this->data_ID = data_ID;
		
		return (GENERIC_SUCCESS);
	}

	return(GENERIC_NULL_POINTER);
}

void *generic_getData(GENERIC *this){
	if(this != NULL){
		return(this->data);
	}

	return (NULL);
}

GENERIC_INT generic_getID(GENERIC *this){
	if(this != NULL){
		return(this->data_ID);
	}

	return (GENERIC_NULL_POINTER);
}
