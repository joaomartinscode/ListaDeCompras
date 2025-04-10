#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BDproduto.h"
#include "BDlista.h"
#include "produto.h"
#include "lista.h"

/*
Instituto Politécnico de Portalegre
Algoritmos e Estrutura de Dados
Ficha 3 - Projeto 1 - Lista de Compras
Engenharia Informática - 1.º Ano
*/

/*
Lista de Warnings suprimidos neste projeto:
C4996: "Function was declared deprecated"		| Para podermos utilizar scanf()
C6011: "Dereferencing NULL pointer ' '			| Para podermos ignorar o aviso de um ponteiro poder estar a apontar para NULL
C6031: "Return value ignored"					| Para podermos ignorar o que a função scanf() retorna
C6387: "Invalid Parameter Passed to Function"	| Para não ser necessário verificar o retorno de malloc (warning surge caso malloc falhe e retorne NULL)
*/

int menu(int n)
{
	switch (n) {
	case 1: {
		printf("\n  ** Lista de Compras **\n\n");
		printf(" 1 - Opcoes BDproduto\n");
		printf(" 2 - Opcoes BDlista\n");
		printf(" 3 - Opcoes Compras\n");
		printf(" 0 - sair\n");
		break;
	}
	case 2: {
		printf("\n  ** MENU BDproduto **\n\n");
		printf(" 1 - Inserir novo produto\n");
		printf(" 2 - Apagar produto\n");
		printf(" 3 - Listar produtos\n");
		printf(" 4 - Alterar nome de produto\n");
		printf(" 0 - voltar ao menu principal\n");
		break;
	}
	case 3: {
		printf("\n  ** MENU BDlista **\n\n");
		printf(" 1 - Inserir nova lista\n");
		printf(" 2 - Apagar lista\n");
		printf(" 3 - Listar listas\n");
		printf(" 4 - Alterar nome de lista\n");
		printf(" 5 - Adicionar produto a lista\n");
		printf(" 6 - Retirar produto a lista\n");
		printf(" 0 - voltar ao menu principal\n");
		break;
	}
	case 4: {
		printf("\n  ** MENU Compras **\n\n");
		printf(" 1 - Registar produto como comprado\n");
		printf(" 2 - Registar todos os produtos como nao comprados\n");
		printf(" 0 - voltar ao menu principal\n");
		break;
	}
	}

	int opcao;
	printf("\n Indique a sua opcao: ");
	scanf("%i", &opcao);
	while (getchar() != '\n');
	return opcao;
}

// FUNÇÕES PRODUTO	----------------------------------------------------------------

// Função para procurar e retornar um produto atravéz do nome
Produto procurarProduto(char* nome) {
	int i, j;
	char tempNomeC[2048] = "\0";		// array temporario para guardar nome completo dado pelo utilizador
	Produto produtoEncontrado;			// ponteiro temporario para guardar produto encontrado
	Produto* produtosEncontrados;		// ponteiro para array de ponteiros temporario para guardar produtos encontrados
	produtosEncontrados = obterProdutosPorNome(nome);

	if (produtosEncontrados[0] == NULL) { 			// Nenhum produto encontrado
		printf(" Nenhum produto encontrado com o nome \"%s\"", nome);
		return NULL;
	}
	else if (produtosEncontrados[1] == NULL) { 		// Apenas um produto encontrado
		produtoEncontrado = produtosEncontrados[0];
		free(produtosEncontrados);
		return produtoEncontrado;
	}
	else {										// Vários produtos encontrados, pedir o nome completo
		printf("\n Produtos encontrados:\n\n");
		for (j = 0; produtosEncontrados[j] != NULL; j++) {
			imprimirProduto(produtosEncontrados[j]);
		}
		printf("\n\n Por favor, insira o nome completo: ");

		fgets(tempNomeC, sizeof(tempNomeC), stdin);
		tempNomeC[strcspn(tempNomeC, "\n")] = '\0';

		for (i = 0; produtosEncontrados[i] != NULL; i++) {
			if (strcmp(daNomeProduto(produtosEncontrados[i]), tempNomeC) == 0) {
				produtoEncontrado = produtosEncontrados[i];
				free(produtosEncontrados);
				return produtoEncontrado;
			}
		}
		printf(" Nenhum produto encontrado com o nome \"%s\"", tempNomeC);
	}
	free(produtosEncontrados);
	return NULL;
}

