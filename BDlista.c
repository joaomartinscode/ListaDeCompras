#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BDlista.h"
#include "lista.h"
#include "produto.h"

// TAI DE ORDEM 0 - "Base de Dados" lista

Lista* listas;		// array de ponteiros para Lista
int nl;				// valor maximo de listas no array
int listasAtuais;	// valor de quantas listas est�o no array a qualquer momento

// Fun��o que aloca mem�ria para criar um array de ponteiros tipo Lista
void criarBDlista(int nListas) {
	int i;
	nl = nListas;
	listas = (Lista*)malloc(sizeof(Lista) * nListas);
	for (i = 0; i < nl; i++)
		listas[i] = NULL;		// preencher o array com posi��es vazias
	listasAtuais = 0;			// inicializar o numero de listas atuais
}

// Fun��o que liberta mem�ria criada do array de ponteiros tipo Lista
void apagarBDlista() {
	int i;
	for (i = 0; i < nl; i++)
		if (listas[i] != NULL)
			apagarLista(listas[i]); // liberta a mem�ria de cada lista dentro do array
	free(listas);					// liberta a mem�ria do array
}

// Fun��o que retorna se a BDlista est� cheia ou n�o
int BDlistaCheio() {
	return (nl == listasAtuais);
}

// Fun��o que insere lista na BDlista e retorna sucesso ou insucesso
int inserirLista(Lista l)
{
	int i;
	for (i = 0; i < nl; i++)
		if (listas[i] == NULL) {	// Encontrou uma posi��o vazia
			listas[i] = l;			// Colocar ponteiro na posi��o encontrada
			listasAtuais++;			// Incrementar numero actual de produtos no array
			return 1;				// Sucesso a inserir nova lista
		}
	return 0; // Insucesso a inserir nova lista (array cheio)
}

// Fun��o que liberta mem�ria de uma Lista do array BDlista
void retirarLista(char* nome)
{
	int i;
	for (i = 0; i < nl; i++) {
		if (listas[i] != NULL && strcmp(daNomeLista(listas[i]), nome) == 0) {
			apagarLista(listas[i]);	// Liberta a memoria cujo ponteiro Produto com codigo dado
			listas[i] = NULL;		// coloca esse ponteiro a apontar para NULL (posi��o vazia)
			listasAtuais--;
			return;
		}
	}
}

// Fun��o para retirar produto de todas as listas que tenham esse produto
void retirarTodosProdutoLista(Produto produto) {
	int i, j;
	for (i = 0; i < nl; i++) {
		if (listas[i] != NULL) {
			retirarProdutoLista(listas[i], produto, nl);
		}
	}
}

// Fun��o para obter Lista por nome 
Lista obterListaPorNome(char* nome) {
	int i;
	for (i = 0; i < nl; i++) {
		if (listas[i] != NULL && strcmp(daNomeLista(listas[i]), nome) == 0) {
			return listas[i];
		}
	}
	return NULL;
}

// Fun��o para listar listas de acordo com o tipo de listagem e filtro
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

