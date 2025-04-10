#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "lista.h"
#include "produto.h"

// TAI DE ORDEM 1 - Lista

// Metodo Struct Auxiliar:
struct produtonalista {
	Produto produto;
	int quantidade;
	int comprado;
};

struct lista {
	char* nomeLista;
	struct produtonalista* produtosNaLista;
};

// Função para alocar memória para um array de chars + copiar string para esse array
static char* mystrcopyLista(const char* str) {
	char* tempstr = malloc(sizeof(char) * (strlen(str) + 1));
	strcpy(tempstr, str);
	return tempstr;
}

// Função para alocar memória para uma variável do tipo "Lista" juntamente com array de structs auxiliares "produtonalista"
Lista criarLista(char* nome, int n) {
	Lista novaLista = (Lista)malloc(sizeof(struct lista));
	novaLista->produtosNaLista = malloc(sizeof(struct produtonalista) * n);
	novaLista->nomeLista = mystrcopyLista(nome);
	for (int i = 0; i < n; i++) {
		novaLista->produtosNaLista[i].produto = NULL;
		novaLista->produtosNaLista[i].quantidade = 0;
		novaLista->produtosNaLista[i].comprado = 0;
	}
	return novaLista;
}

// Função para libertar memória de uma Lista
void apagarLista(Lista lista) {
	if (lista != NULL) {
		free(lista->nomeLista); // liberta a memoria do array de chars do nome
		free(lista->produtosNaLista); // liberta a memoria do array produtosNaLista sem apagar os produtos em si
		free(lista); // liberta o ponteiro lista
	}
}

// Função "get" o nome da lista
char* daNomeLista(Lista lista) {
	return lista->nomeLista;
}

// Função para alterar nome da lista
void alterarNomeLista(Lista lista, char* novonome) {
	free(lista->nomeLista);
	lista->nomeLista = mystrcopyLista(novonome);
}

void alterarCompradoLista(Lista lista, char* nomeProduto, int novoComprado, int n) {
	int i;
	for (i = 0; i < n; i++) {
		if (lista->produtosNaLista[i].produto != NULL && strcmp(daNomeProduto(lista->produtosNaLista[i].produto), nomeProduto) == 0) {
			lista->produtosNaLista[i].comprado = n;
		}
	}
}

// Função para adicionar um produto à lista
void adicionarProdutoLista(Lista lista, Produto produto, int quantidade, int n) {
	int i;
	for (i = 0; i < n; i++) {
		if (lista->produtosNaLista[i].produto == NULL) {
			lista->produtosNaLista[i].produto = produto;
			lista->produtosNaLista[i].quantidade = quantidade;
			return;
		}
	}
}

// Função para retirar um produto à lista
void retirarProdutoLista(Lista lista,Produto produto, int n) {
	int i;
	for (i = 0; i < n; i++) {
		if (lista->produtosNaLista[i].produto != NULL && strcmp(daNomeProduto(lista->produtosNaLista[i].produto), daNomeProduto(produto)) == 0) {
			lista->produtosNaLista[i].produto = NULL; 
			lista->produtosNaLista[i].quantidade = 0;
			return;
		}
	}
}

// Função para procurar um produto na lista por nome
Produto obterProdutoListaPorNome(Lista lista, Produto produto, int n) {
	int i;
	for (i = 0; i < n; i++) {
		if (lista->produtosNaLista[i].produto != NULL && strcmp(daNomeProduto(lista->produtosNaLista[i].produto), daNomeProduto(produto)) == 0) {
			return lista->produtosNaLista[i].produto;
		}
	}
	return NULL;
}

// Função para definir todos os produtos de uma lista como nao comprados
void definirProdutosNComprados(Lista lista, int n) {
	int i;
	for (i = 0; i < n; i++) {
		if (lista->produtosNaLista[i].produto != NULL){
			lista->produtosNaLista[i].comprado = 0;
		}
	}
}

// Função para imprimir informações da lista
void imprimirLista(Lista lista, int n) {
	printf("\n| Nome: %10s |\n", lista->nomeLista);
	for (int i = 0; i < n; i++) {
		if (lista->produtosNaLista[i].produto != NULL) { // ponteiro para Produto que está dentro da struct auxiliar
			imprimirProduto(lista->produtosNaLista[i].produto);
			printf("| Quantidade: %d |", lista->produtosNaLista[i].quantidade);
			if (lista->produtosNaLista[i].comprado == 0)
				printf(" Comprado: NAO |");
			else {
				printf(" Comprado: SIM |");
			}
			printf("\n");
		}
	}
}