// Função para inserir um Produto à BDproduto
void inserirProdutoBDproduto() {

	if (BDprodutocheio()) {
		printf("BDproduto cheio!");
		return;
	}

	Produto p = NULL;
	char tempNome[2048] = "\0";
	char tempTipo[2048] = "\0";

	printf("\n Nome: ");
	fgets(tempNome, sizeof(tempNome), stdin);
	tempNome[strcspn(tempNome, "\n")] = '\0'; // remover o "\n"

	printf("\n Tipo: ");
	fgets(tempTipo, sizeof(tempTipo), stdin);
	tempTipo[strcspn(tempTipo, "\n")] = '\0'; // remover o "\n"

	p = criarProduto(tempNome, tempTipo);
	inserirProduto(p);
	printf("\n Produto %s - %s criado com sucesso!", tempNome, tempTipo);
}

// Função para apagar um Produto, primeiro retirando-o das listas e apenas depois retira-lo da BDproduto e libertar a memoria
void apagarProdutoBDproduto()
{
	char tempNome[2048] = "\0";			// array temporario para guardar nome dado pelo utilizador
	Produto produtoEncontrado;

	printf("\n Nome do produto que quer apagar: ");

	fgets(tempNome, sizeof(tempNome), stdin);
	tempNome[strcspn(tempNome, "\n")] = '\0'; // remover o "\n"

	produtoEncontrado = procurarProduto(tempNome);

	if (produtoEncontrado == NULL) {
		printf(" Produto \"%s\" nao encontrado\n", tempNome);
		return;
	}

	printf(" Produto \"%s\" retirado das Listas e eliminado com sucesso!", daNomeProduto(produtoEncontrado));
	retirarTodosProdutoLista(produtoEncontrado);
	retirarProduto(daNomeProduto(produtoEncontrado));
}

// Função para listar produtos, de um, dois ou três modos (todos, por tipo, por nome)
void listaProduto() {
	printf("\n Escolha o tipo de listagem:\n");
	printf(" 1 - Todos os produtos\n"); // utilizar argumento "0", filtro = NULL,  na função listarProdutos(argumento, filtro);
	printf(" 2 - Produtos por tipo\n"); // utilizar argumento "1", filtro = tipo,  na função listarProdutos(argumento, filtro);
	printf(" 3 - Produtos por nome\n"); // utilizar argumento "2", filtro = nome,  na função listarProdutos(argumento, filtro);

	int tipoListagem;
	printf("\n Indique a sua opcao: ");
	scanf("%d", &tipoListagem);
	getchar();
	if (tipoListagem == 1) {
		system("cls");
		printf("\n  ** Todos os produtos **\n\n");
		listarProdutos(0, NULL);
	}
	else if (tipoListagem == 2) {
		system("cls");
		printf("\n  ** Produtos por tipo **\n\n");
		char tipo[2048];
		printf(" Digite o tipo de produto: ");
		fgets(tipo, sizeof(tipo), stdin);
		tipo[strcspn(tipo, "\n")] = '\0'; // remover o "\n"
		printf("\n");
		listarProdutos(1, tipo);
	}
	else if (tipoListagem == 3) {
		system("cls");
		printf("\n  ** Produtos por nome **\n\n");
		char nome[2048];
		printf(" Digite a string do nome do produto: ");
		fgets(nome, sizeof(nome), stdin);
		nome[strcspn(nome, "\n")] = '\0'; // remover o "\n"
		printf("\n");
		listarProdutos(2, nome);
	}
	else {
		printf("Opcao invalida.\n");
	}
}

