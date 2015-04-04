/*
 * Nome do Arquivo:  node.h
 *       Descrição:  TAD para manipulação de nós genéricos.
 *
 * Exported functions from node.c.
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

#ifndef NODE_HEADER
#define NODE_HEADER

#include "genericDataManipulation.h"

#define NODE_FALSE				 0
#define NODE_TRUE				 1

#define NODE_SUCCESS		  	 0
#define NODE_SET_ERROR 			-1
#define NODE_NULL_POINTER  		-2
#define NODE_INVALID_REF_ID		-3

typedef int					NODE_INT;
typedef unsigned int 		NODE_UINT;
typedef unsigned const int 	NODE_UCINT;
typedef unsigned char		NODE_BOOL;

typedef struct node{
	GENERIC* 		data;

	struct node**	ref;
	NODE_UCINT		ref_lenght;
} NODE;

/* ----                Métodos Constrututores e Destrutures                 ----*/
NODE *node_new(void* data, GENERIC_UCHAR data_ID, NODE_UCINT node_ref_lenght);

NODE_UINT node_free(NODE *this);

/*----               Métodos de Interrelacionamento entre nos               ----*/
NODE_INT node_conect(NODE *ante, NODE *post, NODE_UINT ref_post_in_ante, NODE_UINT ref_ante_int_post);

/*----                      Métodos de Análize de nós                       ----*/
NODE_BOOL node_isDataTypeEqual(NODE *one, NODE *two);

NODE_BOOL node_generic_compare(NODE *one, NODE *two, char (*data_compare)());

/*----                     Métodos de Exibição de dados                     ----*/
NODE_INT node_show(NODE *this, char (*show)());

/*----           Métodos de Armazenamento e Recuperação de Dados            ----*/
void *node_getData(NODE *this);

NODE_INT node_getDataID(NODE *this);

NODE *node_getRef(NODE *this, NODE_UINT ref_ID);

NODE_INT node_getRefLenght(NODE *this);

NODE_INT node_setData(NODE *this, void *data, GENERIC_UCHAR data_ID);

NODE_INT node_setRef(NODE *this, NODE *ref, NODE_UINT ref_ID);

#endif

