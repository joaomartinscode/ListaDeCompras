#ifndef PRODUTO_H
#define PRODUTO_H

/* definição do tipo */
typedef struct produto* Produto;

/* cabeçalho das funções (operações) */
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

	