// Função para mudar nome de produto
void alterarNomeProdutoBDproduto() {
	char tempNome[2048] = "\0";			// array temporario para guardar nome dado pelo utilizador
	char tempNovoNome[2048] = "\0";		// array temporario para guardar novo nome dado pelo utilizador
	Produto produtoEncontrado;

	printf("\n Nome do produto que quer alterar o nome: ");

	fgets(tempNome, sizeof(tempNome), stdin);
	tempNome[strcspn(tempNome, "\n")] = '\0'; // remover o "\n"

	produtoEncontrado = procurarProduto(tempNome);

	if (produtoEncontrado == NULL) {
		printf(" Produto \"%s\" nao encontrado", tempNome);
		return;
	}

	printf("\n Novo nome: ");

	fgets(tempNovoNome, sizeof(tempNovoNome), stdin);
	tempNovoNome[strcspn(tempNovoNome, "\n")] = '\0'; // remover o "\n"

	alterarNomeProduto(produtoEncontrado, tempNovoNome);
	printf(" Produto alterado para nome \"%s\" com sucesso!", daNomeProduto(produtoEncontrado));

}

// FUNÇÕES LISTA	----------------------------------------------------------------

// Função para inserir uma Lista à BDlista
void inserirListaBDlista(int n) {

	if (BDlistaCheio()) {
		printf("BDlista cheia!");
		return;
	}

	Lista listaEncontrada;			// ponteiro temporario para guardar lista encontrada

	Lista l = NULL;
	char tempNome[2048] = "\0";

	printf("\n Nome: ");
	fgets(tempNome, sizeof(tempNome), stdin);
	tempNome[strcspn(tempNome, "\n")] = '\0'; // remover o "\n"

	listaEncontrada = obterListaPorNome(tempNome);

	if (listaEncontrada != NULL) {
		printf(" Lista \"%s\" ja se encontra na BDlista\n", tempNome);
		return;
	}

	l = criarLista(tempNome, n);
	inserirLista(l);
	printf(" Lista \"%s\" criada com sucesso!", tempNome);
}

// Função para apagar uma Lista
void retirarListaBDlista()
{
	char tempNome[2048] = "\0"; // array temporario para guardar nome dado pelo utilizador
	Lista tempLista;

	printf("\n\n Nome da lista que quer apagar: ");

	fgets(tempNome, sizeof(tempNome), stdin);
	tempNome[strcspn(tempNome, "\n")] = '\0'; // remover o "\n"

	tempLista = obterListaPorNome(tempNome);

	if (tempLista == NULL) {
		printf(" Lista \"%s\" nao encontrada\n", tempNome);
		return;
	}

	retirarLista(tempNome);
	printf(" Lista \"%s\" retirado da BDlista com sucesso!", tempNome);
}

// Função para mudar nome de uma lista
void alterarNomeListaBDlista() {
	char tempNome[2048] = "\0";			// array temporario para guardar nome dado pelo utilizador
	char tempNovoNome[2048] = "\0";		// array temporario para guardar novo nome dado pelo utilizador
	Lista listaEncontrada;

	printf("\n Nome da lista que quer alterar o nome: ");

	fgets(tempNome, sizeof(tempNome), stdin);
	tempNome[strcspn(tempNome, "\n")] = '\0'; // remover o "\n"

	listaEncontrada = obterListaPorNome(tempNome);

	if (listaEncontrada == NULL) {
		printf(" Lista \"%s\" nao encontrada", tempNome);
		return;
	}

	printf("\n Novo nome: ");

	fgets(tempNovoNome, sizeof(tempNovoNome), stdin);
	tempNovoNome[strcspn(tempNovoNome, "\n")] = '\0'; // remover o "\n"

	alterarNomeLista(listaEncontrada, tempNovoNome);
	printf(" Lista alterada para nome \"%s\" com sucesso!", daNomeLista(listaEncontrada));

}

