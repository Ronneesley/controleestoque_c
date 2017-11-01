#ifndef FUNCIONARIOS_H
#define FUNCIONARIOS_H

#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>
#include "diretivas_conexao.h"
#include "gerais.h"

typedef struct {
    int id;
    char nome [100];
    char sexo [5];
    char datanasci [10];
    char endereco[100];
    char cidade[100];
    char profissao[100];
    int cep;
    int telefone; 
    int cpf;
    int rg;
    int pispasep;
} Funcionarios;


/**
 * Lista todos os funcinarios cadastrados no banco de dados
 */
void mostrarListagemFuncionarios();//OK

/**
 * Apresenta o cadastro de funcionario
 */
void mostrarCadastroFuncionario();//OK
		
/**
 * Função para inserção de um funcionario no banco de dados
 */
void inserirFuncionario(Funcionarios f);//OK

/**
 * Edita funcionario cadastrados no banco de dados
 */
void alterarfuncionario(Funcionarios f);

 /**
 * Exclui funcionario cadastrado no banco de dados
 */
void ExclusaoFuncionario(int codigo);

Funcionarios* selecionarFuncionario(int codigo);
        
void mostrarAlteracaoFuncionario();

void mostrarExclusaoFuncionario();

#endif