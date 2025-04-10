#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BDproduto.h"
#include "produto.h"

// TAI DE ORDEM 0 - "Base de Dados" produto

Produto* produtos;  // array de ponteiros para Produto
int np;				// valor maximo de produtos no array
int produtosAtuais; // valor de quantos produtos estão no array a qualquer momento

// Função que aloca memória para criar um array de ponteiros tipo Produto
void criarBDproduto(int nProdutos) {
	int i;
	np = nProdutos;
	produtos = (Produto*)malloc(sizeof(Produto) * nProdutos);

	if (produtos == NULL)
		return; // Linha de codigo caso malloc falhe (remove WARNING)

	for (i = 0; i < nProdutos; i++)
		produtos[i] = NULL;		// preencher o array com posições vazias
	produtosAtuais = 0;			// inicializar o numero de produtos atuais
}

// Função que liberta memória criada do array de ponteiros tipo Produto (necessário limpar memória alocada para listas)
void apagarBDproduto() {
	int i;

	// COLOCAR AQUI LOGICA QUE LIBERTA AS LISTAS PRIMEIRO --------------------------------------------------------------------------

	for (i = 0; i < np; i++)
		if (produtos[i] != NULL)
			apagarProduto(produtos[i]); // liberta a memória de cada produto dentro do array
	free(produtos);						// liberta a memória do array
}

// Função que retorna se a BDproduto está cheia ou não
int BDprodutocheio() {
	return (np == produtosAtuais);
}

// Função que insere produto na BDproduto e retorna sucesso ou insucesso
int inserirProduto(Produto p)
{
	int i;
	for (i = 0; i < np; i++)
		if (produtos[i] == NULL) {	// Encontrou uma posição vazia
			produtos[i] = p;		// Colocar ponteiro na posição encontrada
			produtosAtuais++;		// Incrementar numero actual de produtos no array
			return 1;				// Sucesso a inserir novo produto
		}
	return 0;						// Insucesso a inserir novo produto (array cheio)
}

// Função que liberta memória de um produto do array BDproduto (necessário limpar ponteiros das listas que contém esse produto)
void retirarProduto(char* nome)
{
	int i;

	for (i = 0; i < np; i++) {
		if (produtos[i] != NULL && strcmp(daNomeProduto(produtos[i]), nome) == 0) {
			apagarProduto(produtos[i]); // Liberta a memoria cujo ponteiro Produto com nome dado
			produtos[i] = NULL;         // coloca esse ponteiro a apontar para NULL (posição vazia)
			produtosAtuais--;
			break;
		}
	}
}

// Função para obter produtos por nome parcial 
// retorna um ponteiro para um array temporario com os Produtos encontrados + uma posição NULL para identificação do fim desse array
Produto* obterProdutosPorNome(char* nome) {

	int i, j = 0, count = 0;
	Produto* tempProdutos;

	for (i = 0; i < produtosAtuais; i++) {
		if (produtos[i] != NULL && strstr(daNomeProduto(produtos[i]), nome) != NULL) {
			count++;
		}
	}

	tempProdutos = (Produto*)malloc(sizeof(Produto) * (count + 1));

	for (i = 0; i < produtosAtuais; i++) {
		if (produtos[i] != NULL && strstr(daNomeProduto(produtos[i]), nome) != NULL) {
			tempProdutos[j++] = produtos[i];
		}
	}

	tempProdutos[j] = NULL;

	return tempProdutos;
}

// Função para listar produtos de acordo com o tipo de listagem e filtro
void listarProdutos(int tipoListagem, char* filtro) {
	int i, estaVazio = 1;

	for (i = 0; i < np; i++) {
		if (produtos[i] != NULL) {
			if (tipoListagem == 0) {
				// Listar todos os produtos
				imprimirProduto(produtos[i]);
				estaVazio = 0;
			}
			else if (tipoListagem == 1 && strcmp(daTipoProduto(produtos[i]), filtro) == 0) {
				// Listar produtos de um determinado tipo
				imprimirProduto(produtos[i]);
				estaVazio = 0;
			}
			else if (tipoListagem == 2 && strstr(daNomeProduto(produtos[i]), filtro) != NULL) {
				// Listar produtos que tenham no nome uma determinada string
				imprimirProduto(produtos[i]);
				estaVazio = 0;
			}
		}
	}
	if (estaVazio)
		printf("| Nenhum produto encontrado |\n");
}