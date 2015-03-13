/*
 * =================================================================================
 *
 *        Arquivo:  genericDataManipulation.h
 *    	Descrição:  
 *     Compilador:  gcc
 *          Autor:  Gustavo Freitas de Amorim, gustavofreitasamorim@gmail.com
 *
 * =================================================================================
 */

#ifndef GENERIC_DATA_MANIPULATION
#define GENERIC_DATA_MANIPULATION

#include <stdlib.h>

#define GENERIC_FALSE			 0
#define GENERIC_TRUE			 1

#define GENERIC_SUCCESS 		 0
#define GENERIC_SET_ERROR 		-1
#define GENERIC_NULL_POINTER	-2

typedef unsigned char 	GENERIC_UCHAR;
typedef int				GENERIC_INT;
typedef unsigned char 	GENERIC_BOOL;

typedef struct{

	void*			data;
	GENERIC_INT 	data_ID;

} GENERIC;

GENERIC *newGenericData(void *data, GENERIC_UCHAR ID);

GENERIC_INT free_genericData(GENERIC **this);

GENERIC_BOOL generic_isDataIDEqual(GENERIC *one, GENERIC *two);

GENERIC_BOOL generic_compare(GENERIC *one, GENERIC *two, char (*data_compare)());

GENERIC_INT generic_setData(GENERIC *this, void *data, GENERIC_UCHAR data_ID);

void *generic_getData(GENERIC *this);

GENERIC_INT generic_getID(GENERIC *this);



#endif
