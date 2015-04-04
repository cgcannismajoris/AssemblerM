/*
 * Nome do Arquivo:  node.c
 *       Descrição:  Implementação do TAD de manipulação de nós genéricos.
 * 
 * Node for AssemblerM.
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

#include "node.h"

/* ----                Métodos Constrututores e Destrutures                 ----*/
NODE *node_new(void* data, GENERIC_UCHAR data_ID, NODE_UCINT node_ref_lenght){

	NODE_UINT i;
	NODE *new = (NODE*)malloc(sizeof(NODE));

	int *ref;

	if(new != NULL){
		
		//Armazena o dado no local adequado...
		new->data = genericData_new(data, data_ID);

		//Se existem nós nas redondezas...
		if(node_ref_lenght != 0){
			new->ref = (NODE**)malloc(node_ref_lenght * sizeof(NODE*));	

			//Inicializando vetor de ponteiros das redondezas
			if(new->ref != NULL){
				ref = (int*)(&(new->ref_lenght));
				*ref = node_ref_lenght;
//				new->ref_lenght = node_ref_lenght;
				for(i = 0; i < node_ref_lenght; i++){
					(new->ref)[i] = NULL;
				}
			}
			//Erro ao alocar vetor de ponteiros
			//data não é desalocado!
			else{
				free(new);
				return(NULL);
			}
		}
		//Se não existem nós nas redondezas...
		else{
			new->ref = NULL;
			ref = (int*)&(new->ref_lenght);
			*ref = node_ref_lenght;
//			new->ref_lenght = 0;
		}
	}
	

	return (new);
}

NODE_UINT node_free(NODE *this){

	NODE_UINT ref_lenght;

	if(this != NULL){
		
		//Destruição do conteúdo interno do nó
		//Destruição do dado armazenado
		genericData_free( this->data );

		//Remoção das referências para as redondezas
		for(ref_lenght = 0; ref_lenght < this->ref_lenght; ref_lenght++){
			this->ref = NULL;
		}

		free(this);

		return (NODE_SUCCESS);
	}

	return (NODE_NULL_POINTER);
}

/*----               Métodos de Interrelacionamento entre nos               ----*/
NODE_INT node_conect(NODE *ante, NODE *post, NODE_UINT ref_post_in_ante, NODE_UINT ref_ante_in_post){
	
	if(ante != NULL && post != NULL){
		if(ref_post_in_ante < ante->ref_lenght && ref_ante_in_post < post->ref_lenght){
			(ante->ref)[ref_post_in_ante] = post;
			(post->ref)[ref_ante_in_post] = ante;

			return (NODE_SUCCESS);
		}
		else{
			return (NODE_INVALID_REF_ID);
		}
	}
	
	return (NODE_NULL_POINTER);
}

/*----                      Métodos de Análize de nós                       ----*/
NODE_BOOL node_isDataTypeEqual(NODE *one, NODE *two){
	
	if(one != NULL && two != NULL){
		if(generic_isDataIDEqual(one->data, two->data) == GENERIC_TRUE){
			return (NODE_TRUE);
		}
		else{
			return (NODE_FALSE);
		}
	}

	return (NODE_NULL_POINTER);

}

NODE_BOOL node_generic_compare(NODE *one, NODE *two, char (*data_compare)()){
	
	return(generic_compare(one->data, two->data, data_compare));

}

/*----                     Métodos de Exibição de dados                     ----*/
NODE_INT node_show(NODE *this, char (*show)()){
	
	if(this != NULL){

		show(this->data);
		return (NODE_SUCCESS);
	}

	return (NODE_NULL_POINTER);
}

/*----           Métodos de Armazenamento e Recuperação de Dados            ----*/
void *node_getData(NODE *this){
	
	if(this != NULL){
		return (generic_getData(this->data));
	}

	return (NULL);
}

NODE_INT node_getDataID(NODE *this){
	
	if(this != NULL){
		return (generic_getID(this->data));
	}

	return (NODE_NULL_POINTER);
}

NODE *node_getRef(NODE *this, NODE_UINT ref_ID){

	if(this != NULL && this->ref_lenght > ref_ID){
		return ((this->ref)[ref_ID]);
	}

	return (NULL);
}	

NODE_INT node_getRefLenght(NODE *this){
	
	if(this != NULL){
		return (this->ref_lenght);
	}
	
	return (0);
}

NODE_INT node_setData(NODE *this, void *data, GENERIC_UCHAR data_ID){
	
	if(this != NULL){
		generic_setData(this->data, data, data_ID);
		return (NODE_SUCCESS);
	}	
	
	return (NODE_SET_ERROR);
}

NODE_INT node_setRef(NODE *this, NODE *ref, NODE_UINT ref_ID){
	
	if(this != NULL && this->ref_lenght > ref_ID){
		(this->ref)[ref_ID] = ref;
		return (NODE_SUCCESS);
	}
	
	return (NODE_SET_ERROR);
}

