#ifndef PRODUTO_H
#define PRODUTO_H

/* defini��o do tipo */
typedef struct produto* Produto;

/* cabe�alho das fun��es (opera��es) */
Produto criarProduto(char*, char*);
void apagarProduto(Produto);
char* daNomeProduto(Produto);
char* daTipoProduto(Produto);
float daPrecoProduto(Produto);
char* daLojaProduto(Produto);
void alterarNomeProduto(Produto, char*);
void alterarPrecoLojaProduto(Produto, float, char*);
void imprimirProduto(Produto);

#endif

	