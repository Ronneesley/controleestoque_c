#ifndef ESTADOS_H
#define ESTADOS_H

#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>
#include "diretivas_conexao.h"
#include "gerais.h"

typedef struct {
    int idEstado;
    char nomeEstado[100];
    char uf[3];// enquanto o limite do vetor estava como 2 o cadastro não funcionava
    int idPais;
} Estado;

void mostrarListagemEstados();

void mostrarListagemPaises_Cadastro();

void mostrarCadastroEstado();

void inserirEstado(Estado e);
void excluirPais(int codigo);
void alterarEstado(Estado e);
Estado* selecionarEstado(int codigo);

void mostrarAlteracaoEstado();
void mostrarExclusaoEstado();
void excluirEstado(int codigo);

#endif
