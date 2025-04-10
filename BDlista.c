#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BDlista.h"
#include "lista.h"
#include "produto.h"

// TAI DE ORDEM 0 - "Base de Dados" lista

Lista* listas;		// array de ponteiros para Lista
int nl;				// valor maximo de listas no array
int listasAtuais;	// valor de quantas listas estão no array a qualquer momento

// Função que aloca memória para criar um array de ponteiros tipo Lista
void criarBDlista(int nListas) {
	int i;
	nl = nListas;
	listas = (Lista*)malloc(sizeof(Lista) * nListas);
	for (i = 0; i < nl; i++)
		listas[i] = NULL;		// preencher o array com posições vazias
	listasAtuais = 0;			// inicializar o numero de listas atuais
}

// Função que liberta memória criada do array de ponteiros tipo Lista
void apagarBDlista() {
	int i;
	for (i = 0; i < nl; i++)
		if (listas[i] != NULL)
			apagarLista(listas[i]); // liberta a memória de cada lista dentro do array
	free(listas);					// liberta a memória do array
}

// Função que retorna se a BDlista está cheia ou não
int BDlistaCheio() {
	return (nl == listasAtuais);
}

// Função que insere lista na BDlista e retorna sucesso ou insucesso
int inserirLista(Lista l)
{
	int i;
	for (i = 0; i < nl; i++)
		if (listas[i] == NULL) {	// Encontrou uma posição vazia
			listas[i] = l;			// Colocar ponteiro na posição encontrada
			listasAtuais++;			// Incrementar numero actual de produtos no array
			return 1;				// Sucesso a inserir nova lista
		}
	return 0; // Insucesso a inserir nova lista (array cheio)
}

// Função que liberta memória de uma Lista do array BDlista
void retirarLista(char* nome)
{
	int i;
	for (i = 0; i < nl; i++) {
		if (listas[i] != NULL && strcmp(daNomeLista(listas[i]), nome) == 0) {
			apagarLista(listas[i]);	// Liberta a memoria cujo ponteiro Produto com codigo dado
			listas[i] = NULL;		// coloca esse ponteiro a apontar para NULL (posição vazia)
			listasAtuais--;
			return;
		}
	}
}

// Função para retirar produto de todas as listas que tenham esse produto
void retirarTodosProdutoLista(Produto produto) {
	int i, j;
	for (i = 0; i < nl; i++) {
		if (listas[i] != NULL) {
			retirarProdutoLista(listas[i], produto, nl);
		}
	}
}

// Função para obter Lista por nome 
Lista obterListaPorNome(char* nome) {
	int i;
	for (i = 0; i < nl; i++) {
		if (listas[i] != NULL && strcmp(daNomeLista(listas[i]), nome) == 0) {
			return listas[i];
		}
	}
	return NULL;
}

// Função para listar listas de acordo com o tipo de listagem e filtro
void listarListas()
{
	int i, estaVazio = 1;
	for (i = 0; i < nl; i++) {
		if (listas[i] != NULL) {
			imprimirLista(listas[i], nl);
			estaVazio = 0;
		}
	}
	if (estaVazio)
		printf("| BDlista sem listas |\n");
}

