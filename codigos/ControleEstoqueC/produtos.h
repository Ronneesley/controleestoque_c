#ifndef PRODUTOS_H
#define PRODUTOS_H

#include <string.h>
#include <mysql/mysql.h>
#include "diretivas_conexao.h"
#include "gerais.h"


typedef struct {
	int id, qtdEmEstoque, dataCadastro;
	char nome[100], fornecedor[100], descricao[100];
    float precoCompra, precoVenda;
} Produto;


/**
 * Lista todos os produtos cadastrados no banco de dados
 */
void mostraMenuPrincipal();//OK

/**
 * Apresenta o cadastro de produto
 */
void mostrarCadastroProduto();//OK

/**
 * Função para inserção de um produto no banco de dados
 */
void insereProduto(Produto p);//OK


/**
 * Edita produto cadastrados no banco de dados
 */
void alteraProduto(int id, char vetorCampo[], char string[], char tipoDoCampo);

void mostraProdutos();
void mostraProduto(int id);
void mostraAlteracaoProduto();
void leString(char *s, int tam);
int checaSeExiste(int id, char *tabela);
void mostraExclusaoProduto();
void excluiProduto(int id);
//layout
void mostraCabecalhoMenu();
void mostraLinhaMenu();





#endif
