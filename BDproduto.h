#ifndef BDPRODUTO_H
#define BDPRODUTO_H

#include "produto.h"

/* cabe�alho das fun��es (opera��es) */
void criarBDproduto(int);
void apagarBDproduto();
int BDprodutocheio();
int inserirProduto(Produto);
void retirarProduto(char*);
Produto* obterProdutosPorNome(char*);
void listarProdutos(int, char*);

#endif



