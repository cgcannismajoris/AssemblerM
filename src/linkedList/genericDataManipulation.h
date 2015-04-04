/*
 * Nome do Arquivo:  genericDataManipulation.h
 *       Descrição:  TAD especializado em manipular tipos de dados genéricos.
 *
 * Exported functions from genericDataManipulation.c.
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

#ifndef GENERIC_DATA_MANIPULATION_HEADER
#define GENERIC_DATA_MANIPULATION_HEADER

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

GENERIC *genericData_new(void *data, GENERIC_UCHAR ID);

GENERIC_INT genericData_free(GENERIC *this);

GENERIC_BOOL generic_isDataIDEqual(GENERIC *one, GENERIC *two);

GENERIC_BOOL generic_compare(GENERIC *one, GENERIC *two, char (*data_compare)());

GENERIC_INT generic_setData(GENERIC *this, void *data, GENERIC_UCHAR data_ID);

void *generic_getData(GENERIC *this);

GENERIC_INT generic_getID(GENERIC *this);



#endif