// Função para adicionar um produto a uma lista (confirma que não está a ser adicionado um produto duplicado)
void adicionarProdutoListaBDlista(int n) {
	char tempNomeP[2048] = "\0";	// array temporario para guardar nome do produto dado pelo utilizador
	char tempNomeL[2048] = "\0";	// array temporario para guardar nome da lista dado pelo utilizador
	Produto produtoEncontrado;		// ponteiro temporario para guardar produto encontrado
	Produto produtoNaLista;			// ponteiro temporario para guardar produto encontrado dentro da lista
	Lista listaEncontrada;			// ponteiro temporario para guardar lista encontrada
	int quantidade;

	printf("\n\n Nome da lista que quer adicionar produto: ");

	fgets(tempNomeL, sizeof(tempNomeL), stdin);
	tempNomeL[strcspn(tempNomeL, "\n")] = '\0'; // remover o "\n"

	listaEncontrada = obterListaPorNome(tempNomeL);

	if (listaEncontrada == NULL) {
		printf(" Lista \"%s\" nao encontrada\n", tempNomeL);
		return;
	}

	printf("\n\n Nome do Produto que quer adicionar: ");

	fgets(tempNomeP, sizeof(tempNomeP), stdin);
	tempNomeP[strcspn(tempNomeP, "\n")] = '\0';


	produtoEncontrado = procurarProduto(tempNomeP);

	if (produtoEncontrado == NULL) {
		return;
	}

	produtoNaLista = obterProdutoListaPorNome(listaEncontrada, produtoEncontrado, n);

	if (produtoNaLista != NULL) {
		printf(" Produto \"%s\" ja se encontra na lista\n", daNomeProduto(produtoEncontrado));
		return;
	}

	printf("\n\n Quantidade do Produto \"%s\" que quer adicionar: ", daNomeProduto(produtoEncontrado));
	scanf(" %i", &quantidade);

	adicionarProdutoLista(listaEncontrada, produtoEncontrado, quantidade, n);
	printf(" %ix Produto \"%s\" adicionado a lista \"%s\" com sucesso!\n", quantidade, daNomeProduto(produtoEncontrado), tempNomeL);
}

// Função para retirar um produto de uma lista
void retirarProdutoListaBDlista(int n) {
	char tempNomeP[2048] = "\0";	// array temporario para guardar nome do produto dado pelo utilizador
	char tempNomeL[2048] = "\0";	// array temporario para guardar nome da lista dado pelo utilizador
	Produto produtoEncontrado;		// ponteiro temporario para guardar produto encontrado
	Lista listaEncontrada;			// ponteiro temporario para guardar lista encontrada

	printf("\n\n Nome da lista que quer retirar produto: ");

	fgets(tempNomeL, sizeof(tempNomeL), stdin);
	tempNomeL[strcspn(tempNomeL, "\n")] = '\0'; // remover o "\n"

	listaEncontrada = obterListaPorNome(tempNomeL);

	if (listaEncontrada == NULL) {
		printf(" Lista \"%s\" nao encontrada\n", tempNomeL);
		return;
	}

	printf("\n\n Nome do Produto que quer retirar: ");

	fgets(tempNomeP, sizeof(tempNomeP), stdin);
	tempNomeP[strcspn(tempNomeP, "\n")] = '\0';

	produtoEncontrado = procurarProduto(tempNomeP);

	if (produtoEncontrado == NULL) {
		return;
	}

	strcpy(tempNomeP, daNomeProduto(produtoEncontrado));

	// procurar na lista se o produto encontrado existe e atualizar
	produtoEncontrado = obterProdutoListaPorNome(listaEncontrada, produtoEncontrado, n);

	if (produtoEncontrado == NULL) {
		printf(" Produto \"%s\" nao encontrado na lista\n", tempNomeP);
		return;
	}

	retirarProdutoLista(listaEncontrada, produtoEncontrado, n);
	printf(" Produto \"%s\" retirado da lista \"%s\" com sucesso!\n", tempNomeP, tempNomeL);
}

// FUNÇÕES COMPRAS	----------------------------------------------------------------

