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
#include "diretivas_conexao.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct {
    int id;
    int idEstado;
    char uf[3];
    char nome[101];
}cidade;

void mostrarListagemCidades();
void mostrarCadastroCidade();
void inserirCidade(cidade);
void mostrarExclusaoCidade();
void ExclusaoCidade(int codigo);

#endif /* CIDADE_H */

