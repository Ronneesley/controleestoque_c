/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   funcionarios.h
 * Author: brunoqualhato
 *
 * Created on 2 de Novembro de 2017, 21:11
 */

#ifndef FUNCIONARIOS_H
#define FUNCIONARIOS_H

#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>
#include "diretivas_conexao.h"
#include "gerais.h"

typedef struct {
    int  id;
    char nome[100];
    char sexo[3];
    char datanascimento[20];
    char endereco[200];
    char Cidade[50];
    int  cep;
    char  telefone[13];
    char  cpf[13];
    int  rg;
    char profissao[100];
    char  pispasep[12];
    
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
void alterarFuncionario(Funcionarios f);

 /**
 * Exclui funcionario cadastrado no banco de dados
 */
void ExclusaoFuncionario(int codigo);

Funcionarios* selecionarFuncionario(int codigo);
        
void mostrarAlteracaoFuncionario();

void mostrarExclusaoFuncionario();


#endif /* FUNCIONARIOS_H */