/*
 * Nome do Arquivo:  linkedList.c
 *       Descrição:  Implementação dos métodos de lista encadeada genérica.
 *
 * Generic Linked List for AssemblerM.
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


#include "linkedList.h"

/*  ----  Métodos Construtores e Destrutores ---- */
LIST *lista_new(){
	//Aloca a lista na memoria	
	LISTA *new = (LISTA*) malloc(sizeof(LISTA));

	if(new != NULL){	
		//Inicializa os valores
		new->quant = 0;
		new->root = new->last = NULL;
	}
	return (new);
}

LIST_INT lista_free(LISTA *this){
	if(this != NULL){
		lista_clear(this);
		free(this);
		
		return (LIST_SUCCESS);
	}

	return (LIST_NULL_POINTER);
}

LIST_INT lista_clear(LISTA *this){
	
	NODE *aux, *temp;
	
	if(this != NULL){

		aux = lista_getLast(this);
		while(aux != NULL){
			temp = node_getAnte(aux);
			node_free(aux); //Nao e necessario verificar o retorno de node_free
							 //while ja garante a validade do no
			aux = temp;
		}

		lista_setRaiz(this, NULL);
		lista_setLast(this, NULL);
		lista_setQuant(this, 0);

		return (LIST_SUCCESS);
	}

	return (LIST_NULL_POINTER);
}

NODE *lista_node_new(void *data){
	return(node_new(data, 0, NODE_REF_LENGTH));
}

/* ---- Métodos de inserção e Remoção de elemtos ---- */
void lista_insertNode(LISTA *this, NODE *no, int pos){
	//Se a posicao for invalida, retorna
	if(pos < 0) return;
	
	//Se a lista esta vazia, coloca o no na raiz
	if(lista_getRaiz(this) == NULL){
		lista_setRaiz(this, no);
		lista_setLast(this, no);
	}
	
	//Se deseja inserir na primeira posicao
	else if(pos == 0){
		
		NODE *aux;

		aux = this->root; //Salva a raiz
		lista_setRaiz(this, no); //raiz se torna no
		node_conect(no, aux, PROX, ANTE);
	}
	
	//Se deseja inserir no final da lista
	else if(pos >= lista_getQuant(this)){

		//faz com que o ultimo elemento aponte para o nó recebido
		node_conect(lista_getLast(this), no, PROX, ANTE);

		lista_setLast(this, no);
	}
	
	//se deseja inserir um elemento no meio da lista
	else{
		
		NODE *aux;
		int cont = 0;

		//Percorre a lista ate a posicao desejada
		aux = lista_getRaiz(this);
		while(cont < pos){
			aux = node_getProx(aux);
			cont++;
		}

		//no passa a apontar para o proximo de aux
		node_conect(no, node_getProx(aux), PROX, ANTE);
		//aux passa a apontar para no
		node_conect(aux, no, PROX, ANTE);
	}
	//Incrementa a quantidade de elementos	
	this->quant++;	
}

void lista_insertLastNode(LISTA *this, NODE *no){
	
	if(this != NULL && no != NULL){
		if(lista_getQuant(this) > 0){
			node_conect(lista_getLast(this), no, PROX, ANTE);
			lista_setLast(this, no);
			node_setProxNull(no);
		}
		else{
			lista_setLast(this, no);
			lista_setRaiz(this, no);
			node_setProxNull(no);
			node_setAnteNull(no);
		}
		this->quant++;
	}

}

int lista_removeNode(LISTA *this, NODE *no){
	
	if(this != NULL && no != NULL){
		if(lista_getQuant(this) > 0){
			//Se o nó é a raiz...
			if(no == lista_getRaiz(this)){
				lista_setRaiz(this, node_getProx(no));
				if(lista_getRaiz(this) != NULL){
					node_setAnteNull(lista_getRaiz(this));
				}
			}
			//Se o nó é o ultimo..
			else if(no == lista_getLast(this)){
				lista_setLast(this, node_getAnte(no));
				if(lista_getLast(this) != NULL){
					node_setProxNull(lista_getLast(this));
				}
			}
			//se o nó está no meio...
			else{
				node_conect(node_getAnte(no), node_getProx(no), PROX, ANTE);	
			}
			this->quant--;
			return(1);
		}
	}
	return (-1);
}

