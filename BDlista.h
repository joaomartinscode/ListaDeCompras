#ifndef BDLISTA_H
#define BDLISTA_H

#include "lista.h"

/* cabeçalho das funções (operações) */
void criarBDlista(int);
void apagarBDlista();
int BDlistaCheio();
int inserirLista(Lista);
void retirarLista(char*);
void retirarTodosProdutoLista(Produto);
Lista obterListaPorNome(char*);
void listarListas();

#endif


