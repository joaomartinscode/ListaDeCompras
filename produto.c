#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "produto.h"

// TAI DE ORDEM 1 - Produto

struct produto {
	char* nome;
	char* tipo;
	float preco;
	char* loja;
};

// Fun��o para alocar mem�ria para um array de chars + copiar string para esse array
static char* mystrcopyProduto(char* str) {
	char* tempstr = malloc(sizeof(char) * (strlen(str) + 1));
	strcpy(tempstr, str);
	return tempstr;
}

// Fun��o para alocar mem�ria para uma vari�vel do tipo "Produto" + copiar dados para essa mem�ria
Produto criarProduto(char* nome, char* tipo) {
	Produto novoProduto = (Produto)malloc(sizeof(struct produto));
	novoProduto->nome = mystrcopyProduto(nome);	// Nome do produto
	novoProduto->tipo = mystrcopyProduto(tipo);	// Tipo de produto
	novoProduto->preco = 2147483647;		// Pre�o n�o inicializado (MAX_FLOAT)
	novoProduto->loja = NULL;				// String "loja" n�o inicializada (NULL)
	return novoProduto;
}

// Fun��o para libertar mem�ria dum Produto
void apagarProduto(Produto produto) {
	free(produto->nome);
	free(produto->tipo);
	free(produto->loja);
	free(produto);
}

// Fun��o "Get" nome de produto
char* daNomeProduto(Produto produto) {
	return produto->nome;
}

// Fun��o "Get" tipo de produto
char* daTipoProduto(Produto produto) {
	return produto->tipo;
}

// Fun��o "Get" pre�o de produto
float daPrecoProduto(Produto produto) {
	return produto->preco;
}

// Fun��o "Get" loja de produto
char* daLojaProduto(Produto produto) {
	return produto->loja;
}

// Fun��o para alterar nome de produto
void alterarNomeProduto(Produto produto, char* novonome) {
	free(produto->nome);
	produto->nome = mystrcopyProduto(novonome);
}

// Fun��o para alterar pre�o e loja de produto
void alterarPrecoLojaProduto(Produto produto, float novopreco, char* novoloja) {
	if (produto->preco > novopreco) {
		produto->preco = novopreco;
		free(produto->loja);
		produto->loja = mystrcopyProduto(novoloja);
	}
}

// Fun��o para imprimir informa��o de produto
void imprimirProduto(Produto produto) {
	printf("| %20s ", produto->nome);
	printf("| %20s |", produto->tipo);
	if (produto->loja != NULL) {
		printf("| Preco: %4.2f ", produto->preco);
		printf("| Loja: %s |", produto->loja);
	}
	printf("\n");
}