// Função para registar um produto de uma lista como comprado
void registarProdutoComprado(int n) {
	char tempNomeP[2048] = "\0";	// array temporario para guardar nome do produto dado pelo utilizador
	char tempNomeL[2048] = "\0";	// array temporario para guardar nome da lista dado pelo utilizador
	char tempNomeLoja[2048] = "\0";		// array temporario para guardar nome da loja dado pelo utilizador

	Produto produtoEncontrado;		// ponteiro temporario para guardar produto encontrado
	Lista listaEncontrada;			// ponteiro temporario para guardar lista encontrada
	float tempPreco;


	printf("\n\n Nome da lista: ");

	fgets(tempNomeL, sizeof(tempNomeL), stdin);
	tempNomeL[strcspn(tempNomeL, "\n")] = '\0'; // remover o "\n"

	listaEncontrada = obterListaPorNome(tempNomeL);

	if (listaEncontrada == NULL) {
		printf(" Lista \"%s\" nao encontrada\n", tempNomeL);
		return;
	}

	printf("\n\n Nome do produto: ");

	fgets(tempNomeP, sizeof(tempNomeP), stdin);
	tempNomeP[strcspn(tempNomeP, "\n")] = '\0';

	produtoEncontrado = procurarProduto(tempNomeP);

	if (produtoEncontrado == NULL) {
		return;
	}

	// procurar na lista se o produto encontrado existe e atualizar
	produtoEncontrado = obterProdutoListaPorNome(listaEncontrada, produtoEncontrado, n);


	if (produtoEncontrado == NULL) {
		printf(" Produto \"%s\" nao encontrado na lista \"%s\"\n", daNomeProduto(produtoEncontrado), daNomeLista(listaEncontrada));
		return;
	}

	printf("\n\n Preco a que comprou o produto \"%s\": ", daNomeProduto(produtoEncontrado));
	scanf(" %f", &tempPreco);
	getchar();

	printf("\n\n Loja onde comprou o produto \"%s\": ", daNomeProduto(produtoEncontrado));
	fgets(tempNomeLoja, sizeof(tempNomeLoja), stdin);
	tempNomeLoja[strcspn(tempNomeLoja, "\n")] = '\0';


	alterarCompradoLista(listaEncontrada, daNomeProduto(produtoEncontrado), 1, n); // 1 = COMPRADO: SIM
	alterarPrecoLojaProduto(produtoEncontrado, tempPreco, tempNomeLoja);

	printf(" Produto \"%s\" registado como comprado com sucesso!\n", daNomeProduto(produtoEncontrado));
}

// Função para registar todos os produtos de uma lista como não comprados
void registarProdutosNComprado(int n) {
	char tempNomeL[2048] = "\0";	// array temporario para guardar nome da lista dado pelo utilizador
	char decisao;

	Lista listaEncontrada;			// ponteiro temporario para guardar lista encontrada

	printf("\n\n Nome da lista: ");

	fgets(tempNomeL, sizeof(tempNomeL), stdin);
	tempNomeL[strcspn(tempNomeL, "\n")] = '\0'; // remover o "\n"

	listaEncontrada = obterListaPorNome(tempNomeL);

	if (listaEncontrada == NULL) {
		printf(" Lista \"%s\" nao encontrada\n", tempNomeL);
		return;
	}

	printf("\n\n Tem a certeza que quer colocar todos os produtos de \"%s\" como nao comprados? (S/N): ", daNomeLista(listaEncontrada));
	scanf("%c", &decisao);
	getchar();

	if (decisao == 's' || decisao == 'S') {
		definirProdutosNComprados(listaEncontrada, n);
		printf(" Produtos de \"%s\" registados como nao comprados com sucesso!\n", daNomeLista(listaEncontrada));
	}

}

// FUNÇÕES AUXILIARES	----------------------------------------------------------------

