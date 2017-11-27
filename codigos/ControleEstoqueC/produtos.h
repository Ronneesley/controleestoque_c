#ifndef PRODUTOS_H
#define PRODUTOS_H

#include <string.h>
#include <mysql/mysql.h>
#include "diretivas_conexao.h"
#include "gerais.h"


typedef struct {
	int id, qtdEmEstoque, dataCadastro, dataModificacao;
	char nome[100], fornecedor[100], descricao[100];
    float precoCompra, precoVenda;
} Produto;

//cadastro
void mostraMenuProdutos();
void mostrarCadastroProduto();
void insereProduto(Produto p);

//alteração
void alteraProduto(int id, char vetorCampo[], char string[], char tipoDoCampo);
void mostraAlteracaoProduto();

//exclusão
void mostraProdutos();
void mostraProduto(int id);
void mostraExclusaoProduto();
void excluiProduto(int id);

//layout
void mostraCabecalhoMenu();
void mostraLinhaMenu();

//outras
void leString(char s[], int tam);
int checaSeExiste(int id, char *tabela);

#endif