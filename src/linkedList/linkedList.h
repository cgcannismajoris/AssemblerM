/*
 * =================================================================================
 *        Arquivo:  lista.h
 *    	Descrição:  Cabeçalho do arquivo "lista.c"
 * =================================================================================
 */

#ifndef LINKED_LIST_LIBRARIE
#define LINKED_LIST_LIBRARIE

#include <stdint.h>

#include "node.h"

#define LIST_SUCCESS		 0
#define LIST_NULL_POINTER 	-2


#define NODE_REF_LENGHT 2
#define ANTE			0
#define PROX 			1


#define node_getAnte(X1)     node_getRef((X1), ANTE)
#define node_getProx(X2)     node_getRef((X2), PROX)

#define node_setAnteNull(Y1) node_setRef((Y1), NULL, ANTE)
#define node_setProxNull(Y2) node_setRef((Y2), NULL, PROX)



typedef int				LIST_INT;
typedef unsigned int	LIST_UINT;

typedef struct{
	
	NODE *root, *last;	
	uint64_t quant;

} LISTA, LIST, LINKED_LIST;

/* ----    Métodos Construtores e Destrutores    ---- */
/* Descrição	: Aloca uma nova estrutura do tipo LISTA na memória e retorna 
 * 				  seu ponteiro.
 * Argumentos	: void.
 * Retorno		: Ponteiro para a lista criada.
 * 	Se != NULL = Estrutura alocada com sucesso.
 * 	Se == NULL = Não foi possível alocar a estrutura.
 */
LIST *lista_new();

/* Descrição	: Desaloca da memória uma lista inteira (Lista e Elementos).
 * Argumentos	: 
 * 	 -> LISTA *this = Lista a ser desalocada da memória.
 * Retorno		: Void.
 */
LIST_INT lista_free(LISTA *this);

/* Descrição	: Desaloca da memória todos os elementos de uma lista.
 * Argumentos	: 
 * 	 -> LISTA *this = Lista a ter seus elementos apagados.
 * Retorno		: Void.
 */
LIST_INT lista_clear(LISTA *this);

NODE *lista_node_new(void *data, uint32_t size);

/* ---- Métodos de inserção e Remoção de elemtos ---- */
/* Descrição	: Insere um nó em uma lista encadeada na posição desejada.
 * Argumentos	: 
 * 	 -> LISTA *this = Lista que irá receber o nó.
 * 	 -> NODE *no	= Nó a ser inserido na lista.
 * 	 -> int pos		= Posição a ser inserido o nó.
 * 	     Se == 0 O nó passa a ser a raiz da lista.
 * 	     Se > quantidade total de elementos o nó passa a ser o ultimo elemento.
 * Retorno		: Void.
 */
void lista_insertNode(LISTA *this, NODE *no, int pos);

void lista_insertLastNode(LISTA *this, NODE *no);

/* Descrição	: Remove o  nó recebido da lista também recebida.
 * Argumentos	: 
 * 	 -> LISTA *this = Lista a ter o nó removido.
 * 	 -> NODE *no 	= Nó a ser removido.
 * Retorno		:
 *   -> Se == 1 o nó foi removido com sucesso.
 *   -> Se == -1 ocorreu um erro na remoção do nó.
 */
int lista_removeNode(LISTA *this, NODE *no);

/* Descrição	: Remove a raiz de uma lista encadeada e retorna o ponteiro 
 * 				  o nó removido.
 * Argumentos	: 
 * 	 -> LISTA *this = Lista a ter a raiz removida.
 * Retorno		: Ponteiro para o nó removido.
 * 	 Se != NULL = Nó removido com sucesso.
 * 	 Se == NULL = Lista vazia ou inválida.
 */
NODE *lista_removeRaiz(LISTA *this);



/*  ----     Exibição de Elementos      ---- */
/* Descrição	: Imprime na tela todos os elementos de uma lista encadeada.
 * Argumentos	: 
 * 	 -> LISTA *this = Lista a ser exibida.
 * Retorno		: Quantidade de elementos exibidos.
 */
int lista_printLista(LISTA *this, void (*show_na_tela)(void*));

/* ----              Geters e Seters             ---- */
//Retorna o endereço do nó raiz
NODE *lista_getRaiz(LISTA *this);
//Seta o nó da raiz
void lista_setRaiz(LISTA *this, NODE *no);
//Retorna o ultimo elemento da lista
NODE *lista_getLast(LISTA *this);
//Seta o ultimo elemento da lista
void lista_setLast(LISTA *this, NODE *last);
//Retorna a quantidade de elementos da lista
uint64_t lista_getQuant(LISTA *this);
//Seta a quantidade de elementos da lista encadeada.
void lista_setQuant(LISTA *this, int quant);

#endif