// Função para preencher BDproduto e BDlista
void popularBDs(int n) {

	int i;

	char* produtos[] = {
		"banana", "banana da madeira", "iogurte", "iogurte de pedacos", "iogurte grego",
		"leite magro", "leite gordo", "queijo cheddar", "queijo mozzarella", "queijo feta",
		"pao de forma", "pao integral", "pao de centeio", "cafe torrado", "cafe soluvel",
		"cha verde", "cha preto", "manteiga", "margarina", "azeite virgem",
		"oleo de girassol", "farinha de trigo", "farinha de milho", "acucar branco", "acucar amarelo",
		"sal grosso", "sal fino", "massa esparguete", "massa penne", "arroz basmati"
	};
	
	for (i = 0; i < n / 2 && i < (sizeof(produtos) / sizeof(produtos[0])); i++) {
		Produto p = criarProduto(produtos[i], "Produto generico");
		inserirProduto(p);
	}

	inserirLista(criarLista("compras", n));
}

// Função para parar execução e esperar por "qualquer tecla"
void continuar() {
	printf("\n\n Continuar?\n");
	printf("\n ********** ~o~ **********\n\n ");
	system("pause > NUL");
}


int main()
{
	int op1 = -1, op2 = -1, n;

	printf("\n Indique o numero de produtos da database: ");
	scanf("%i", &n);

	criarBDproduto(n);
	criarBDlista(n);
	popularBDs(n);

	do {
		system("cls");
		op1 = menu(1);
		switch (op1) {
		case 0: // 0 - Sair
			system("cls");
			printf("Obrigado por utilizar este programa!\n");
			apagarBDproduto();
			printf("Memoria libertada com sucesso!\n\n");
			return 0;
		case 1: // Opcoes BDproduto
			do {
				system("cls");
				op2 = menu(2);
				switch (op2) {
				case 0:
					break;
				case 1:
					system("cls");
					printf("\n  ** Inserir novo produto **\n");
					inserirProdutoBDproduto();
					continuar();
					break;
				case 2:
					system("cls");
					printf("\n  ** Apagar produto **\n");
					apagarProdutoBDproduto();
					continuar();
					break;
				case 3:
					system("cls");
					printf("\n  ** Listar produtos **\n");
					listaProduto();
					continuar();
					break;
				case 4:
					system("cls");
					printf("\n  ** Alterar nome de produto **\n");
					alterarNomeProdutoBDproduto();
					continuar();
					break;
				default:
					printf("\n\nOpcao errada\n");
					continuar();
					break;
				}
			} while (op2 != 0);
			break;
		case 2: // Opcoes BDlista
			do {
				system("cls");

				op2 = menu(3);
				switch (op2) {
				case 0:
					break;
				case 1:
					system("cls");
					printf("\n  ** Inserir nova lista **\n");
					inserirListaBDlista(n);
					continuar();
					break;
				case 2:
					system("cls");
					printf("\n  ** Apagar lista **\n");
					retirarListaBDlista();
					continuar();
					break;
				case 3:
					system("cls");
					printf("\n  ** Listar listas **\n\n");
					listarListas();
					continuar();
					break;
				case 4:
					system("cls");
					printf("\n  ** Alterar nome de lista **\n");
					alterarNomeListaBDlista();
					continuar();
					break;
				case 5:
					system("cls");
					printf("\n  ** Inserir produto a lista **\n");
					adicionarProdutoListaBDlista(n);
					continuar();
					break;
				case 6:
					system("cls");
					printf("\n  ** Retirar produto a lista **\n");
					retirarProdutoListaBDlista(n);
					continuar();
					break;
				default:
					printf("\n\nOpcao errada\n");
					break;
				}
			} while (op2 != 0);
			break;
		case 3: // Opcoes Compras
			do {
				system("cls");
				op2 = menu(4);
				switch (op2) {
				case 0:
					break;
				case 1:
					system("cls");
					printf("\n  ** Registar produto como Comprado **\n");
					registarProdutoComprado(n);
					continuar();
					break;
				case 2:
					system("cls");
					printf("\n  ** Registar todos os produtos como nao comprados **\n");
					registarProdutosNComprado(n);
					continuar();
					break;
				default:
					printf("\n\nOpcao errada\n");
					break;
				}
			} while (op2 != 0);
			break;
		default:
			printf("\n\nOpcao errada\n");
			break;
		}
	} while (op1 != 0);
}

