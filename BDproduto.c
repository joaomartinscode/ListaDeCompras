#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BDproduto.h"
#include "produto.h"

// TAI DE ORDEM 0 - "Base de Dados" produto

Produto* produtos;  // array de ponteiros para Produto
int np;				// valor maximo de produtos no array
int produtosAtuais; // valor de quantos produtos est�o no array a qualquer momento

// Fun��o que aloca mem�ria para criar um array de ponteiros tipo Produto
void criarBDproduto(int nProdutos) {
	int i;
	np = nProdutos;
	produtos = (Produto*)malloc(sizeof(Produto) * nProdutos);

	if (produtos == NULL)
		return; // Linha de codigo caso malloc falhe (remove WARNING)

	for (i = 0; i < nProdutos; i++)
		produtos[i] = NULL;		// preencher o array com posi��es vazias
	produtosAtuais = 0;			// inicializar o numero de produtos atuais
}

// Fun��o que liberta mem�ria criada do array de ponteiros tipo Produto (necess�rio limpar mem�ria alocada para listas)
void apagarBDproduto() {
	int i;

	// COLOCAR AQUI LOGICA QUE LIBERTA AS LISTAS PRIMEIRO --------------------------------------------------------------------------

	for (i = 0; i < np; i++)
		if (produtos[i] != NULL)
			apagarProduto(produtos[i]); // liberta a mem�ria de cada produto dentro do array
	free(produtos);						// liberta a mem�ria do array
}

// Fun��o que retorna se a BDproduto est� cheia ou n�o
int BDprodutocheio() {
	return (np == produtosAtuais);
}

// Fun��o que insere produto na BDproduto e retorna sucesso ou insucesso
int inserirProduto(Produto p)
{
	int i;
	for (i = 0; i < np; i++)
		if (produtos[i] == NULL) {	// Encontrou uma posi��o vazia
			produtos[i] = p;		// Colocar ponteiro na posi��o encontrada
			produtosAtuais++;		// Incrementar numero actual de produtos no array
			return 1;				// Sucesso a inserir novo produto
		}
	return 0;						// Insucesso a inserir novo produto (array cheio)
}

// Fun��o que liberta mem�ria de um produto do array BDproduto (necess�rio limpar ponteiros das listas que cont�m esse produto)
void retirarProduto(char* nome)
{
	int i;

	for (i = 0; i < np; i++) {
		if (produtos[i] != NULL && strcmp(daNomeProduto(produtos[i]), nome) == 0) {
			apagarProduto(produtos[i]); // Liberta a memoria cujo ponteiro Produto com nome dado
			produtos[i] = NULL;         // coloca esse ponteiro a apontar para NULL (posi��o vazia)
			produtosAtuais--;
			break;
		}
	}
}

// Fun��o para obter produtos por nome parcial 
// retorna um ponteiro para um array temporario com os Produtos encontrados + uma posi��o NULL para identifica��o do fim desse array
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

// Fun��o para listar produtos de acordo com o tipo de listagem e filtro
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