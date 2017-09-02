#ifndef PRODUTOS_H
#define PRODUTOS_H

#include <stdio.h>
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
void mostrarListagemProdutos();//OK

/**
 * Apresenta o cadastro de produto
 */
void mostrarCadastroProduto();//OK


		//---BANCO DE DADOS---//
/**
 * Função para inserção de um produto no banco de dados
 */
void inserirProduto(Produto p);//OK


/**
 * Edita produto cadastrados no banco de dados
 */
//void alterarProduto();

 /**
 * Exclui produto cadastrado no banco de dados
 */
//void excluirProduto();

#endif
