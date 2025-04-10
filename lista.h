#ifndef LISTA_H
#define LISTA_H

#include "produto.h"

/* definição do tipo */
typedef struct lista* Lista;

/* cabeçalho das funções (operações) */
Lista criarLista(char*, int);
void apagarLista(Lista);
char* daNomeLista(Lista);
void alterarNomeLista(Lista, char*);
void alterarCompradoLista(Lista, char*, int, int);
void adicionarProdutoLista(Lista, Produto, int, int);
void retirarProdutoLista(Lista, Produto, int);
Produto obterProdutoListaPorNome(Lista, Produto, int);
void definirProdutosNComprados(Lista, int);
void imprimirLista(Lista, int);

#endif
