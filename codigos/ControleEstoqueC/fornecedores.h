/** 
 * File:   fornecedores.h
 * Author: Andreia, Ana Paula, Láila e Welliton
 *
 * Created on 31 de Outubro de 2017, 12:17
 */

#ifndef FORNECEDORES_H
#define FORNECEDORES_H

#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>
#include "diretivas_conexao.h"
#include "gerais.h"

// Tipo Variável para receber o campo CNPJ do Banco de Dados
typedef unsigned long long int ulong;

// Estrutura Fornecedores
typedef struct {
    int id;
    char nomeFornecedor[100];
    ulong CNPJ;
    char endereco[150];
} Fornecedores;

// Menu Principal do Cadastro de  Fornecedores
void MenuFornecedores();

// Acessa o sub Menu de consultas
void ConsultarFornecedores();

// Consulta os Fornecedores por ordem de nome
void consultarNome();

// consulta os Fornecedores por ordem de ID
void consultarId();

// Mostra Sub Menu da opção de exclusão de Fornecedores
void MenuExclusao();

// Consulta Fornecedores dentro da Função Excluir e Alterar Fornecedores
void ConsultarPadrao();

// Função para Excluir os Fornecedores
void ExcluirFornecedor();

// Função que excluir o Fornecedor do Banco de Dados
void DeletarFornecedor(int codigo);

// Função para cadastrar os Fornecedores
void CadastrarFornecedor();

// Função para inserir um  Fornecedor no Banco de Dados
void inserirFornecedores(Fornecedores f);

// Mostra Sub Menu da opção de Alteração de Fornecedores
void MenuAlteracao();

// Função para Alterar um Fornecedor
void MostrarAlteracaoFornecedores();

// Função para alterar o nome do Fornecedor no Banco de Dados.
void AlterarNomeFornecedores(Fornecedores f);

// Função para alterar o Cnpj do Fornecedor no Banco de Dados.
void AlterarCnpjFornecedores(Fornecedores f);

// Função para alterar o Endereço do Fornecedor no Banco de Dados.
void AlterarEndFornecedores(Fornecedores f);

// Mostra as informações do fornecedor a ser alterado antes de executar a alteração
Fornecedores* SelecionarFornecedores(int codigo);



#endif /* FORNECEDORES_H */

