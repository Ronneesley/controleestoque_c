/** 
 * File:   fornecedores.h
 * Author: welliton
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

// Estrutura Fornecedores
typedef struct {
    int id;
    char nome[100];
    int CNPJ;
} Fornecedores;

// Menu Principal do Cadastro de  Fornecedores
void MenuFornecedores();

// Acessa o sub Menu de consultas
void ConsultaFornecedores();

// Consulta os Fornecedores por ordem de nome
void consultaNome();

// consulta os Fornecedores por ordem de ID
void consultaId();



#endif /* FORNECEDORES_H */

