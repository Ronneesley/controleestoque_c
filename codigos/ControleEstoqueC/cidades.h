
/* 
 * File:   cidade.h
 * Author: Daniel, Matheus, Patricia,Vitor
 *
 * Created on October 30, 2017, 10:13 PM
 */

#ifndef CIDADE_H
#define CIDADE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>
#include "estados.h"
#include "diretivas_conexao.h"
#include "gerais.h"

typedef struct {
    int id;
    int idEstado;
    
    char nome[100];
}Cidade;

void mostrarListagemCidades();
void mostrarCadastroCidade();
void mostrarAlteracaoCidade();
void mostrarListaEstados();
void inserirCidade(Cidade c);
void mostrarExclusaoCidade();
void ExclusaoCidade(int codigo);
void alterarCidade(Cidade c);
Cidade* selecionarCidade(int id);
#endif /* CIDADE_H */
