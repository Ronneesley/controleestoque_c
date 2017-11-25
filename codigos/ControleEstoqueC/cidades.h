/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cidade.h
 * Author: blackowl
 *
 * Created on October 30, 2017, 10:13 PM
 */

#ifndef CIDADE_H
#define CIDADE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>
#include "diretivas_conexao.h"
#include "gerais.h"

typedef struct {
    int id;
    int idEstado;
    char cep[10];
    char nome[101];
}Cidade;

void mostrarListagemCidades();
void mostrarCadastroCidade();
void mostrarAlteracaoCidade();
void mostrarListagemEstado_Cadastro();
void inserirCidade(Cidade c);
void mostrarExclusaoCidade();
void ExclusaoCidade(int codigo);
void alterarCidade(Cidade c);
Cidade* selecionarCidade(int id);
#endif /* CIDADE_H */
