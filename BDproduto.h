#ifndef BDPRODUTO_H
#define BDPRODUTO_H

#include "produto.h"

/* cabeçalho das funções (operações) */
void criarBDproduto(int);
void apagarBDproduto();
int BDprodutocheio();
int inserirProduto(Produto);
void retirarProduto(char*);
Produto* obterProdutosPorNome(char*);
void listarProdutos(int, char*);

#endif



