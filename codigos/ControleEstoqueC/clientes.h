/* 
 * File:   clientes.h
 * Author: ronneesley
 *
 * Created on 10 de Setembro de 2017, 21:31
 */

#ifndef CLIENTES_H
#define CLIENTES_H

#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>
#include "diretivas_conexao.h"
#include "gerais.h"

/**
 * Estrutura para representar um pais
 */
typedef struct {
    int id;
    char nome[100];
    char sexo[3];
    char datanasc[12];
    char endereco[200];
    char cidade[50];
    char cep[12];
    char telefone[17];
    char cpf[16];
    char rg[12];
    char profissao[50];
} Cliente;

/**
 * Lista todos os países cadastrados no banco de dados
 */
void mostrarListagemClientes();

/**
 * Apresenta o cadastro de países
 */
void mostrarCadastroCliente();

/**
 * Função para inserção de um país no banco de dados
 */
void inserirCliente(Cliente c);
void excluirCliente(int codigo);
void alterarCliente(Cliente c);
Cliente* selecionarCliente(int codigo);

void mostrarAlteracaoCliente();
void mostrarExclusaoCliente();
void excluirCliente(int codigo);

#endif /* CLIENTES_H */