NODE *lista_removeRaiz(LISTA *this){

	NODE *root = NULL;

	if(this != NULL){
		if(lista_getQuant(this) > 0){
			root = lista_getRaiz(this);

			if(node_getProx(root) != NULL){
				lista_setRaiz(this, node_getProx(root));
				node_setAnteNull(lista_getRaiz(this));
			}
			else{
				lista_setRaiz(this, NULL);
			}

			node_setProxNull(root);
			node_setAnteNull(root);
			//Decrementa a quantidade de elementos
			lista_setQuant(this, (lista_getQuant(this) - 1));

			//Se acabaram os elementos...
			if(lista_getQuant(this) == 0){
				//Indica que a raiz e nula
				lista_setRaiz(this, NULL);
				lista_setLast(this, NULL);
			}
		}
	}
	return root;
}


NODE *lista_getNode(LISTA *this, uint64_t pos)
{

	NODE *tmp;

	if(pos >= this->quant)
		return (NULL);
	
	tmp = this->root;

	while(pos > 0)
	{
		tmp = node_getProx(tmp);
		pos--;
	}

	return (tmp);
}

/*  ----     Exibição de Elementos      ---- */
int lista_printLista(LISTA *this, void (*show_na_tela)(void*)){
	
	//Se a lista estiver vazia, retorna -1	
	if (lista_getRaiz(this) == NULL) return(-1);

	//Declaração das variaveis
	int i;
	NODE *aux;

	aux = lista_getRaiz(this); //aux recebe o ponteiro para a raiz
	
	//Percorre toda a lista exibindo cada elemento
	for(i = 1; i <= lista_getQuant(this); i++){
		show_na_tela(aux); //imprime o no na tela
		aux = node_getProx(aux); //"caminha" para o proximo nó
	}

	return(i); //Retorna a quantidade de elementos exibidos
}

/*  ----     Procura de elementos       ---- */
NODE *lista_search(LISTA *this, const void *key, 
				int (*compar)(const void *, const void *)){
	
	NODE *result = NULL;
	NODE *temp;

	if(this == NULL || compar == NULL){
		return (NULL);
	}
	
	temp = this->root;

	while(temp != NULL){
		if(compar(key, node_getData(temp)) == 0){
			return(temp);
		}
		else{
			temp = node_getProx(temp);
		} 
	}

	return (NULL);
}
 
long int lista_search_getPos(LISTA *this, const void *key, 
				int (*compar)(const void *, const void *)){
	NODE *result = NULL;
	NODE *temp;
	uint64_t counter = 0;	

	if(this == NULL || compar == NULL){
		return (-1);
	}
	
	temp = this->root;

	while(temp != NULL){
		if(compar(key, node_getData(temp)) == 0){
			return(counter);
		}
		else{
			temp = node_getProx(temp);
		} 
		counter++;
	}

	return (-1);
}

/*  ----        Geters e Seters         ---- */
NODE *lista_getRaiz(LISTA *this){
	return(this->root); //Retorna a raiz da lista recebida
}

void lista_setRaiz(LISTA *this, NODE *no){
	this->root = no; //Seta a raiz como sendo o nó recebido
}

NODE *lista_getLast(LISTA *this){
	return(this->last);
}

void lista_setLast(LISTA *this, NODE *last){
	this->last = last;
}


uint64_t lista_getQuant(LISTA *this){
	return(this->quant); //Retorna a quantidade de elementos da lista recebida
}

void lista_setQuant(LISTA *this, int quant){
	this->quant = quant;
}
